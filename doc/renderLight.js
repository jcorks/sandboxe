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
     * Resets the timer with the time it should expire in milliseconds.
     * @param {Number} time If specified, sets the new duration for the timer. If excluded, the timer has no time limit.
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