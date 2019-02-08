/**
 * @class shape2d
 * @extends component
 * @description
 * Component that can express basic 2D shapes and polygons.
 * 
 */ 
function shape2d() {

    /**
     * Forms the shape into a rectangle.
     *
     * The top-left corner of the rectangle is the origin. 
     * Width and height are expressed in pixels.
     * @param {Number} width The width of the rectangle in pixels.
     * @param {Number} height The height of the rectangle in pixels.
     */
    this.formRectangle = function(){};

    /**
     *
     Forms the shape into a visual of an image.
     *
     * If the image has multiple frames, the image is drawn as
     * an animation.
     * @param {asset} image The image to display as the aspect. If image does not refer to
     * a valid Image, no action is taken. If the Image has multiple frames, the subsequent frame
     * is drawn upon next draw() of the shape2d.
     * @param {Number} forcedWidth Optional forced width 
     * @param {Number} forcedHeight Optional forced height
     */
    this.formImage = function(){};

    /**
     * Forms the aspect into a frame of an image.
     *
     * Behaves like formImage(), but a specific frame index is
     * specified to draw rather than the image as an animation.
     * @param {asset} image The image to form as the aspect. If image does not refer to
     * a valid image asset, no action is taken
     * @param {Number} frame The frame of the image to use, starting at 0. If the
     * frame is negative, the aspect is drawn as if formImage() had been called.
     * @param {Number} forcedWidth Optional forced width 
     * @param {Number} forcedHeight Optional forced height
     */
    this.formImageFrame = function(){};

    /**
     * Forms the shape into an estimated circle made of triangles.
     *
     * @param {Number} radius The radius of the circle. Measured in pixels.
     * @param {Number} numIterations Number of sides that the circle
     * should have. The more iterations, the smoother the
     * circle will become, but the more resource-intensive
     * the shape becomes as well.
     */
    this.formCircle = function(){};

    /**
     * Forms the shape into a collection of triangle primitives.
     *
     * The points are interpreted as pixels and are expected to be in groups of 3.
     * If a non-multiple-of-three number of points is given,
     * the remainder points are ignored.
     * @param {Array} pts The points of the triangles as individual components, that is, pairs of X-Y values.
     */
    this.formTriangles = function(){};

    /**
     * Forms a collection of line segments.
     *
     * Every two points form a line segment. If an odd number of points are given, the last point is ignored.
     * @param {Array} pts The points of the lines as individual components, that is, pairs of X-Y values.
     */
    this.formLines = function(){};





    /**
     * Color of the shape.
     * @type {color}
     */
    this.color = {};

    /**
     * Whether the shape should be drawn using the absolute positions 
     * of its geometry. If absolute, node information is ignored.
     * @type {Boolean}
     */
    this.absolute = false;

    /**
     * The transform of the shape component.
     * @type {transform}
     */
    this.node = {};
    
    /** 
     * The rendering mode. See {@link sandboxe.render2d.renderMode}
     * @type {Number} 
     */
     this.mode = 0;

    /** 
     * The etching mode. See {@link sandboxe.render2d.etchMode}
     * @type {Number} 
     */
     this.etch = 0;





    return this;
}
