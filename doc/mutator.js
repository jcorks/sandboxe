/**
 * @class mutator
 * @extends component
 * @description
 *  A piecewise function manager that changes inputs
 *  over time.
 *
 *  There are some instances where it is useful to model
 *  the transformation of a value in a complex manner. The mutator component
 *  provides functionality for simple and complex easing. You can string easing functions
 *  together to achieve more complex behavior in one instance of a Mutator through
 *  the mutation interface. For more simple easing, see {@link sandboxe.ease}.
 *  All times are delt with in seconds and
 *  the Mutator always begins at time 0.
 *
 * 
 */ 
function mutator() {

    /**
     * Removes all mutations.
     */
    this.clear = function(){};

    /**
     * Adds a new mutation.
     * @param {Number} when The time that the mutation will be over, in seconds.
     * @param {Number} value The value that should be reached when the mutation is over.
     * @param {Number} mutationType See {@link sandboxe.mutator.mutation}
     */
    this.add = function(){};

    /**
     * Starts the mutation lifetime. If it was already started, this function starts the 
     * mutation lifetime from the beginning.
     */
    this.start = function(){};

    /**
     * Stops the mutation lifetime. Once stopped, the mutation's value is set as if all mutations finished normally.
     */
    this.stop = function(){};

    /**
     * Returns the value of the mutator at the given time in seconds based on all added mutations.
     * @param {Number} time The time to request in seconds.
     * @returns {Number} The value at that time.
     */
    this.getAt = function(){};

    /**
     * Returns the current value of the mutation state. See {@link mutator.start}.
     */
    this.value = function(){};




    /**
     * Returns whether the mutator's life cycle has expired. Writing to this value has no effect.
     * @type {Number}
     */
    this.expired = 0.0;

    /**
     * Returns the current time elapsed since starting the mutation life cycle. Writing to this value has no effect
     * @type {Number}
     */
    this.currentTime = 0.0;

    /**
     * Returns the duration of the mutator based on current mutations. Writing to this value has no effect.
     * @type {Number}
     */
    this.duration = 0.0;

    /**
     * Whether the mutator should loop automatically once the lifetime has elapsed. The default is false.
     * @type {Number}
     */
    this.loop = 0.0;






    return this;
}
