/**
 * @class image
 * @description
 * Class for abstracting visual data blocks.
 *
 * An Image is a list of frames, where each frame is
 * 2-dimensional matrix of 4-component RGBA colors. Every layer (or frame)
 * of an image has the same dimensions. A typical uses of multiple layers of an image
 * are tilesets and animations. In most cases, the pixel data for the image
 * is stored on the GPU. Images are essentially containers for their frames.
 * 
 */ 
function image() {

    /**
     * Gets the frame requested.
     *
     * @param {Number} i The i'th frame requested
     * @returns {frame} The frame requested
     */
    this.getFrame = function(){};




    /**
     * Number of frames that belong to the image.
     * @type {Number}
     */
    this.frameCount = 0;





    return this;
}
