/**
 * @class clock
 * @extends component
 * @description
 * An component that keeps track of time with millisecond resolution. Instantiates with {@link sandboxe.clock.create()} </br></br>
 *
 * Grants functionality similar to using a stopwatch. Note that all properties 
  * are readonly. Writing to them will have no effect and will not persist.</br></br> 
 *
 * Known {@link component} events:</br>
 * <pre>
 * - clock-step: Called every step when the clock is active.
 * - clock-draw: Called every draw when the clock is active.
 * - clock-expire: Called when the clock expires
 * </pre>
 *
 * 
 */ 
function clock() {

    /**
     * Resets the timer with the time it should expire in milliseconds.
     * @param {Number} time If specified, sets the new duration for the timer. If excluded, the timer has no time limit.
     */
    this.set = function(){};

    /**
     * Resets the timer with the time it had previously
     */
    this.reset = function(){};

    /**
     * Pauses the timer.
     */
    this.pause = function(){};

    /**
     * Resumes the timer from the pause state.
     */
    this.resume = function(){};



    /**
     * Returns the number of milliseconds since the clock was last set.
     * @type {Number}
     */
    this.timeSince = 0.0;

    /**
     * Returns the number of milliseconds left until the clock expires
     * @type {Number}
     */
    this.timeLeft = 0.0;

    /**
     * Returns duration of the timer in milliseconds.
     * @type {Number}
     */
    this.duration = 0.0;

    /**
     * Returns whether the clock as expired.
     * @type {Number}
     */
    this.expired = 0.0;

    /**
     * Returns whether the clock is in a paused state.
     * @type {Number}
     */
    this.paused = 0.0;





    return this;
}