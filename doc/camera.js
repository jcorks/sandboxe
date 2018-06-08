/**
 * @class camera
 * @extends entity
 * @description
 * A rendering target and manipulation object.
 *
 * The camera is the symbolic viewing port for sandboxe.
 * It acts as the bridge between the rendered scene and the viewer.
 * Any number of cameras can be maintained, but only one may be used at a time.
 * See {@link sandboxe.graphics.setCamera2d}
 * ,{@link sandboxe.graphics.setCamera3d}
 * ,{@link sandboxe.graphics.setRenderCamera}
 * 
 *
 */ 
function camera() {

    /**
     * Forces clearing of the results of drawing stored within the Camera.
     */
    this.refresh = function(){};


    /**
     * Sets the camera's facing target. When called, the camera will orient itseld
     * so that the center of its view "looks" at the given position.
     * @param {vector} pos Position to look at
     */
    this.setTarget = function(pos){};


    /**
     * Sets the width and height of the camer'as internal framebuffer. The frameuffer 
     * is effectively the image representing the results of drawing operations.
     * @param {Number} width The new width in device units.
     * @param {Number} height The new height in device units.
     */
    this.setRenderResolution = function(width, height){};


    /**
     * Converts a point representing a pixel on a display to
     * a point in world space..
     *
     * @param {vector} pointScreen The point to convert.
     * @param {Number} disance The distance to project the Vector to. In the case of a 3D perspective camera: Since the source is 2D, the
     * Z value is ignored. However, when projecting, since there is no source Z value,
     * The actual depth from the Camera's point of view is undefined when projecting,
     * so a distance from the viewpoint is needed.
     */
    this.transformScreenToWorld = function(pointScreen, distance){};

    /**
     * Converts a point in transformed space to a pixel position on the camera's framebuffer.
     *
     * @param {vector} point The source point to project onto the camera.
     */
    this.transformWorldToScreen = function(point){};


    /**
     * Width of the camera's output framebuffer
     * @type {Number}
     */
    this.width = 0;


    /**
     * Height of the camera's output framebuffer
     * @type {Number}
     */
    this.height = 0;

    /**
     * Type of the camera. See {@link sandboxe.camera.type}.
     * @type {Number}
     */
    this.type = 0;


    /**
     * Whether the engine should handle clearing the framebuffer for you when 
     * using this camer as a render target. Unless you're doing something very special,
     * the default of 'true' is good.
     * @type {Boolean}
     */
    this.autoRefresh = 0;

    
     
    return this;
}