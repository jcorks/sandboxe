// base outline for dynaoce module
// "Revealing module pattern"




var sandboxe = {
    debug : {
        getProperties : __debug_get_properties,
        isNative : __debug_isNative,
        isFunction : __debug_isFunction
    },
    stateControl : {
        create : __state_control_create
    },
    scheduler : {
        create : __scheduler_create
    },
    
    
    
    trunk : {
        // prepares a new executable with a trunk
        //stage : __trunk_stage // stages
        //remove : __trunk_remove
        //commit :__trunk_commit
        
        //query : __trunk_query
        //clean : __trunk_clean
        
    },
    renderMesh : {
        create : __render_mesh_create,
        polygon : {
            triangle : 0,
            line : 1
        }
    },
    
    material : {
        create : __material_create,
        coreProgram : { 
            basic : 0,
            lighting : 1
        },
        
        textureSlot : {
            color : 0,
            basic : 1,
            shiny : 2
        }
    },
    
    shader : {
        create : __shader_create,
        stage : {
            vertexProcessor : 0,
            FragmentProcessor : 1
        },
        status : {
            invalid : 0,
            success : 1,
            notCompiled : 2
        }
    },
    
    mesh : {
        create : __mesh_create,
        vertexAttribute : {
            position : 0,
            normal : 1, 
            uv : 2,   
            userData : 3 
        }
    },
    renderLight : {
        create : __render_light_create,
        type : {
            point : 0,
            directional : 1
        }
    },
    camera : {
        create : __camera_create
    },
    
    graphics : {
        commit : __graphics_commit,
        draw : __graphics_draw,
        setDrawEachFrame : __graphics_set_draw_each_frame,
        getDrawEachFrame : __graphics_get_draw_each_frame,
        setEnableFiltering : __graphics_set_enable_filtering,
        
        setCamera2d : __graphics_set_camera_2d,
        setCamera3d : __graphics_set_camera_3d,
        setRenderCamera : __graphics_set_render_camera,

        getCamera2d : __graphics_get_camera_2d,
        getCamera3d : __graphics_get_camera_3d,
        getRenderCamera : __graphics_get_render_camera


    },
    
    object2d : {
        create : __object2d_create,
        drawColliders : __object2d_draw_colliders
    },

    mutator : {
        mutation : {
            constant : 0,
            linear : 1,
            quadratic : 2,
            squareRoot : 3,
            cubic : 4,
            sinudoidal : 5,
            logarithmic : 6,
            randomDistribution : 7
        },

        create : __mutator_create,
        step : __mutator_step
    },
    
    gui : {
        create : __gui_create,
        ungrabInput : __gui_ungrab_input,
        unfocus : __gui_unfocus
    },
    
    dataTable : {
        create : __data_table_create
    },
    
    text2d : {
        create : __text2d_create,
        spacingMode : {
            kerned : 0,
            monospace : 1,
            bitmap : 2
        }
    },
    
    clock : {
        create : __clock_create
    },
    
    shape2d : {
        create : __shape2d_create
    },
    
    color : {
        create : __color_create
    },
    
    byteArray : {
        create : __byte_array_create
    },
    
    assets : {
        type : {
            image : 1,
            font : 2,        
            audio : 3,          
            sequence : 4,       
            particle : 5,       
            rawData : 6,      
            model : 7,          
            noType : 8
        },
        
        load : __assets_load,
        loadFromBuffer : __assets_load_from_buffer,
        supportedLoadExtensions : __assets_supported_load_extensions,
        supportedWriteExtensions : __assets_supported_write_extensions,
        query : __assets_query,
        new : __assets_new
    },
    
    input : {
        // Keyboard inputs
        key_0 : -1, ///< 0
        key_1 : 1, ///< 1
        key_2 : 2, ///< 2
        key_3 : 3, ///< 3
        key_4 : 4, ///< 4
        key_5 : 5, ///< 5
        key_6 : 6, ///< 6
        key_7 : 7, ///< 7
        key_8 : 8, ///< 8
        key_9 : 9, ///< 9
        key_a : 10, ///< a
        key_b : 11, ///< b
        key_c : 12, ///< c
        key_d : 13, ///< d
        key_e : 14, ///< e
        key_f : 15, ///< f
        key_g : 16, ///< g
        key_h : 17, ///< h
        key_i : 18, ///< i
        key_j : 19, ///< j
        key_k : 20, ///< k
        key_l : 21, ///< l
        key_m : 22, ///< m
        key_n : 23, ///< n
        key_o : 24, ///< o
        key_p : 25, ///< p
        key_q : 26, ///< q
        key_r : 27, ///< r
        key_s : 28, ///< s
        key_t : 29, ///< t
        key_u : 30, ///< u
        key_v : 31, ///< v
        key_w : 32, ///< w
        key_x : 33, ///< x
        key_y : 34, ///< y
        key_z : 35, ///< z
        key_lshift : 36, ///< Left shift key
        key_rshift : 37, ///< Right shift key
        key_lctrl : 38,  ///< Left control key
        key_rctrl : 39,  ///< Right control key
        key_lalt : 40,   ///< Left alt key
        key_ralt : 41,   ///< Right alt key
        key_tab : 42,    ///< Tab
        key_F1 : 43,     ///< F1
        key_F2 : 44,     ///< F2
        key_F3 : 45,     ///< F3
        key_F4 : 46,     ///< F4
        key_F5 : 47,     ///< F5
        key_F6 : 48,     ///< F6
        key_F7 : 49,     ///< F7
        key_F8 : 50,     ///< F8
        key_F9 : 51,     ///< F9
        key_F10 : 52,    ///< F10
        key_F11 : 53,    ///< F11
        key_F12 : 54,    ///< F12
        key_up : 55,     ///< Up arrow
        key_down : 56,   ///< Down arrow
        key_left : 57,   ///< Left arrow
        key_right : 58,  ///< Right arrow
        key_minus : 59,  ///< -
        key_equal : 60,  ///< : 
        key_backspace : 61,  ///< Backspace
        key_grave : 62,  ///< `
        key_esc : 63,    ///< Escape
        key_home : 64,   ///< Home key
        key_pageUp : 65, ///< Page up key
        key_pageDown : 66,  ///< Page down key
        key_end : 67,    ///< End key
        key_backslash : 68, ///< '\'
        key_lbracket : 69, ///< [
        key_rbracket : 70, ///< ]
        key_semicolon : 71, ///< ;
        key_apostrophe : 72, ///< '
        key_frontslash : 73, ///< /
        key_enter : 74, ///< Enter
        key_delete : 75, ///< Delete
        key_numpad0 : 76, ///< Numpad 0
        key_numpad1 : 77, ///< Numpad 1
        key_numpad2 : 78, ///< Numpad 2
        key_numpad3 : 79, ///< Numpad 3
        key_numpad4 : 80, ///< Numpad 4
        key_numpad5 : 81, ///< Numpad 5
        key_numpad6 : 82, ///< Numpad 6
        key_numpad7 : 83, ///< Numpad 7
        key_numpad8 : 84, ///< Numpad 8
        key_numpad9 : 85, ///< Numpad 9
        key_prtscr : 86, ///< Print screen button
        key_lsuper : 87, ///< Left Super key (Windows key)
        key_rsuper : 88, ///< Right Super key (Windows key)
        key_space : 89,  ///< Space
        key_insert : 90, ///< Insert key
        key_comma : 91, ///< ,
        key_period : 92, ///< .
        ///
        ///
        mouse_left : 93,
        mouse_right : 94,
        mouse_middle : 95,
        ///
        ///
        mouseAxis_x : 96,
        mouseAxis_y : 97,
        mouseAxis_wheel : 98,
        ///
        ///
        // Pad buttons
        pad_b0 : 100, ///< Button 0
        pad_b1 : 101, ///< Button 1
        pad_b2 : 102, ///< Button 2
        pad_b3 : 103, ///< Button 3
        pad_b4 : 104,///< Button 4
        pad_b5 : 105,///< Button 5
        pad_b6 : 106,///< Button 6
        pad_b7 : 107,///< Button 7
        pad_b8 : 108,///< Button 8
        pad_b9 : 109,///< Button 9
        pad_b10 : 110,///< Button 10
        pad_b11 : 111,    ///< Button 11
        pad_b12 : 112,///< Button 12
        pad_b13 : 113,///< Button 13
        pad_b14 : 114,///< Button 14
        pad_b15 : 115,///< Button 15
        pad_b16 : 116,///< Button 16
        pad_b17 : 117,///< Button 17
        pad_b18 : 118,///< Button 18
        pad_b19 : 119,///< Button 19
        pad_b20 : 120,///< Button 20
        pad_b21 : 121,///< Button 21
        pad_b22 : 122,///< Button 22
        pad_b23 : 123,///< Button 23
        pad_b24 : 124,///< Button 24
        pad_b25 : 125,///< Button 25
        pad_b26 : 126,///< Button 26
        pad_b27 : 127,///< Button 27
        pad_b28 : 128,///< Button 28
        pad_b29 : 129,///< Button 29
        pad_b30 : 130,///< Button 30
        pad_b31 : 131,///< Button 31
        pad_b32 : 132,///< Button 32


        pad_x : 133, ///< X button
        pad_y : 134, ///< Y button
        pad_z : 135,  ///< Z button
        pad_x2 : 136,///< X2 button 
        pad_y2 : 137,///< Y2 button
        pad_z2 : 138,///< Z2 button
        pad_x3 : 139,///< X3 button
        pad_y3 : 140,///< Y3 button
        pad_z3 : 141,///< Z3 button
        pad_x4 : 142,///< X4 button
        pad_y4 : 143,///< Y4 button
        pad_z4 : 144,///< Z4 button
        

        
        buttonListener : {
            create : __input_button_listener_new
        },
        
        mouseX : __input_mouse_x,
        mouseY : __input_mouse_y,
        mouseXDelta : __input_mouse_x_delta,
        mouseXDelta : __input_mouse_y_delta,
        mouseWheel : __input_mouse_wheel,
        getState : __input_get_state,
        isPressed : __input_is_pressed,
        isHeld : __input_is_held,
        isReleased : __input_is_released,
        mapInput : __input_map_input,
        unmapInput : __input_unmap_input,
        addListener : __input_add_listener
    },
    
    engine : {
        getRoot : __engine_get_root,
        setRoot : __engine_set_root,
        quit : __engine_quit,
        attachManager : __engine_attach_manager,
        setMaxFPS : __engine_set_max_fps,
        getBaseDirectory : __engine_get_base_directory,
        version : __engine_version
        
    },
    
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
        run : __script_include,
        include : function(script) {__script_include(script, 1);}
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





