/**
 * @class text2d
 * @extends component
 * @description
 * Component that can be used to draw high-quality text on-screen.
 * 
 */ 
function text2d() {

    /**
     * Returns the pixel position of the i'th character 
     * in the stored string. 
     *
     * Often, it is useful to get the extents of the the text that you wish to render.
     * This will tell you at what pixel offset from the text2d node's position the character's 
     * top-left corner will be. The first character is always (0, 0).
     * @param {Number} i The index of the character to get the position of.
     * @returns {vector} The position
     */
    this.getCharPosition = function(){};

    /**
     * Returns the bounding box dimensions
     * of the rendered text in pixels.
     * @returns {vector}
     */
    this.getDimensions = function(){};




    /**
     * Color of the text.
     * @type {color}
     */
    this.color = {};

    /**
     * The Text to display.
     * @type {String} 
     */
    this.text = "";

    /**
     * The size of the font, in "points"
     * @type {Number}
     */
    this.fontSize = 0.0;


    /**
     * See {@link sandboxe.text2d.spacingMode}
     * @type {Number} 
     */
    this.spacingMode = 0;


    /**
     * The font asset to use. See {@link snadboxe.assets.load}
     * @type {asset} 
     */
    this.font = {};


    /** 
     * The rendering mode. See {@link sandboxe.render2d.renderMode}
     * @type {Number} 
     */
     this.mode = 0;


     /**
      * Whether the shape should be drawn using the absolute positions 
      * of its geometry. If absolute, node information is ignored.
      * @type {Boolean}
      */
     this.absolute = false;


     /**
      * The transform of the shape component.
      * @type {node}
      */
     this.node = {};




    return this;
}