/**
 * @class display
 * @description
 * Abstracts the system's means of displaying rendered data. Instantiates with {@link sandboxe.display.create()} </br></br>
 *
 * An interface for displaying rendered data
 *
 * 
 */ 
function display() {

    /**
     * 
     * Resizes the display. If the display does not support resizing, no action is taken.
     * @param {Number} width The new width
     * @param {Number} height The new height
     */
    this.resize = function(width, height){};

    /**
     * Sets the position of the display. 
     *
     * Usually, this is relative to whatever environment
     * the display exists in. For example, in a desktop environment, this could be
     * an offset from the DE's origin. If the display does not support moving,
     * no action is taken.
     * @param {Number} x The new x position of the display
     * @param {Number} y The new y position of the display
     */
    this.setPosition = function(x, y){};

    /**
     * Set the display into a fullscreen context. If fullscreen is not supported,
     * no action is taken.
     * @param {Boolean} fs Whether to enable or disable fullscreen
     */
    this.fullscreen = function(fs){};

    /**
     * Attempts to hide the display. If hiding is not supported, no action is taken.
     * @param {Boolean} hide Whether to hide the display
     */
    this.hide = function(){};

    /**
     * Returns whether the display has user input focus. On display implementations
     * where this doesnt apply, i.e. where there is only one logical display available,,
     * this will always return true. 
     * @returns {Boolean} Returns whether the display has input focus
     */
    this.hasInputFocus = function(){};


    /**
     * Attempts to prevent resizing on the user's side. 
     *
     * For example,
     * in a desktop environment, this would disable the feature of resizing
     * the window.
     * @param {Boolean} lock Whether to lock client resize.
     */
    this.lockClientResize = function(){};


    /**
     * Attempts to prevent moving on the user's side. 
     * @param {Boolean} lock Whether to lock client display position.
     */
    this.lockPosition = function(){};

    /**
     * Controls how the Renderer's information is displayed. The default policy is "MatchSize"
     * See ViewPolicy for more information.
     * @param {Number} viewPolicy The viewing policy. See {@link sandboxe.display.viewPolicy}.
     */
    this.setViewPolicy = function(){};

    /**
     * Sets the name of the display. On some systems, this can, for example,
     * set the title bar of the application to the specified name.
     * @param {String} name The new name.
     */
    this.setName = function(){};

    /**
     * Returns whether or not the display is able to 
     * perform the requested capability.
     * @param {Number} capability The viewing policy. See {@link sandboxe.display.capability}.
     */
    this.isCapable = function(){};



    /**
     * Width of the display
     * @type {Number}
     */
    this.width = 0;

    /**
     * Height of the display
     * @type {Number}
     */
    this.height = 0;


    /**
     * The X position of the display
     * @type {Number}
     */
    this.x = 0;

    /**
     * The Y position of the display
     * @type {Number}
     */
    this.y = 0;
    
    /**
     * Function called when a resize event is detected for the display.
     * The function is called after the event is applied.
     * @type {Function}
     */
    this.onResize = undefined;
    
    /**
     * Function called when a close event for the display is detected.
     * @type {Function}
     */
    this.onClose = undefined;



    return this;
}