/**
 * @class node
 * @extends component
 * @description
 * A hierarchical transform object.
 *
 * Allows for chaining transformation information including
 * position, rotation, and scaling.
 *
 * 
 */ 
function node() {



    /**
     * Sets whether to reverse the node's interpretation of 
     * of translation for transform calculation. Rarely useful.
     * @type {Boolean}
     */
    this.reverse = 0.0;

    /**
     * X, Y, and Z positional component of the transform.
     * @type {vector}
     */
    this.position = 0.0;

    /**
     * X, Y, and Z scale component of the transform.
     * @type {vector}
     */
    this.scale = 0.0;

    /**
     * X, Y, and Z axes rotational components.
     * @type {vector}
     */
    this.rotation = 0.0;




    return this;
}