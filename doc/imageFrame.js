/**
 * @class frame
 * @description
 * A 2D matrix of pixels. All data involving frames are RGBA formatted in 
 * one large array, organized from left-to-right, top-to-bottom.
 * 
 */ 
function frame() {

    /**
     * Reforms the image to have the width and height specified.
     * This destroys the previous contents of the image.
     * @param {Number} width
     * @param {Number} height
     */
    this.resize = function(width. height){};

    /**
     * Makes this current frame a copy of the given frame.
     * @param {frame} frame The frame to copy from.
     */
    this.copyFrom = function(){};

    /**
     * Retrieves the RGBA-formatted data of the image frame.
     * @returns {Array} An array of byte values for the frame.
     */
    this.getData = function(){};

    /**
     * Sets the contents of the frame to the supplied RGBA-formatted array of byte values.
     * @param {Array} An array of byte values.
     */
    this.setData = function(){};




    /**
     * Width of the frame in pixels. This is a read-only property; changing the size is only doable through resize().
     * @type {Number}
     */
    this.width = 0;

    /**
     * Height of the frame in pixels. This is a read-only property; changing the size is only doable through resize().
     * @type {Number}
     */
    this.height = 0;




    return this;
}
