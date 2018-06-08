/**
 * @class color
 * @description
 * Holds a standard RGBA value. See {@link sandboxe.color.create} to instantiate 
 * it. </br></br>
 *
 * colors are sandboxe's primitive color type. Each component holds byte values 
 * but are expressed as decimals from 0.0 (no intensity) to 1.0 (maximum intensity).
 *
 * A notable feature is that components or arguments that except colors may 
 * also accept string values as if calling {@link color.set}.
 *
 */ 
function color() {

    
    /**
     * Converts the color into a string.
     * @returns {String}
     */
    this.toString = function(){};

    /**
     * Creates a copy of this color.
     * @returns {color}
     */
    this.clone = function(){};
    
    /** 
     * Sets the color from a string value or color.
     * String values accepted can follow one of 2 formats: </br></br>
     * 1.) As a color name (see this list https://en.wikipedia.org/wiki/X11_color_names) </br>
     * 2.) As a typical hex html / css style format color (i.e. #ff00ff). Alpha channel may be included in this hex string. 
     * @param {String|color} value The new value to set.
     */
    this.set = function(value){};



    /**
     * Red component. Defined from 0.0 to 1.0
     * @type {Number}
     */
    this.r = {};

    /**
     * Green component. Defined from 0.0 to 1.0
     * @type {Number}
     */
    this.g = {};

    /**
     * Blue component. Defined from 0.0 to 1.0
     * @type {Number}
     */
    this.b = {};

    /**
     * Alpha/opacity component. Defined from 0.0 to 1.0
     * @type {Number}
     */
    this.a = {};





    /**
     * Alias for color.r
     * @type {Number}
     */
    this.red = {};

    /**
     * Alias for color.g
     * @type {Number}
     */
    this.green = {};

    /**
     * Alias for color.b
     * @type {Number}
     */
    this.blue = {};

    /**
     * Alias for color.a
     * @type {Number}
     */
    this.alpha = {};

    return this;
}