/**
 * @class vector
 * @description
 *
 *  A hybrid class suitable for both 2D and 3D
 *  positional and physics operations.  See {@link sandboxe.vector.create}
 *
 */ 
function vector() {

    
    /**
     * Returns the length of the vector.
     *
     * @returns {Number}
     */
    this.length = function(){};

    /**
     * Instantiates a new vector that is a copy of this one's data.
     * @returns {vector}
     */
    this.clone = function(){};

    /**
     * Returns this vector in string form
     * @returns {String}
     */
    this.toString = function(){};

    /**
     * Gets the non-directional distance between 2 vectors as positions.
     * @param {vector} other 
     */
    this.distance = function(){};

    /**
     * Sets this vector to a normalized form where its length becomes 1.0.
     */
    this.normalized = function(){};

    /**
     * Returns the dot product of the two vectors.
 	 *
 	 * The dot product is defined as
 	 * (a.length() * b.length() * cos(\theta))
 	 * where theta is the angle between the 2 vectors
     * @param {vector} b
     * @returns {Number}
     */
    this.dot = function(){};

    /**
     * Returns the 2D cross product => this x other.
 	 *
 	 * A cross product is computed as if the z components
     * were equal to zero. This gives the magnitude, or Z of
     * the cross product.
     * @param {vector} other 
     * @returns {Number}
     */
    this.cross2D = function(){};

    /**
     * Returns the cross product of this vector and another in that order.
     * @param {vector} other 
     * @returns {Number}
     */
    this.cross = function(){};




    /**
     * returns the YZ angle between the 2
     * vectors in relation to the origin in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationXDiff = function(){};

    /**
     * returns the angle between the 2
     * vectors in relation to this vector in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationXDiffRelative = function(){};

    /**
     * X axis rotation in degrees
     *
     * If a vector has length zero in these dimensions
     * , the angle is always zero.
     * The rotation is about the directional vector (1, 0, 0) and
     * Positive rotation is towards the positive Z direction.
     * @returns {Number}
     */
    this.rotationX = function(){};






    /**
     * returns the ZX angle between the 2
     * vectors in relation to the origin in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationYDiff = function(){};

    /**
     * returns the angle between the 2
     * vectors in relation to this vector in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationYDiffRelative = function(){};

    /**
     * Y axis rotation in degrees
     *
     * If a vector has length zero in these dimensions
     * , the angle is always zero.
     * The rotation is about the directional vector (0, 1, 0) and
     * Positive rotation is towards the positive X direction.
     * @returns {Number}
     */
    this.rotationY = function(){};
    
    



    /**
     * returns the XY angle between the 2
     * vectors in relation to the origin in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationZDiff = function(){};

    /**
     * returns the angle between the 2
     * vectors in relation to this vector in degrees
     * @param {vector} 
     * @returns {Number}
     */
    this.rotationZDiffRelative = function(){};

    /**
     * Z axis rotation in degrees
     *
     * These deal with angles between the x and y axes.
     * XY is most useful for 2D angles and transformations.
     * If a vector has length zero in these dimensions
     * , the angle is always zero.
     * The rotation is about the directional vector (0, 0, 1).
     * Positive rotation is towards the positive Y direction.
     * @returns {Number}
     */
    this.rotationZ = function(){};




    
    /**
     * Rotates the directional vector about the {1, 0, 0} axis in degrees.
     * @param {Number}
     
     */
    this.rotateX = function(){};

    /**
     * Rotates the directional vector about the {0, 1, 0} axis in degrees.
     * @param {Number}
     */
    this.rotateY = function(){};

    /**
     * Rotates the directional vector about the {0, 0, 1} axis in degrees.
     * @param {Number}
     */
    this.rotateZ = function(){};



    /**
     * Rotates the directional vector about the {1, 0, 0} axis in degrees from a different origin.
     * @param {vector}
     * @param {Number}
     */
    this.rotateXFrom = function(){};

    /**
     * Rotates the directional vector about the {0, 1, 0} axis in degrees from a different origin.
     * @param {vector}
     * @param {Number}
     */
    this.rotateYFrom = function(){};

    /**
     * Rotates the directional vector about the {0, 0, 1} axis in degrees from a different origin.
     * @param {vector}
     * @param {Number}
     */
    this.rotateZFrom = function(){};




    /**
     * X component of the vector
     * @type {Number}
     */
    this.x = {};

    /**
     * Y component of the vector
     * @type {Number}
     */
    this.y = {};

    /**
     * Z component of the vector
     * @type {Number}
     */
    this.z = {};


    return this;
}