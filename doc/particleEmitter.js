/**
 * @class particleEmitter2D
 * @extends entity
 * @description
 *
 * Particle emitters are a means of producing particle effects 
 * that are both more efficiently rendered and rendered with relatively 
 * few configurations. By importing a particle specification file to 
 * define a particle ({@link sandboxe.assets.load}), you can instantiate 
 * a pseudorandomixed effect with a single call.
 *
 */ 
function particleEmitter2D() {


    /**
     * Instantiates a particle in 2D space based on a stored design.
     *
     * @param {asset} p    The name of the particle design to emit. If p does
     *             not refer to a stored particle, then no particle is emitted
     *             and the reference returned is invalid.
     * @param {Number} count number of these particles to emit.
     */
    this.emitParticle = function(p, count){};

    /**
     * Enable texture filtering for each particle emitted.
     * It is enabled by default.
     * @type {Boolean}
     */
    this.filtered = false;


    /**
     * Enable translucency for each each particle drawn.
     * It is enabled by default.
     * @type {Boolean}
     */
    this.translucent = false;
    
     
    return this;
}