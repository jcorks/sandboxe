/**
 * @class object2d
 * @extends component
 * @description
 * A component that gives movement and collision-detection
 * related attributes to an Entity in 2D space
 *
 * Known {@link component} events:</br>
 * <pre>
 * - on-move: Called 
 * - on-collide: 
 * </pre>
 * 
 */ 
function object2d() {

    /**
     * Compounds a velocity vector with the current velocity
     * @param {Number} factor The velocity amount to add. Can be negative.
     * @param {Number} direction The direction to apply the velocity in degrees.
     */
    this.addVelocity = function(){};

    /**
     * Compounds a velocity vector with the current velocity towards a point.
     * @param {Number} factor The velocity amount to add. Can be negative.
     * @param {vector} target The point to add velocity towards
     */
    this.addVelocityTowards = function(){};


    /**
     * Sets the velocity vector of an object.
     * @param {Number} factor The velocity to set.
     * @param {Number} direction The direction to set the velocity in degrees.
     */
    this.setVelocity = function(){};

    /**
     * Sets the velocity vector of an object.
     * @param {Number} factor The velocity to set.
     * @param {vector} target The point to set velocity towards
     */
    this.setVelocityTowards = function(){};


    /**
     * Reduces the speed of the Entity to 0.
     */
    this.halt = function(){};

    /**
     * Enables collisions between the given groups. By default, all groups can collide 
     * with all other groups, including itself.
     * @param {Number} src  Group in question
     * @param {Number} dest Group to collide with in future collisions
     */
    this.enableGroupInteraction = function(){};

    /**
     * Disables collisions between the given groups.
     * @param {Number} src  Group in question
     * @param {Number} dest Group to prevent collisions with in future collisions
     */
    this.disableGroupInteraction = function(){};





    /**
     * Sets the amount of resistance to speed measured as a percentile.
     *
     * Every frame, only the amount percent of the host Entity's velocity is retained. For example,
     * if amt is specified to be .95, every frame 5% of the Entity's speed will be lost.
     * This is applied in the horizontal direction.
     * @type {Number}
     */
    this.frictionX = 0.0;

    /**
     * Same as frinctionX, but is applied in the vertical direction.
     * @type {Number}
     */
    this.frictionY = 0.0;

    /**
     * Returns the speed of the object.
     * @type {Number}
     */
    this.speed = 0.0;

    /**
     * Returns the direction that the obejct is traveling in degress.
     * @type {Number}
     */
    this.direction = 0.0;



    /**
     * Horizontal velocity of the object.
     * @type {Number}
     */
    this.velocityX = 0.0;

    /**
     * Vertical velocity of the object.
     * @type {Number}
     */
    this.velocityY = 0.0;


    /**
     * When set, redefines the collider 
     * for the object. The array should be pairs of xy values
     * to define the colled polygon object.
     * @type {Array}
     */
    this.collider = 0.0;


    /**
     * Returns the entity that this object last collided with.
     * @type {entity}
     */
    this.lastCollided = {};


    /**
     * Based on the objects current velocity, returns the position that will be used 
     * as the new position next frame. Note that if the object moves by other means 
     * (i.e. the host's node is modified), the nextPosition will also change.
     * @type {vector}
     */
    this.nextPosition = {};

    /**
     * Returns the previous position that was used before the current position 
     * when this object2d was attached.
     * @type {vector}
     */
    this.lastPosition = {};

    /**
     * Sets/Gets the collision group. Groups can be used to ignore sets of object2D colliders 
     * efficently before collisions are processed. The default for all groups is sandboxe.object2d.group.a)
     * @type {Number}
     */
    this.group = 0;






    return this;
}
