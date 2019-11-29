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
         * Convenience function that throws an exception if the parameter passed is not true.
         *
         * @param {Object} assertion The assertion to check   
         * @function
         */
        assert : function(assertion) {
            if (!assertion) debugger;
        },



    },

    /**
     * Display management utilities and functions.
     * @namespace
     */   
    display : {
        /**
         * Creates a new display object. See {@link display}.
         *
         * @param {String} name Optional: A name for the display. The default is "sandboxe"
         * @param {Number} width Optional: Width for the display. The default is 640
         * @param {Number} height Optional: Height for the display. The default is 480
         * @returns {display} 
         * @function
         */
        create : __display_create,

        /**
         * Convenience function: equavalent to creating a display and setting it as the main display. See {@link display}.
         *
         * @param {String} name Optional: A name for the display. The default is "sandboxe"
         * @param {Number} width Optional: Width for the display. The default is 640
         * @param {Number} height Optional: Height for the display. The default is 480
         * @returns {display} 
         * @function
         */
        createMain : function(name, w, h) {var d=__display_create(name, w, h); __display_set_main(d); return d;},

        /**
         * Destroys a display object.
         *
         * @param {display} display Display to remove from the system.
         * @function
         */
        destroy : __display_destroy,

        /**
         * Tells sandboxe which display to update and draw to. Once set as a main display,
         * this display will receive all update requests from the renderer. In addition,
         * sandboxe will use this display as the source of input from the user on systems 
         * where input comes form the display (i.e. WINAPI or X11).
         *
         * @param {display} display Display to set as the main.
         * @function
         */
        setMain : __display_set_main,
        
        /**
         * Returns the current main display for sandboxe in use, if any.
         *
         * @returns {display}
         * @function
        
         * Tells sandboxe which display to update and draw to. Once set as a main display,
         * this display will receive all update requests from the renderer. In addition,
         * sandboxe will use this display as the source of input from the user on systems 
         * where input comes form the display (i.e. WINAPI or X11).
         *
         * @param {display} display Display to set as the main.
         * @function
         */
        setMain : __display_set_main,
        
        /**
         * Returns the current main display for sandboxe in use, if any.
         *
         * @returns {display}
         * @function
         */
        getMain : __display_get_main,


        /**
         * Returns the current string contents of the system/ current display's clipboard, if applicable.
         * On systems where the clipbaord is either inaccessible, unavailable, or does not 
         * exits, an empty string is returned.
         * 
         * @returns {String}
         * @function
         */
        getClipboard : __display_get_clipboard,


        /**
         * Attempts to set clipboard data of the current system / current dusplay's clipboard.
         * The setting of the clipboard cant be guaranteed.
         * 
         * @param {String}
         * @function
         */
        setClipboard : __display_set_clipboard,

        
        /**
         * View policy for {@link display.setViewPolicy}.
         * @namespace 
         */
        viewPolicy : {
            /**
             * The display will show the attached framebuffer's contents with no transformation
             */
            noPolicy : 0,      

            /**
             * The display will stretch the attached framebuffer's contents to match the windows dimensions
             */
            matchSize : 1
        },
        
        
        /**
         * The standard functional capabilities of a Display.
         * @namespace
         */
        capability : {
            /**
             * The display can be resized.
             */
            canResize : 0,

            /**
             * The display's position can be moved.
             */
            canMove : 1,        

            /**
             * The display's size can consume the entire physical device, often in a special state.
             */
            canFullscreen : 2,

            /**
             * The display can be hidden.
             */
            canHide : 3, 

            /**
             * The display can prevent the user from changing the dimensions of the display.
             */
            canLockSize : 4 
        }
    },
    
    
    /**
     * Collection of functions managing components in general. See {@link component}
     * @namespace
     */   
    component : {

        /**
         * @namespace 
         * @description 
         * Component type do be passed to the addComponent function.
         */
        type : {
            /**  Adds a generic component object to the entity. See {@link component} */
            object : 0,
         
            /**  Adds a clock/timer component to the entity. See {@link clock}*/
            clock : 1,

            /**  Adds a data storage object to the entity. See {@link dataTable}*/
            dataTable : 2,

            /**  Adds a gui-helper object to the entity. See {@link gui}*/
            gui : 3,

            /**  Adds an easing function object to the entity. See {@link mutator}*/
            mutator : 4,

            /**  Adds a 2D collision and movement helper to the entity. See {@link object2d} */
            object2d : 5,

            /**  Adds a 3D lighting component to the entity. See {@link renderLight}*/
            renderLight : 6,

            /**  Adds a 3D mesh renderer component to the entity. See {@link renderMesh}*/
            renderMesh : 7,

            /**  Adds a timed function manager component to the entity. See {@link scheduler}*/
            scheduler : 8,

            /**  Adds a 2D rendering component to the entity. See {@link shape2d}*/
            shape2d : 9,

            /**  Adds a state machine to the entity. See {@link stateControl}*/
            stateControl : 10,

            /**  Adds a 2D text rendering component to the entity. {See @link text2d}*/
            text2d : 11


        },


        /**
         * Functions and types general to renderMesh objects. See {@link renderMesh}
         *
         * @namespace 
         */
        renderMesh : {
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

        },
        
        /**
         * Functions and types general to mutator objects. See {@link mutator}
         *
         * @namespace 
         */
        gui : {
            /**
             * Ungrabs the input for the gui that currently owns input
             * @function
             */
            ungrabInput : __gui_ungrab_input,

            /**
             * Unsets the currently focused widget. This fires the "on-unfocus" event for the component.
             * @function
             */
            unfocus : __gui_unfocus
        },


        /**
         * Functions and types general to text2d objects. See {@link text2d}
         *
         * @namespace 
         */        
        text2d : {

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
         * Functions and types general to object2d objects. See {@link object2d}
         *
         * @namespace 
         */        
        object2d : {

            /**
             * Group IDs for collisions. See {@link object2d}
             * @namespace
             */
            group : {
                /** Group A. This is the defult. */
                a : 0,
                /** Group B. */
                b : 1,
                /** Group C. */
                c : 2,
                /** Group D. */
                d : 3,
                /** Group E. */
                e : 4,
                /** Group F. */
                f : 5,
                /** Group G. */
                g : 6,
                /** Group H. */
                h : 7,
                /** Group I. */
                i : 8,
                /** Group J. */
                j : 9,
                /** Group K. */
                k : 10,
                /** Group L. */
                l : 11,
                /** Group M. */
                m : 12,
                /** Group N. */
                n : 13,
                /** Group O. */
                o : 14,
                /** Group P. */
                p : 15,
                /** Group Q. */
                q : 16,
                /** Group R. */
                r : 17,
                /** Group S. */
                s : 18,
                /** Group T. */
                t : 19,
                /** Group U. */
                u : 20,
                /** Group V. */
                v : 21,
                /** Group W. */
                w : 22,
                /** Group X. */
                x : 23,
                /** Group Y. */
                y : 24,
                /** Group Z. */
                z : 25


            }
        },
        
        
        
        /**
         * Functions and types general to 2D rendering objects. See {@link text2d} and {@link shape2d}.
         *
         * @namespace 
         */        
        render2d : {
            /**
             * Flags for rendering modes
             * @namespace
             */
            renderMode : {
                /** This is the default. Colors are interpreted as you would normally expect with the alpha channle being expressed as a transparency value.*/
                normal : 0,
            
                /** Ignores all transparency */
                opaque : 1,

                /** Translucency is a way of expressing transparency. When a rasterization is translucent, the vertices colors are added to whatever is drawn underneath it. This is referred to in some places as additive blending. */
                translucent : 2,

                /** Ignores all color output. Etching information will still be output if applicable */
                none : 3,

            },



            /**
             * Flags for etching modes. Etching allwos for defining regions where 2D visuals are allowed to be displayed. These regions are defined by rendering with "etchMode.define". Once regions are defined, using the "etchMode.in" flag will only allow that rendering to appear in the defined regions.
             * @namespace
             */
            etchMode : {

                /** This is the default. Etching is ignored entirely.*/
                ignore : 0,
            
                /** Defines an etching region. Note that visual information may still be displayed. */
                define : 1,

                /** Reverts a region back to a non-defined etching space, undoing an etched region.*/
                undefine : 2,
        
                /** Only shows rendering results of pixels that fall within a defined etch region. */
                in : 3,

                /** Only shows rendering results of pixels that fall outside a defined etch region. */                
                out : 4
            },

 
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
        getItemNames : __trunk_get_item_names,
        
        /**
        * Stages all trunk items that existed at the creation of this binary.
        *
        * @function 
        */
        inherit : __trunk_inherit
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
         * @param {string|number} param If the first parameter is alone, it is interpreted as a string as if calling {@link color.set}. If not alone, it is a decimal for the red component. 
         * @param {number} green green value as a decimal. 0.f to 1.f.
         * @param {number} blue Blue value as a decimal. 0.f to 1.f.
         * @param {number} alpha Alpha value as a decimal. 0.f to 1.f.
         * @returns {color}
         * @function
         */         
        create : __color_create
    },
    

    /**
     * @namespace 
     * @description 
     * Functions and references to assist in storing external or binary assets. 
     */
    assets : {
        
        /**
         * @namespace 
         * Types of assets  
         */
        type : {
            /** An image object */
            image : 1,
            
            /** A font object */
            font : 2,        
            
            /** An audio object */
            audio : 3,          
            
            /** A sequence type object. Currently unavailable. */
            sequence : 4,       
            
            /** A particle specification type object */
            particle : 5,       

            /** Unspecified binary data */
            rawData : 6,      
            
            /** A model object */
            model : 7,          
            
            /** Not a type */
            noType : 8
        },


        /** 
         * Retrieves an asset object by name or disk path.
         * @param {String} extension The standard extension of the file. For example 'png' would be for PNG images. 
         * @param {String} path The path or name of the asset. If the path refers to a stored name within the trunk, raw data referring to the asset is used from within the binary and the disk is not otherwise accessed. If the asset has been loaded before using this function, the same asset reference is returned and a new one is NOT created. In the case that this argument is true and the name is not in the trunk, the disk is searched recursively from the path set from {@link sandboxe.assets.setSearchPath}. By default this is the binary directory.
         * @param {Boolean} isName Optional. Says whether the path given is a filename only or a full path. If filename, the file will be searched recursively from the search path. Otherwise, the file is looked for directly.
         * @returns {asset} Reference to the asset.
         * @function 
         */
        load : __assets_load,


        /**
         * Loads an asset form raw binary data.
         * @param {String} extension The standard extension of the file. For example 'png' would be for PNG images. 
         * @param {String} name The name of the asset. Preferrably should be unique.
         * @param {Array} bytes An array of byte values to be interpreted as a byte stream.
         * @returns {asset} Reference to the asset.
         * @function 
         */
        loadFromBuffer : __assets_load_from_buffer,
        
        
        /**
         * Returns all supported extension strings for loading the given asset type.
         * @param {Number} type The type of asset to get extensions for. See {@link sandboxe.assets.type}
         * @returns {Array} The names of supported extention types.
         * @function
         */
        supportedLoadExtensions : __assets_supported_load_extensions,

        /**
         * Returns all supported extension strings for writing the given asset type.
         * @param {Number} type The type of asset to get extensions for. See {@link sandboxe.assets.type}
         * @returns {Array} The names of supported extention types.
         * @function
         */
        supportedWriteExtensions : __assets_supported_write_extensions,


        /**
         * Returns the asset of the given type and name, if any.
         * @param {Number} type The type of the asset to query. See {@link sandboxe.assets.type}
         * @param {String} name The name / path of the asset provided when loading it.
         * @returns {asset} The asset queried. If none, return undefined.
         * @function
         */
        query : __assets_query,


        /**
         * Sets the base search path for loading assets. The default is sandboxe.engine.getBaseDirectory().
         * @param {String} path The path to set as the searching root. See {@link sandboxe.assets.load}.
         * @function
         */
        setSearchPath : __assets_set_search_path,

        /**
         * Gets the base search path for loading assets. The default is sandboxe.engine.getBaseDirectory().
         * @returns {String} The path set as the searching root. See {@link sandboxe.assets.load}.
         * @function
         */
        getSearchPath : __assets_get_search_path,

        
        
        /**
         * Creates a new asset.
         * @param {Number} type The type of th enew asset. See {@link sandboxe.assets.type}
         * @param {String} name The name of the new asset. Preferrably should be unique.
         * @returns {asset} The new asset to be created.
         * @function
         */
        create : __assets_new
    },
    
    
    
    /**
     * @namespace 
     * @description 
     * Collection of functions and references to work with input form the system.
     */
    input : {


        /**
         * Creates a new inputListener object, which are used to call methods after certain inputs are detected. This is specifically for keyboard events.
         * @returns {inputListener}
         * @function
         */
        addKeyListener : __input_key_listener_new,

        /**
         * Creates a new inputListener object, which are used to call methods after certain inputs are detected. This is specifically for mouse/pointer events.
         * @returns {inputListener}
         * @function
         */
        addPointerListener : __input_pointer_listener_new,

        /**
         * Creates a new inputListener object, which are used to call methods after certain inputs are detected. This is specific to an auxiliary input pad.
         * @param {Number} this refers to the pad index that should be listened to.
         * @returns {inputListener}
         * @function
         */
        addPadListener : __input_pad_listener_new,


        /**
         * Creates a new inputListener object, which are used to call methods after certain inputs are detected. This is specific to a mapped input string.
         * @param {String} this should be a string to listen to.
         * @returns {inputListener}
         * @function
         */
        addMappedListener : __input_mapped_listener_new,


        
        /**
         * Creates a new unicodeListener object, which are used to call methods after characters are typed by the user keyboard.
         * @returns {unicodeListener}
         * @function
         */        
        unicodeListener : {
            create : __input_unicode_listener_new
        },


        /**
         * Sets a deadzone for a pad. If a deadzone is set, any inputs below the deadzone value in magnitude will be ignored. Normally, gamepad axis work best with a deadzone active. Once a deadzone is set, inputs for that pad are renormalized becase on the deadzone so that that full input range is expressed. 
         * @param {Number} The index of the pad 
         * @param {Number} The input to have the deadzone applied to
         * @param {Number} The deadzone value
         * @function
         */
        setDeadzone : __input_set_deadzone,

        /**
         * Returns an array of valid pand indices. These refer to physically connected / accessible auxiliary input devices. This indices can be used to modify and query specific pads.
         * @returns {Array} Array of pad IDs as integers.
         * @funciton
         */
        queryPads : __input_query_pads,

        /**
         * Returns the X position of the pointer, if any.
         * @returns {Number} X position of the pointer.
         * @function 
         */
        mouseX : __input_mouse_x,

        /**
         * Returns the Y position of the pointer, if any.
         * @returns {Number} Y position of the pointer.
         * @function 
         */
        mouseY : __input_mouse_y,
        
        
        /**
         * Returns the X position change since last update frame. 
         * @returns {Number} 
         * @function 
         */
        mouseXDelta : __input_mouse_x_delta,

        /**
         * Returns the Y position change since last update frame. 
         * @returns {Number} 
         * @function 
         */
        mouseYDelta : __input_mouse_y_delta,

        /**
         * Returns the mouse wheel's current state. 0 is for "neutral", 
         * -1 is for down, and 1 is for up.
         * @returns {Number} 
         * @function 
         */
        mouseWheel : __input_mouse_wheel,


        /**
         * Returns the active state of the input. 0 is for inactive (not pressed) 
         * 1 is for active (pressed)
         * @param {Number|String} Input The type of input to query. See {@link sandboxe} input enumerator.
         * @returns {Boolean} 
         * @function 
         */
        getState : __input_get_state,


        /**
         * Maps an input value flag to a string, allowing for more convenient querying.
         * Once a mapping has taken place, any place an input enumerator value is accepted, a string can be 
         * accepted in its place.
         * @param {String} Name 
         * @param {Number} Input Value to map to. See {@link sandboxe} input enumerator.
         * @function 
         */
        mapInput : __input_map_input,
        
        /**
         * Removes an input map by name.
         * @param {String} MappedName  
         * @function 
         */
        unmapInput : __input_unmap_input,


        /**
         * Retrieves the last unicode value typed by a user keyboard if any.
         * @returns {Number} 
         * @function 
         */
        getLastUnicode : __input_get_last_unicode,


        /**
         * Attempts to open/close a virtual keyboard on the system if available.
         * @param {Boolean} show Whether to show or hide the virtual keyboard.
         */
        showVirtualKeyboard : __input_show_virtual_keyboard
    },
    
    /**
     * @namespace 
     * @description 
     * Collection of fuctions to work with the engine in general 
     */
    engine : {
        /**
         * Gets the current entity that is set as the root. See {@link sandbose.engine.setRoot}.
         * @returns {entity}
         * @function 
         */
        getRoot : __engine_get_root,

        /**
         * Sets the root of the entity hierarchy.
         * For normal, automatic updating of an entity by the engine, an entity needs to be 
         * either the root of the hierarchy or a child within the hierarchy. 
         * Once this is the case, the stepping and drawing behavior for entities will be 
         * called at regular intervals. Once in the hierarchy, the entity may also be
         * inspected through the runtime debugger (F3).
         * @param {entity} root The new root of the emtity hierarchy.
         * @function 
         */
        setRoot : __engine_set_root,


        /**
         * Terminates the program.
         * @function 
         */
        quit : __engine_quit,

        /**
         * Attaches a manager-type entity to the engine.
         * Normally, the entity hierarchy is used for normal objects; however, 
         * sometimes it is useful to have management objects that are 
         * separate from the hierarchy. attachManager() does all the 
         * management of a given entity is if it were in the hierarchy without 
         * exposing it to hierarchy attributes (i.e. inspection in the debugger,
         * inheriting transforms, etc.)
         * @param {entity} manager The management-type entity to insert into the engine.
         * @function
         */
        attachManager : __engine_attach_manager,
        
        /** 
         * Sets the maximum update rate of the engine. The default is 60 FPS (frames per second).
         * In sandboxe, the step and frame rate are coupled.
         * @param {Number} FPS The new amount to set.
         * @function
         */
        setMaxFPS : __engine_set_max_fps,
        
        /**
         * Returns the base directory of the binary. This serves as the root path for 
         * any specified relative paths given to sandboxe. It is equivalent to the 
         * starting directory of the binary. On environments where this doesn't make sense, 
         * an empty string is returned.
         * @returns {String} The base path.
         * @function
         */
        getBaseDirectory : __engine_get_base_directory,

        /** 
         * Returns a version string for the engine.
         * @returns {String} The version.
         * @function
         */
        version : __engine_version,
        
        /**
         * Returns the total number of MS since sandboxe started.
         * @returns {Number} milliseconds since startup. Note that this is approximate.
         */       
         getTotalTime : __engine_get_total_time
    },
    
    
    /**
     * @namespace 
     * @description 
     * Collection of functions to work with the base {@link vector} object.
     */
    vector : {
        /**
         * Creates a new vector object. See {@link vector.set} for syntax.
         * @returns {vector}
         * @function
         */
        create : __vector_create_new
    },
    
    /**
     * @namespace 
     * @description 
     * Collection of functions to work with the {@link entity} object.
     */
    entity : {
        
        /**
         * Creates a new entity object, which are the base updatable 
         * extensible objects of sandboxe.
         * @returns {entity} A new entity
         * @function
         */
        create : __entity_create_default,
        
        /**
         * Returns all entities within sandboxe.
         * @returns {Array} An array of all the entities.
         * @function
         */
        getAll : __entity_get_all,
        
        
        /**
         * When entities update, an update class may be chosen for whether a 
         * child updates before, after, etc. the parent object does.
         * @namespace
         */
        updateClass : {
            /**
             * Object updates before its parent does.
             */
            before : 0,

            /**
             * Object updates after its parent does.
             */
            ater : 1
        },



    },


    /**
     * @namespace 
     * @description
     * Collection of references that work with the script side of sandboxe
     * 
     */
    script : {
        /**
         * Runs all the logic of the given file as if it were a source file.
         * This is unconditional.
         * @param {String} path Path to file. If absolute is false (which is the default), this is relative to {@link sandboxe.assets.getSearchPath}
         * @params {Boolean} absolute Optional. Whether the path given should be interpreted as relative. The default is false.
         * @function
         */
        run : function(script, b) {__script_include(script, 0, b==undefined?false:true);},
        
        /**
         * Similar to {@link sandboxe.script.run} except, a source file is only 
         * executabed the first time include() is called for that path. On subsequent calls
         * with the same path argument, no action is taken.
         * @param {String} path Path to file. This is relative to {@link sandboxe.assets.getSearchPath}
         * @params {Boolean} absolute Optional. Whether the path given should be interpreted as relative. The default is false.
         * @function
         */
        include : function(script, b) {__script_include(script, 1, b==undefined?false:true);},

        onError : function(){}
    },

    


    /**
     * @namespace 
     * @description
     * Collection of references that work with the system console.
     * 
     */
    console : {
        //var add command 
        /** 
         * Returns the number of lines of output
         * currently held by the console.
         * @returns {Number} 
         * @function
         */
        getNumLines : __console_get_num_lines,

        /** 
         * Returns the string for the i'th line, starting at 0.
         * @param {Number} i THe line to retrieve.
         * @returns {String} 
         * @function
         */
        getLine :     __console_get_line,

        /**
         * Removes all stored lines of console output.
         * @function
         */
        clear :       __console_clear,


        /**
         * Sets the overlay message mode for incoming console messages.
         * @param {Number} mode The mode to set. See {@link sandboxe.console.messageMode}.
         * @function
         */
        setOverlayMessageMode : __console_overlay_message_mode,

        /**
         * Gets the overlay message mode. THe default is sandboxe.console.messageMode.standard
         * @returns {Number} See {@link sandboxe.console.messageMode}.
         * @function
         */
        getOverlayMessageMode : __console_get_overlay_message_mode,


        /**
         * Prints console output as a system-generated message. If the overlay mode is 
         * not disabled, sending a newline (\\n) will trigger a visual.
         * @param {String} content
         * @function
         */
        system  : __console_stream_system,

        /**
         * Prints console output as a info message. If the overlay mode is 
         * not disabled, sending a newline (\\n) will trigger a visual.
         * @param {String} content
         * @function
         */
        info    : __console_stream_info,

        /**
         * Prints console output as a error message. If the overlay mode is 
         * not disabled, sending a newline (\\n) will trigger a visual.
         * @param {String} content
         * @function
         */
        error   : function() {
            __console_stream_error; debugger;
        },

        /**
         * Prints console output as a warning message. If the overlay mode is 
         * not disabled, sending a newline (\\n) will trigger a visual.
         * @param {String} content
         * @function
         */
        warning : __console_stream_warning,
        

        /**
         * @namespace 
         * @description 
         * Modes possible for the overlay windows from console output. 
         */
        messageMode : {
            /** Standard mode: each newline triggers an output box visual containing the message. */
            standard : 0,
            
            /** No output visual is generated from any console stream activity. */
            disabled : 1
        }


    },

    /**
     * @namespace 
     * @description
     * Collection of references that work with the {@link filesys} object.
     * 
     */
    filesys : {
        /**
         * Creates a new filesys object. See {@link filesys} for more details.
         * @returns {filesys}
         * @function
         */
        create : __filesys_create_new,
    },
    
    /** 0 */
    key_0 : 1, 
    
    /** 1 */
    key_1 : 2, 
    
    /** 2 */
    key_2 : 3, 
    
    /** 3 */
    key_3 : 4, 
    
    /** 4 */
    key_4 : 5, 
    
    /** 5 */
    key_5 : 6,
    
    /** 6  */
    key_6 : 7, 
    
    /** 7 */
    key_7 : 8, 
    
    /** 8 */
    key_8 : 9, 
    
    /** 9 */
    key_9 : 10, 

    /** a*/
    key_a : 11, 
    
    /** b*/
    key_b : 12, 
    
    /** c*/
    key_c : 13, 
    
    /** d*/
    key_d : 14, 
    
    /** e*/
    key_e : 15, 
    
    /** f*/
    key_f : 16, 
    
    /** g*/
    key_g : 17, 
    
    /** h*/
    key_h : 18, 

    /** i*/
    key_i : 19, 
    
    /** j*/
    key_j : 20, 
    
    /** k*/
    key_k : 21,
    
    /** l*/ 
    key_l : 22, 
    
    /** m*/
    key_m : 23, 
    
    /** n*/
    key_n : 24, 
    
    /** o*/
    key_o : 25, 
    
    /** p*/
    key_p : 26, 
    
    /** q*/
    key_q : 27, 
    
    /** r*/
    key_r : 28, 
    
    /** s*/
    key_s : 29,
    
    /** t*/ 
    key_t : 30,
    
    /** u*/ 
    key_u : 31,
    
    /** v*/ 
    key_v : 32,
    
    /** w*/ 
    key_w : 33,
    
    /** x*/ 
    key_x : 34,
    
    /** y*/ 
    key_y : 35,
    
    /** z*/ 
    key_z : 36, 
    
    /** Left shift key */
    key_lshift : 37, 
    
    /** Right shift key*/
    key_rshift : 38, 
    
    /** Left control key*/
    key_lctrl : 39, 
    
    /** Right control key*/ 
    key_rctrl : 40,  
    
    /** Left alt key*/
    key_lalt : 41,   
    
    /** Right alt key*/
    key_ralt : 42,   
    
    /** Tab*/
    key_tab : 43,    
    
    /** F1*/
    key_F1 : 44,     
    
    /** F2*/
    key_F2 : 45,     
    
    /** F3*/
    key_F3 : 46,     
    
    /** F4*/
    key_F4 : 47,     
    
    /** F5*/
    key_F5 : 48,     
    
    /** F6*/
    key_F6 : 49,    

    /** F7*/ 
    key_F7 : 50,     
    
    /** F8*/
    key_F8 : 51,     
    
    /** F9*/
    key_F9 : 52,     
    
    /** F10*/
    key_F10 : 53,    
    
    /** F11*/
    key_F11 : 54,    
    
    /** F12*/
    key_F12 : 55,    
    
    /** Up arrow*/
    key_up : 56,     
    
    /** Down arrow*/
    key_down : 57,   
    
    /** Left arrow*/
    key_left : 58,   
    
    /** Right arrow*/
    key_right : 59,  
    
    /** -*/
    key_minus : 60,  
    
    /** : */
    key_equal : 61,  
    
    /** Backspace*/
    key_backspace : 62,  
    
    /** `*/
    key_grave : 63,  
    
    /** Escape*/
    key_esc : 64,    
    
    /** Home key*/
    key_home : 65,   
    
    /** Page up key*/
    key_pageUp : 66, 
    
    /** Page down key*/
    key_pageDown : 67,  
    
    /** End key*/
    key_end : 68,    
    
    /** ''*/
    key_backslash : 69,
    
    /** [*/ 
    key_lbracket : 70, 
    
    /** ]*/
    key_rbracket : 71, 
    
    /** ;*/
    key_semicolon : 72, 
    
    /** '*/
    key_apostrophe : 73, 
    
    /** /*/
    key_frontslash : 74, 
    
    /** Enter*/
    key_enter : 75, 
    
    /** Delete*/
    key_delete : 76, 
    
    /** Numpad 0*/
    key_numpad0 : 77, 
    
    /** Numpad 1*/
    key_numpad1 : 78, 
    
    /** Numpad 2*/
    key_numpad2 : 79, 
    
    /** Numpad 3*/
    key_numpad3 : 80, 
    
    /** Numpad 4*/
    key_numpad4 : 81, 
    
    /** Numpad 5*/
    key_numpad5 : 82, 
    
    /** Numpad 6*/
    key_numpad6 : 83, 
    
    /** Numpad 7*/
    key_numpad7 : 84, 
    
    /** Numpad 8*/
    key_numpad8 : 85, 
    
    /** Numpad 9*/
    key_numpad9 : 86, 
    
    /** Print screen button*/
    key_prtscr : 87, 
    
    /** Left Super key (Windows key)*/
    key_lsuper : 88, 
    
    /** Right Super key (Windows key)*/
    key_rsuper : 89, 
    
    /** Space*/
    key_space : 90, 
    
     /** Insert key*/ 
    key_insert : 91,
    
    /** ,*/
    key_comma : 92, 
    
    /** .*/
    key_period : 93, 


    /** Mouse left button*/
    mouse_left : 94,

    /** Mouse right button*/
    mouse_right : 95,

    /** Mouse middle button*/
    mouse_middle : 96,


    /** Mouse movement X axis*/
    mouseAxis_x : 97,

    /** Mouse movement Y axis*/
    mouseAxis_y : 98,

    /** Mouse wheel axis*/
    mouseAxis_wheel : 99,


    pad_a : 100,
    pad_b : 101,
    pad_c : 102,
    pad_x : 103,
    pad_y :  104,
    pad_r :  105,
    pad_l :   106,
    pad_r2 :   107,
    pad_l2 :   108,
    pad_r3 :  109,
    pad_l3 :   110,
    pad_start :  111,
    pad_select : 112,
    pad_b13 : 113,
    pad_b14 : 114,
    pad_b15 : 115,
    pad_b16 : 116,
    pad_b17 : 117,
    pad_b18 : 118,
    pad_b19 : 119,
    pad_b20 : 120,
    pad_b21 : 121,
    pad_b22 : 122,
    pad_b23 : 123,
    pad_b24 : 124,
    pad_b25 : 125,
    pad_b26 : 126,
    pad_b27 : 127,
    pad_b28 : 128,
    pad_b29 : 129,
    pad_b30 : 130,
    pad_b31 : 131,
    pad_b32 : 132,

    pad_axisX :  133,
    pad_axisY :  134,
    pad_axisZ :  135,
    pad_axisX2 : 136,
    pad_axisY2 : 137,
    pad_axisZ2 : 138,
    pad_axisX3 : 139,
    pad_axisY3 : 140,
    pad_axisZ3 : 141,
    pad_axisX4 : 142,
    pad_axisY4 : 143,
    pad_axisZ4 : 144,
    pad_axisX5 : 145,
    pad_axisY5 : 146,
    pad_axisZ5 : 147,
    pad_axisX6 : 148,
    pad_axisY6 : 149,
    pad_axisZ6 : 150,

    pad_axisR :  151,   
    pad_axisL :  152,   
    pad_axisR2 : 153,    
    pad_axisL2 : 154,    
    pad_axisR3 : 155,    
    pad_axisL3 : 156,    
    pad_axisR4 : 157,    
    pad_axisL4 : 158,    

    pad_options : 159, 

    /** 
     * @function 
     * @description
     * A generic easing function. For more complex easing, see {@link mutator}.
     * @param {Number} Current Current value 
     * @param {Number} Destination End value 
     * @param {Number} Progress (Optional) Amount of percentage progression to that value. Default is .5f
     * @param {Number} Function (Optional) Base easing function. Default is linear. See {@link sandboxe.mutator.mutation}
     * @return {Number} New value that should replace current.
     */
    ease : __mutator_step

};
sandboxe.heap = __sandboxe_internal__heap;



//")SBINITJS0";


