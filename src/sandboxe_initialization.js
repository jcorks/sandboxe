R"SBINITJS0(//"


 
/**
 * The sandboxe namespace.
 * @namespace 
 *
 */
var sandboxe = {
    /** 
     * Types of data specified by the native system. For use with inputBuffer 
     * and outputBuffer, for example. 
     *
     * @namespace 
     */
    type : {
        /**
         * Represents a 32bit signed integer.
         *
         */
        int : 0,
        
        /**
         * Represents an floating point value of single precision.
         *
         */
        float : 1,

        /**
         * Represents an unsigned 32bit integer.
         *
         */
        uint32 : 2,

        /**
         * Represents an unsigned 8bit integer.
         *         
         */
        byte : 3
    },
    
    
    /**
     * inputBuffer utility namespace
     * @namespace
     */
    inputBuffer : {
        /**
         * Creates a new inputBuffer object. inputBuffer objects 
         * contain utilities to help work with binary input data from 
         * files or arbitrary byte buffers.
         * @returns {inputBuffer} A new {@link inputBuffer}
         * @function
         */
        create : __input_buffer_create
    },

    /**
     * inputBuffer utility namespace
     * @namespace
     */    
    outputBuffer : {
        /**
         * Creates a new outputBuffer object. outputBuffer objects 
         * contain utilities to help work with binary output data for 
         * files or arbitrary byte buffers.
         * @returns {outputBuffer}
         * @function
         */
        create : __output_buffer_create
    },

    /**
     * particleEmitter2d utility namespace
     * @namespace
     */   
    particleEmitter2D : {
        /**
         * Creates a new particleEmitter2D, an entity that 
         * can efficiently emit particles.
         * @returns {particleEmitter2D}
         * @function
         */
        create : __particle_emitter_2d_create
    },
    /**
     * Sound and general audio utility namespace
     * @namespace
     *
     * @description 
     * Sound within the engine is output into separate channels, each of which 
     * are assembled into a waveform sent to the system. Each channel has its 
     * own volume, panning, and custom effect control, allowing for advanced audio control 
     * (i.e. independent volume for sound effects and background music.)
     */   
    sound : {

        /**
         * Returns whether the given sound file is playing.
         * @returns {boolean} 
         * @param {asset} asset The loaded sound file 
         * @function
         */
        isPlaying : __sound_is_playing,
        
        
        /**
         * Plays the given audio asset. 
         *
         * @returns {activeSound} 
         * @param {asset} asset The loaded sound asset.
         * @param {Number} channel The channel to send the audio to. Default is 0. (optional)
         * @param {Number} volume The volume multiplier to play the audio at. Default is 1.0. (optional)
         * @param {Number} panning The panning multiplier to play the audio with. 0 -> left audio device, 1-> right audio device. Default is .5. (optional)
         * @function
         */        
        playAudio : __sound_play_audio,

        /**
         * Adds an effect to the audio channel. **WARNING:** currently, effect functors are very resource intensive and 
         * may not perform well enough for most applications.
         *
         * Channel effects provide a mechnism to provide custom behavior to the raw audio that 
         * passes through a sound channel. See {@link audioBuffer}
         *
         * @param {Function} effectHandler The function to provde the custom effect. Its input is an {@link audioBuffer}
         * @param {Number} channel The channel to add this effect to.
         * @function
         */     
        channelAddEffect : __sound_channel_add_effect,
        
        /**
         * Removes all effects from a channel.
         *
         * @param {Number} channel Channel to reset.
         * @function
         */     
        channelReset : __sound_channel_reset,
        
        /**
         * Sets the volume for the channel.
         *
         * @param {Number} channel Channel to set the volume 
         * @param {Number} volume Volume to set. Default is 1.0.
         * @function
         */
        channelSetVolume : __sound_channel_set_volume,

        /**
         * Sets the panning for the channel. As with all other 
         * panning input contexts, 0.f is all the way to the left, and 1.f is all the way to the left.
         *
         * @param {Number} channel Channel to set the volume 
         * @param {Number} volume Volume to set. Default is .5
         * @function
         */
        channelSetPanning : __sound_channel_set_panning,

        /**
         * Sets whether to keep the channel awake.
         * By default, channels will only be active if there are samples playing through it 
         * This is normally fine, execpt this means effects will stop once no samples are 
         * being processed through a channel. For something like reverberation, this 
         * would cut off meaningful information from being output. Keeping the channel 
         * awake sacrifices performance for making more quality effects.
         *
         * @param {Number} channel Channel to set the volume 
         * @param {Boolean} enable Whether to keep the channel awake. By default, no channels are kept awake.
         * @function
         */
        channelKeepAwake : __sound_channel_keep_awake
    },
    /**
     * General debugging utility namespace
     * @namespace
     */   
    debug : {
        /**
         * Convenience function that returns all names of an object. 
         *
         * @param {Object} object The object to query.
         * @returns {Array} Names of properties belonging to the object as an array.
         * @function
         */
        getProperties : __debug_get_properties,

        /**
         * Returns whether an object is a native object. When native, the object's
         * functions and member accesses will trigger code internal to the sandboxe binary.
         *
         * @param {Object} object The object to query.
         * @returns {Boolean} Whether the object is a native object. 
         * @function
         */
        isNative : __debug_isNative,

        /**
         * Convenience function that reurns whether the object can be called as a function
         *
         * @param {Object} object The object to query.
         * @returns {Boolean} Whether the object is a function object. 
         * @function
         */
        isFunction : __debug_isFunction,

        /**
         * Convenience function that throws an exception if the parameter passed is not true.
         *
         * @param {Object} assertion The assertion to check   
         * @function
         */
        assert : function(assertion) {
            if (!assertion) throw 'Assertion failure.';
        }
    },

    /**
     * View (window/display) management utilities and functions.
     * @namespace
     */   
    view : {
        /**
         * Creates a new display object. See {@link display}.
         *
         * @param {String} name Optional: A name for the display. The default is "sandboxe"
         * @param {Number} width Optional: Width for the display. The default is 640
         * @param {Number} height Optional: Height for the display. The default is 480
         * @returns {display} 
         * @function
         */
        createDisplay : __view_manager_create_display,

        /**
         * Destroys a display object.
         *
         * @param {display} display Display to remove from the system.
         * @function
         */
        destroyDisplay : __view_manager_destroy_display,

        /**
         * Tells sand boxe which display to update and draw to. Once set as a main display,
         * this display will receive all update requests from the renderer. In addition,
         * sandboxe will use this display as the source of input from the user on systems 
         * where input comes form the display (i.e. WINAPI or X11).
         *
         * @param {display} display Display to set as the main.
         * @function
         */
        setMain : __view_manager_set_main,
    },
    
    
    /**
     * Collection of functions managing components in general. See {@link component}
     * @namespace
     */   
    component : {
        /**
         * Creates an emtpy component which can be customized through event handling and update functions.
         *
         * @returns {component}
         * @function
         */
        create : __component_create,

        /**
         * Functions and types general to stateControl objects. See {@link stateControl}
         *
         * @namespace 
         */
        stateControl : {
            /**
             * Creates a stateControl component, which provides state machine utilities specific to each 
             * host entity. 
             *
             * @returns {stateControl}
             * @function
             */        
            create : __state_control_create
        },

        /**
         * Functions and types general to scheduler objects. See {@link scheduler}
         *
         * @namespace 
         */
        scheduler : {
            /**
             * Creates a scheduler component, which can be used to control autonomous time events.
             *
             *
             * @returns {scheduler}
             * @function
             */
            create : __scheduler_create
        },

        /**
         * Functions and types general to renderMesh objects. See {@link renderMesh}
         *
         * @namespace 
         */
        renderMesh : {
            /**
             * Creates a renderMesh component, which can be used to render 3D geometry.
             * 
             * @returns {renderMesh}
             * @function
             */
            create : __render_mesh_create,
            
            /**
             * Primitives to use when rendering 3d vertices.
             * @namespace 
             */
            polygon : {
                /** Solid triangle */
                triangle : 0,
                
                /** 3d line */
                line : 1
            }
        },
        
        /**
         * Functions and types general to renderLight objects. See {@link renderLight}
         *
         * @namespace 
         */
        renderLight : {
            /**
             * Creates a renderLight component, which can be used to model 3D geometry lights.
             * 
             * @returns {renderLight}
             * @function
             */
            create : __render_light_create,

            /**
             * Enumerator of different types of lights.
             * 
             * @namespace
             */
            type : {
                /**
                 * When given to a renderLight as the type, the light becomes a 
                 * fixed-point type light in 3D space.
                 */
                point : 0,

                /**
                 * When given to a renderLight as the type, the light becomes a 
                 * location-independent directional light. In this case, the position 
                 * property is interpreted as a directional vector.
                 */
                directional : 1
            }
        },
        
        /**
         * Functions and types general to object2d objects. See {@link object2d}
         *
         * @namespace 
         */
        object2d : {
            /**
             * Creates an object component, which can be used to give 2d objects complex movement attributes.
             * 
             * @returns {object2d}
             * @function
             */
            create : __object2d_create,
        },

        /**
         * Functions and types general to mutator objects. See {@link mutator}
         *
         * @namespace 
         */
        mutator : {

            /**
             * Types of mutation functions
             * @namespace
             */
            mutation : {
                /** Output is a constant value */
                constant : 0,

                /** Output models a linear function */
                linear : 1,
                
                /** Output models a quadratic function */
                quadratic : 2,

                /** Output models a squareroot function */
                squareRoot : 3,

                /** Output models a cubic function */
                cubic : 4,

                /** Output models a sine wave, where input is radians into a standard sine function.*/
                sinudoidal : 5,

                /** Output models a logarithmic function. */
                logarithmic : 6,

                /** Output is random and is independent of input. */
                randomDistribution : 7
            },

            /**
             * Creates a mutator component, which can be used to complex mathematical functions useful for animations.
             * 
             * @returns {mutator}
             * @function
             */
            create : __mutator_create,
        },
        
        /**
         * Functions and types general to mutator objects. See {@link mutator}
         *
         * @namespace 
         */
        gui : {
            /**
             * Creates a gui component, which can be used to make UI objects.
             *
             * @returns {gui}
             * @function
             */
            create : __gui_create,

            /**
             * Ungrabs the input for the gui that currently owns input
             */
            ungrabInput : __gui_ungrab_input,

            /**
             * Unsets the currently focused widget. This fires the "on-unfocus" event for the component.
             *
             */
            unfocus : __gui_unfocus
        },
        /**
         * Functions and types general to dataTable objects. See {@link dataTable}
         *
         * @namespace 
         */
        dataTable : {
            /**
             * Creates a dataTable object, which can be used to store, manipulate, and import binary data.
             *
             * @returns {dataTable}
             * @function
             */
            create : __data_table_create
        },

        /**
         * Functions and types general to text2d objects. See {@link text2d}
         *
         * @namespace 
         */        
        text2d : {
            /**
             * Creates a text2d object, which can be used to display text within the entity world space.
             *
             * @returns {text2d}
             * @function
             */
            create : __text2d_create,
            /**
             * Flags for spacing modes to be used with text2d objects.
             * @namespace
             */
            spacingMode : {
                /** Attempts to produce the most natural spacing between text by taking into account any special character spacing rules determined by the font. This is the default.*/
                kerned : 0,
                /** Space among characters is distributed uniformly regardless of input text. This is typically preferred for performance and for ease of determining space usage. */
                monospace : 1,
                /** Spcifies space to be determined by the actual character extents only. This is at times useful, but may cause awkward spacing with certain fonts.*/
                bitmap : 2
            }
        },

        /**
         * Functions and types general to clock objects. See {@link clock}
         *
         * @namespace 
         */                
        clock : {
            /**
             * Creates a clock object, which can be used to keep track of timing-based events on a basic level.
             *
             * @returns {clock}
             * @function
             */
            create : __clock_create
        },
        
        /**
         * Functions and types general to shape2d objects. See {@link shape2d}
         *
         * @namespace 
         */                
        shape2d : {
            /**
             * Creates a shape2d component, which can be used to render 2d shapes.
             *
             * @returns {shape2d}
             * @function
             */
            create : __shape2d_create
        },
    },

    
    /**
     * @namespace
     *
     * @description
     * Functions to work with the trunk, allowing for packing assets into binaries. </br>
     *  
     * The trunk is a conceptual means by which you can store assets for your project 
     * to be bundled with an executable. Using the trunk, you can create copies of the 
     * sandboxe binary with files packed into the binary. When trunk assets are added
     * they are automatically looked for when doing an action that would normally 
     * check the disk. </br></br>
     * 
     * It's important to note that this process doesn't actually modify the currently 
     * running executable, but instead allows to create a new executable with the parameters you set. </br></br>
     * 
     * The usual process of using the trunk is like so:
     * <pre>
     * 1. stage() the files to be included
     * 2. commit() the files to produce a new binary 
     * </pre>
     *
     * Then when running the new binary, there's no need to change any code. 
     * The normal routines that look for disk objects (i.e. {@link sandboxe.assets}) will 
     * automatically search objects in the trunk for a match based on its original path 
     * before defaulting to the disk. The new binary's trunk can always be checked using 
     * {@link sandboxe.trunk.getItemNames()}.
     *
     * For example:
     * @example
     *
     * // Stages the image for a new binary.
     * sandboxe.trunk.stage('/path/to/myImage.png');
     * // create new binary.
     * sandboxe.trunk.commit('/path/to/new/binary');
     * 
     *
     */
    trunk : {
        /** 
         * Adds the specified file to list of files to add to the trunk. 
         * @param {String} path The path to the file you wish to commit to the trunk.
         * @function
         */
        stage : __trunk_stage, // stages
        
        /**
         * Removes the given path from the stages files within the trunk. Note that 
         * this does not remove files from this binary's trun; only the stages 
         * file reference is removed.
         * @param {String} path The path to remove from the staged file list.
         * @function
         */
        remove : __trunk_remove,

        /**
         * Creates a new binary that is a copy of this one, except its trunk 
         * consists of the files added with {@link sandboxe.trunk.stage()}. 
         * If any file is not found, the export fails.
         * @returns {String} A status message is returned giving info if unsuccessful. If successful, the string is returned is empty.
         * @function
         */
        commit :__trunk_commit,
        

        /**
         * Returns a list of the currently stages files.
         * @returns {Array} Array of strings with the names given for each staging call.
         * @function
         */
        query : __trunk_query,

        /**
         * Removes all stages file names for commit. Note that this doesnt actually touch any files, just removes the effects of staging it
         * @function
         */        
        clear : __trunk_clear,
        
        /**
        * Returns an array of all files added to the trunk from the commit() call that 
        * created this binary. For any file action whose path equals a name on this list, the 
        * internal binary data packed in the trunk will be used instead of looking for an on-disk file.
        *
        * @function
        * @returns {Array} List of files in the trunk
         */
        getItemNames : __trunk_get_item_names
    },


    /**
     * @namespace
     * @description 
     * Collection of functions to work with {@link material}s.
     */
    material : {
        /**
         * Creates a new material object, needed for working with 3D renderings.
         * See {@link renderMesh} and {@link mesh}. 
         * @returns {material}
         * @function
         */
        create : __material_create,
        
        /**
         * Built-in programs for the program property of a material.
         * These are to be used if no user shader programs are provided.
         * @namespace
         */
        coreProgram : { 
            /** Default material. No lighting. The color is determined by the Ambient color.*/
            basic : 0,
            
            /** Lighting material. The lighting shader is guaranteed to follow and Phong-like shading model.*/
            lighting : 1
        },

        /**
         * Slots to specify input image references as texture slots for a material.
         * @namespace
         */
        textureSlot : {
            
            /** Interprets the texture as an RGBA texture. */
            color : 0,
            
            /** Interprets the texture as a normal map. Each 4-pixel component is interpreted as a normal vector, using rgb saturation values as xyz directions respectively. The alpha component is ignored. */
            basic : 1,
            
            /** Interprets the texture as a shiny map. Each red component of each 4-pixel is interpreted as a shiny value. The bga values are ignored. */
            shiny : 2
        }
    },
    
    /** 
     * @namespace 
     * @description 
     * Collection of references to work with {@link shader} objects.
     */
    shader : {
        /**
         * Creates a new shader object, which allows for custom rendering using materials and 3d objects.
         * @returns {shader} 
         * @function
         */
        create : __shader_create,

        /**
         * Flags for the shader stage. 
         * @namespace
         */
        stage : {
            /** First stage of the shader. Processes each vertex */
            vertexProcessor : 0,

            /** Next stage of the shader. Processes each fragment (pixel in the output framebuffer) */
            fragmentProcessor : 1
        },
        
        /**
         * Flags for the status of a shader compilation.
         * @namespace
         */
        status : {
            /** compile() was called, but the compilation failed. AddStage() and Copmile() may be called again to fix the bad stage(s). */
            invalid : 0,
            /** compile() was successful and the Shader may be used in rendering. See Material. */
            success : 1,
            /** compile() has not yet been called. */
            notCompiled : 2
        }
    },
    
    
    /** 
     * @namespace 
     * @description 
     * Collection of functions and references to work with {@link mesh} objects.
     */
    mesh : {
        /**
         * Creates a new mesh object, which hold raw 3d data to be given to {@link renderMesh} components for drawing. 
         * @returns {mesh}
         * @function
         */
        create : __mesh_create,
        
        /** 
         * Denotation of vertex data type.
         * @namespace
         */
        vertexAttribute : {
            /** Position of the vertex. 3 components: xyz. */
            position : 0,

            /** he normal vector of the vertex. 3 components: xyz. */
            normal : 1, 
            
            /** The texture cooridates of the vertex. 2 components: xy. */
            uv : 2,   
            
            /** User-defined data. 3 components: xyz. */
            userData : 3 
        },
        
        /** 
         * Returns a pre-build mesh representing a cube.
         * @returns {mesh} A newly made mesh.
         * @function
         */
        createCube : __mesh_create_cube,

        /** 
         * Returns a pre-build mesh representing a flat square.
         * @returns {mesh} A newly made mesh.
         * @function
         */
        createSquare : __mesh_create_square

    },

    /**
     * @namespace 
     * @description 
     * Functions for working with {@link camera} entities.
     */
    camera : {
        /** 
         * Creates a new camera entity, which are necessary for 2d and 3d rendering 
         * See {@link sandboxe.graphics} for more details in usage.
         * @returns {camera} 
         * @function
         */
        create : __camera_create
    },
    
    
    /** 
     * @namespace 
     * @description 
     *
     * Functions for working with rendering setup and actions.
     * Note that most rendering actions are done through components 
     * such as {@link shape2d} or {@link renderMesh}. 
     */
    graphics : {
        
        /** 
         * Forces the rendered scene to be drawn on the screen. This is normally done for you.
         * @function
         */
        commit : __graphics_commit,

        /** 
         * Draws an object to the current display. This is normally done for you automatically 
         * by attaching copmonents and having the host entity as part of the main entity tree.
         * @param {shape2d|renderMesh} object The object to draw.
         * @function
         */
        draw : __graphics_draw,

        /**
         * Sets whether or not to automatically draw, commit, and clear.
         * @param {boolean}
         * @function
         */
        setDrawEachFrame : __graphics_set_draw_each_frame,
        /**
         *  whether each frame is being drawn, updated, and swapped automatically by sandboxe or not.
         * @returns {boolean}
         * @function
         */
        getDrawEachFrame : __graphics_get_draw_each_frame,

        /**
         * Disables or enables bilinear filtering of Images during rendering.
         * Bilinear filtering makes stratched images look less grainy.
         * The default is not to enable
         * @param {boolean}
         * @function
         */
        setEnableFiltering : __graphics_set_enable_filtering,


        /** 
         * Sets the current camera to view from for 2D renderings.
         * If invalid, the current camera is not changed.
         * @param {camera}
         * @function
         */
        setCamera2d : __graphics_set_camera_2d,

        /**
         * Sets the current camera to view from for 3D renderings.
         * If invalid, the current camera is not changed.
         * @param {camera}
         * @function
         */
        setCamera3d : __graphics_set_camera_3d,

        /**
         * Sets the current camera that processes all visuals and hands them to the display i.e. the window.
         *  If invalid, the current camera is not changed.
         * @param {camera}
         * @function
         */
        setRenderCamera : __graphics_set_render_camera,



        /** 
         * Returns the current 2d camera object. 
         * @returns {camera}
         * @function
         */
        getCamera2d : __graphics_get_camera_2d,

        /** 
         * Returns the current 3d camera object. 
         * @returns {camera}
         * @function
         */
        getCamera3d : __graphics_get_camera_3d,

        /** 
         * Returns the current render camera object. 
         * @returns {camera}
         * @function
         */
        getRenderCamera : __graphics_get_render_camera


    },
    

    /**
     * @namespace 
     * @description 
     * Functions to work with {@link color} objects
     * 
     */
    color : {
        /**
         * Creates a new RGBA color object.
         * @param {string|number} param If the first parameter is alone, it is interpreted as a string. When the parameter is a string, the color can be initialized in 2 ways. If the string starts with a '#' character, the color is attempted to be instantiated using the typical hex html / css style color formatting. Alpha channel may be included in this hex string. If the string does not start with #, the color is attempted to be initialized by name. All of the X11 standard colors are recognized. if the first parameter is not a string, it is interpreted as a floating point for the red component.
         * @param {number} green green value as a decimal. 0.f to 1.f.
         * @param {number} blue Blue value as a decimal. 0.f to 1.f.
         * @param {number} alpha Alpha value as a decimal. 0.f to 1.f.
         * @returns {color}
         * @function
         */         
        create : __color_create
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


        
        buttonListener : {
            create : __input_button_listener_new
        },
        
        mouseX : __input_mouse_x,
        mouseY : __input_mouse_y,
        mouseXDelta : __input_mouse_x_delta,
        mouseYDelta : __input_mouse_y_delta,
        mouseWheel : __input_mouse_wheel,
        getState : __input_get_state,
        isPressed : __input_is_pressed,
        isHeld : __input_is_held,
        isReleased : __input_is_released,
        mapInput : __input_map_input,
        unmapInput : __input_unmap_input,
        getLastUnicode : __input_get_last_unicode
    },
    
    /**
     * @namespace 
     * @description 
     * Collection of fuctions to work with the engine in general 
     */
    engine : {
        /**
         * @function 
         * Gets the current entity that is set as the root. See {@link sandbose.engine.setRoot}.
         * @returns {entity}
         */
        getRoot : __engine_get_root,

        /**
         * @function 
         * Sets the root of the entity hierarchy.
         * For normal, automatic updating of an entity by the engine, an entity needs to be 
         * either the root of the hierarchy or a child within the hierarchy. 
         * Once this is the case, the stepping and drawing behavior for entities will be 
         * called at regular intervals. Once in the hierarchy, the entity may also be
         * inspected through the runtime debugger (F3).
         * @param {entity} root The new root of the emtity hierarchy.
         */
        setRoot : __engine_set_root,


        /**
         * @function 
         * Terminates the program.
         */
        quit : __engine_quit,

        /**
        * @function
         * Attaches a manager-type entity to the engine.
         *
         */
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


    
    script : {
        run : __script_include,
        include : function(script) {__script_include(script, 1);}
    },

    /**
     * The Console namespace.
     * @memberof sandboxe
     * @namespace 
     * 
     */
    console : {
        // exact mappings
        /**
         * Returns whether the console is currently visible
         * @memberof sandboxe.console
         * @returns {boolean} 
         */
        isVisible : function(){},
    
        /** 
         * Sets whether to show the console. 
         * The console is also showable through the keyboard shortcut Shift+Tab
         *
         * @memberof sandboxe.console
         * @param {boolean} showConsole  If true, shows the console; if false, hides it.
         */
        show : function(showConsole){},

        /**
         * Returns whether the console is locked. If locked, the console cannot 
         * be shown or hidden through either the keyboard shortcut or the showConsole 
         * function.
         * @memberof sandboxe.console
         * @returns {boolean} 
         */
        isLockedfunction : function(){},

        /** 
         * Returns whether to lock or unlock the console.
         * The default is false.
         *
         * @memberof sandboxe.console
         * @param {boolean} lockConsole If true, the console is locked (see isLocked)
         */ 
        lock : function(lockConsole){},
        
        
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


    },
    
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
    key_backslash : 68, ///< ''
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
    pad_z4 : 144, ///< Z4 button


    ease : __mutator_step

};




//")SBINITJS0";


