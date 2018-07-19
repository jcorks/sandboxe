/**
 * @class renderLight
 * @extends component
 * @description
 * A rendering light in 3D space.
 * 
 * 
 */ 
function renderLight() {

    /**
     * Resets the lights properties back to the default state.
     */
    this.reset = function(){};



    /**
     * Type of light. See {@link sandboxe.renderLight.type} for possible choices.
     * @type {Number}
     */
    this.type = 0.0;

    /**
     * Whether to enable the light itself.
     * @type {Boolean}
     */
    this.enabled = false;

    /**
     * Global / absolute position of the light.
     * @type {vector}
     */
    this.position = {};

    /**
     * Intensity of the light.
     * @type {Number}
     */
    this.intensity = 0.0;

    /**
     * Color of the light.
     * @type {color}
     */
    this.color = {};





    return this;
}