/**
 * @class shader
 * @description
 *   Allows you to specify rendering programs usually on your GPU.
 *
 * Shaders are programs compiled and run during runtime to process graphics data. On 
 * backends that support them, they will usually run on dedicated hardware. 
 * Since the actual source language of the Shader depends on the Renderer backend, 
 * The rules and behavior of how the shader source will vary greatly.
 *
 * For the stock OpenGL backend, the shader language will be a variant of GLSL.
 *
 */ 
function shader() {

    /**
     * Adds a stage to the shader program.
     * If the stage already exists and the program has not been compiled succesfully, 
     * this call replaces the old source with this source.
     * @param {Number} stage See {@link sandboxe.shader.stage}
     * @param {String} shader data
     */
    this.addStage = function(){};

    /**
     * Finalizes the programs stages. After this call,
     * the status property will either contain success, meaning the program is now usable,
     * or invalid, meaning compilation failed. In the case of failure,
     * the log property may contain more information as to why the compilation failed.
     */
    this.compile = function(){};






    /**
     * Returns any additional logging information from the shader program.
     * If the status Invalid, typically the log will contain information on why.
     * @type {String}
     */
    this.log = "";

    /**
     * Returns the current program status.
     * See {@link sandboxe.shader.status}
     * @type {Number}
     */
    this.status = 0.5;

    /**
     * Returns a string containing the shader language used by shading programs. This 
     * is dependent on the parameters of the renderer used by / compiled with sandboxe.
     * @type {String}
     */
    this.shaderLanguage = "";
    
     
    return this;
}