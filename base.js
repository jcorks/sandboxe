// base outline for dynaoce module
// "Revealing module pattern"


var sandboxe = {

    vector : {
        create : __vector_create_new
    },
    
    entity : {
        create : __entity_create_default,
        getAll : __entity_get_all,
        
        
        updateClass : {
            before : 0,
            ater : 1
        }
    },

    component : {
        create : __component_create
    },
    
    script : {
        include : __script_include
    },

    console : {
        // exact mappings
        isVisible :   __console_is_visible,
        
        show :        __console_show,
        isLocked :    __console_is_locked,
        lock :        __console_lock,
        //var add command 
        getNumLines : __console_get_num_lines,
        getLine :     __console_get_line,
        clear :       __console_clear,
        overlayMessageMode : __console_overlay_message_mode,
        getOverlayMessageMode : __console_get_overlay_message_mode,


        // special streams        
        system  : __console_stream_system,
        info    : __console_stream_info,
        error   : __console_stream_error,
        warning : __console_stream_warning,
        

        // enums
        messageMode : {
            Standard : 0,
            Disabled : 1
        }


    }
};






sandboxe.script.include("main.js");