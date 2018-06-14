/**
 * @class material
 * @description
 * Defines how a mesh should be visualized.
 *
 * Materials are the main way to have advanced graphics control
 * with customized behavior. With custom or built-in {@link shader} objects,
 * materials provide the data inputs to these programs allowing for dynamic 
 * visuals.
 *
 * 
 */ 
function material() {

    /**
     * Adds a texture to be drawn.
     *
     * How textures interact with the mesh is dependent on the material attached with 
     * {@link renderMesh.material}. If the material is using a {@link sandboxe.material.coreProgram}, {@link sandboxe.material.textureSlot.color} 
     * will be used as an RGBA texture, {@link sandboxe.material.textureSlot.normal} will be used as a lighting normal map,
     * and {@link sandboxe.material.textureSlot.shiny} will be used as a light reflectivity map. For user-made programs using
     * Shader, the first argument refers to what texture slot you can access the texture from in 
     * the shader programming language. Refer to {@link shader} for more info. Note that using textureSlot.color,
     * .normal, and .shiny are equivalent to calling addTexture() with 0, 1, and 2 respectively as 
     * the texture slot argument.
     * @param {Number} slot The texture slot. See {@link sandboxe.material.textureSlot}
     * @param {asset} image The image to use a texture. Multiple frames are supported and can be iterated through dynamically.
     */
    this.addTexture = function(){};

    /**
     * Sets the given camera as the source framebuffer.
     *
     * The source framebuffer is an optional input you can specify 
     * to utilize the last known visual of a camera as a texture 
     * source. This can be used in a few different ways. Once its set, 
     * sandboxe.material.corePrograms will map it as another texture binding.
     * To disable this, simply call setFramebufferSource again with a 
     * default entity. If your material uses a custom shader, the shader can access 
     * if through the Dynacoe_SampleFramebuffer function.
     * @param {camera} Camera 
     */
    this.setFramebufferSource = function(){};

    /**
     * Iterates all textures to the next texture frame
     */
    this.nextTextureFrame = function(){};






    /**
     * The ambient color of the material.
     * @type {color}
     */
    this.ambient = {};

    /**
     * The diffuse color of the material.
     * @type {color}
     */
    this.diffuse = {};

    /** 
     * The specular color of the material
     * @type {color}
     */
    this.specular = 0;




    /**
     * The amount of specular light that should be allowed.
     * @type {Number}
     */
    this.specularAmount = 0;

    /**
     * The amount of diffuse light that should be allowed.
     * @type {Number}
     */
    this.diffuseAmount = 0;

    /**
     * The amount of reflected specular light.
     * @type {Number}
     */
    this.shininess = 0;

    /**
     * The source logic for the material as a shading program.
     * This can either be a {@link sandboxe.material.coreProgram} or 
     * a {@link shader} program object with custom logic.
     * @type {Number|shader}
     */
    this.program = 0;



    /**
     * Data that depends on the drawing mode. In implementations
     * that support shaders, this can be used as you see fit.
     * This property should be overwritten to update the user data.
     * Up to 32 values can be given to the program.
     * @type {Array}
     */
    this.userData = 0;




    return this;
}
