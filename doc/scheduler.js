/**
 * @class scheduler
 * @extends component
 * @description
 * A component that allows for automatic running 
 * of logic at certain intervals.
 *
 * 
 */ 
function scheduler() {

    /**
     * Begins a new task. A task will run 
     * once per every announced millisecond interval.
     * The resolution is only as good as the number of times the
     * host's step() is called. In an Engine context, this is usually
     * locked to the sandboxe's max FPS.
     * @param {String} name Name of the task.
     * @param {Number} interval Interval in milliseconds.
     * @param {Function} function Function to run at the given interval
     */
    this.startTask = function(){};

    /**
     * Halts the task with the given name.
     *
     * If there is no task with the given name, no action is taken.
     * @param {String} name Name of the interval to end.
     */
    this.endTask = function(){};

    /**
     * Returns the millisecond rate of the given task name.
     * @param {String} name 
     * @returns {Number}
     */
    this.getTaskInterval = function(){};

    /**
     * Resumes the scheduler from the pause state.
     */
    this.resume = function(){};

    /**
     * Pauses the timer from the pause state.
     */
    this.pause = function(){};



    /**
     * Returns all registered tasks by name.
     * @type {Array} names
     */
    this.tasks = 0.0;





    return this;
}