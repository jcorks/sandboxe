#include <sandboxe/script/duktape/runtime_dt_debug.h>
#include <sandboxe/script/duktape/runtime_dt_tobject.h>
#include <duk_trans_dvalue.h>
#include <cassert>
#ifdef SANDBOXE_DT_DEBUG

using namespace Sandboxe::Script::Runtime;



static DTContext * ctx_attached = nullptr;


void sandboxe_dt_trans_received(duk_trans_dvalue_ctx * ctx, duk_dvalue * dv) {
    char output[DUK_DVALUE_TOSTRING_BUFLEN];    
    duk_dvalue_to_string(dv, output);
    printf("dvalue received: %s\n", output);
}

void sandboxe_dt_trans_cooperate(duk_trans_dvalue_ctx * ctx, int block) {
    static int first_blocked = 1;

    if (!block) {
        /* Duktape is not blocked; you can cooperate with e.g. a user
         * interface here and send dvalues to Duktape, but don't block.
         */
        return;
    }

    /* Duktape is blocked on a read and won't continue until debug
     * command(s) are sent.
     *
     * Normally you'd enter your own event loop here, and process
     * events until something needs to be sent to Duktape.  For
     * example, the user might press a "Step over" button in the
     * UI which would cause dvalues to be sent.  You can then
     * return from this callback.
     *
     * The code below sends some example messages for testing the
     * dvalue handling of the transport.
     *
     * If you create dvalues manually and send them using
     * duk_trans_dvalue_send(), you must free the dvalues after
     * the send call returns using duk_dvalue_free().
     */

    if (first_blocked) {
        char *tmp;
        int i;

        /* First time Duktape becomes blocked, send DumpHeap which
         * exercises a lot of parsing code.
         *
         * NOTE: Valgrind may complain about reading uninitialized
         * bytes.  This is caused by the DumpHeap command writing out
         * verbatim duk_tval values which are intentionally not
         * always fully initialized for performance reasons.
         */
        first_blocked = 0;

        fprintf(stderr, "Duktape is blocked, send DumpHeap\n");
        fflush(stderr);

        duk_trans_dvalue_send_req(ctx);
        duk_trans_dvalue_send_integer(ctx, 0x20);  /* DumpHeap */
        duk_trans_dvalue_send_eom(ctx);

        /* Also send a dummy TriggerStatus request with trailing dvalues
         * ignored by Duktape; Duktape will parse the dvalues to be able to
         * skip them, so that the dvalue encoding is exercised.
         */

        tmp =(char*) malloc(100000);  /* long buffer, >= 65536 chars */
        for (i = 0; i < 100000; i++) {
            tmp[i] = (char) i;
        }
        duk_trans_dvalue_send_req(ctx);
        duk_trans_dvalue_send_integer(ctx, 0x11);  /* TriggerStatus */
        duk_trans_dvalue_send_string(ctx, "dummy");  /* short, <= 31 chars */
        duk_trans_dvalue_send_string(ctx, "123456789012345678901234567890foobar");  /* medium, >= 32 chars */
        duk_trans_dvalue_send_lstring(ctx, (const char *) tmp, 65535UL);
        duk_trans_dvalue_send_lstring(ctx, (const char *) tmp, 65536UL);
        duk_trans_dvalue_send_lstring(ctx, (const char *) tmp, 100000UL);
        duk_trans_dvalue_send_buffer(ctx, (const char *) tmp, 255U);
        duk_trans_dvalue_send_buffer(ctx, (const char *) tmp, 65535UL);
        duk_trans_dvalue_send_buffer(ctx, (const char *) tmp, 65536UL);
        duk_trans_dvalue_send_buffer(ctx, (const char *) tmp, 100000UL);
        duk_trans_dvalue_send_unused(ctx);
        duk_trans_dvalue_send_undefined(ctx);
        duk_trans_dvalue_send_null(ctx);
        duk_trans_dvalue_send_true(ctx);
        duk_trans_dvalue_send_false(ctx);
        duk_trans_dvalue_send_number(ctx, 123.456);
        duk_trans_dvalue_send_object(ctx, 12 /*classnum*/, (const char *) tmp, 8);  /* fake ptr len */
        duk_trans_dvalue_send_pointer(ctx, (const char *) tmp, 8);  /* fake ptr len */
        duk_trans_dvalue_send_lightfunc(ctx, 0xdabc /*lf_flags*/, (const char *) tmp, 8);  /* fake ptr len */
        duk_trans_dvalue_send_heapptr(ctx, (const char *) tmp, 8);  /* fake ptr len */

        duk_trans_dvalue_send_eom(ctx);
    }

    fprintf(stderr, "Duktape is blocked, send Eval and StepInto to resume execution\n");
    fflush(stderr);

    /* duk_trans_dvalue_send_req_cmd() sends a REQ dvalue followed by
     * an integer dvalue (command) for convenience.
     */

    duk_trans_dvalue_send_req_cmd(ctx, 0x1e);  /* 0x1e = Eval */
    duk_trans_dvalue_send_string(ctx, "8+8");
    duk_trans_dvalue_send_eom(ctx);

    duk_trans_dvalue_send_req_cmd(ctx, 0x14);  /* 0x14 = StepOver */
    duk_trans_dvalue_send_eom(ctx);
}


void sandboxe_dt_trans_handshake(duk_trans_dvalue_ctx * ctx, const char * handshake) {
    printf("handshake: %s\n", handshake);
}

void sandboxe_dt_trans_detached(duk_trans_dvalue_ctx * ctx) {
    printf("was detached!\n");
}

DTDebugger::DTDebugger(DTContext * context) {
    ctx = context;
    paused = false;
}

void DTDebugger::Pause() {
    if (ctx_attached) {
        return;
    }

    duk_trans_dvalue_ctx * trans_ctx = duk_trans_dvalue_init();
    if (!trans_ctx) {
        return;
    }


    ctx_attached = ctx;
    paused = true;

    Dynacoe::Console::Show(true);
    Dynacoe::Engine::Pause();
    

    trans_ctx->cooperate = sandboxe_dt_trans_cooperate;
    trans_ctx->received = sandboxe_dt_trans_received;
    trans_ctx->handshake = sandboxe_dt_trans_handshake;
    trans_ctx->detached = sandboxe_dt_trans_detached;

    /* Attach debugger; this will fail with a fatal error here unless
     * debugger support is compiled in.  To fail more gracefully, call
     * this under a duk_safe_call() to catch the error.
     */
    duk_debugger_attach(
        ctx->GetCTX(),
        duk_trans_dvalue_read_cb,
        duk_trans_dvalue_write_cb,
        duk_trans_dvalue_peek_cb,
        duk_trans_dvalue_read_flush_cb,
        duk_trans_dvalue_write_flush_cb,
        NULL,  /* app request cb */
        duk_trans_dvalue_detached_cb,
        (void *) trans_ctx
    );

    
    while(Dynacoe::Engine::IsPaused()) {
        Dynacoe::Engine::Iterate();
        duk_debugger_cooperate(ctx->GetCTX());
    }
    duk_debugger_detach(ctx->GetCTX());
    paused = false;
    Dynacoe::Engine::Resume();

    //duk_debugger_detach(ctx_attached->GetCTX());
    ctx_attached = nullptr;    
}


void DTDebugger::Resume() {
    if (!ctx_attached) return;
    // send request
    //duk_debugger_cooperate(ctx_attached->GetCTX());
    Dynacoe::Console::Show(false);
    Dynacoe::Engine::Resume();
}


std::string DTDebugger::GetBacktraceString() const {
    duk_context * source = ctx->GetCTX();
    int stackSize = duk_get_top(source);

    int level = -1;   
    duk_inspect_callstack_entry(source, level);
    std::vector<std::string> fns;
    std::vector<std::string> lineNumbers;
    std::vector<std::string> filenames;

    std::string empty;
    while(true) {
        TObject current(source);
    
        if (std::string(current.ThisAsPrimitive()) == empty) {
            duk_pop(source);
            break;
        } else {
            level--;
            std::string fn = "";
            std::string lineNumber = current.Get("lineNumber");
            std::string filename = "";

            duk_get_prop_string(source, -1, "function");
            {
                TObject nameObject(source);
                std::string temp = nameObject.Get("name");
                filename = nameObject.Get("fileName");
                if (temp != "") {
                    fn = temp + "()";
                }
            }
            duk_pop(source);

            if (!(lineNumber == "0" && filename == "undefined")) {
                fns.push_back(fn);
                lineNumbers.push_back(lineNumber);
                filenames.push_back(filename);
            }
            duk_pop(source);
            duk_inspect_callstack_entry(source, level);
        }
    }

    Dynacoe::Chain out = "Backtrace:\n";
    for(uint32_t i = 0; i < fns.size(); ++i) {
        out = out <<  "    (#" << i << ") -> " << fns[i] <<  "" << filenames[i] << " @ Line " << lineNumbers[i] << "\n"; 
    }


    assert(duk_get_top(source) == stackSize);
    return out;
}




#endif
