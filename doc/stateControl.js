/**
 * @class stateControl
 * @extends component
 * @description
 * Adds a state machine mechanism to the entity.
 *
 * Each StateControl instance is effectively a dynamic state machine.
 * After desgnating what states exist within the machine using
 * CreateState(), the machine can be run using Execute(). Using each state's
 * StepFunc, the states will transition until an invalid state is returned. Referring
 * to an invalid state halts the state machine.
 *
 * It is also entirely valid to modify the state machine mid-execution.
 *
 * 
 */ 
function stateControl() {

    /**
     * Sets this array of functions as the only one associated 
     * with the state of the given name.
     *
     * During each state, different logic is disgnated to run to control
     * what happens during this state and when the state should be altered.
     * The step function of the state loop is is meant to hold the bulk of the logic, but 
     * it also returns what state should be transitioned to. If the state is to be 
     * kept the same, the StepFunc should simply return the empty string. The draw function of the array
     * can be used to produce visual effects associated with the state, but
     * may not change the current state.
     *
     * If the state tag returned by the StepFunc does not refer to a valid 
     * state part of stateControl, the execution state of the stateControl halts.
     * After being halted, the state machine will remain idle until the next
     * execute() is called. 
     * 
     *
     * @param {String} name Name of the state.
     * @param {Object} stateLoop An container of functions. If defined, the onStep() function will be called called when step()ing and within this state. Next, if onDraw() is defined, it will be called for each draw() in this state. Finally if the onInit() function is defined, it will be called when first entering this state.
     */
    this.createState = function(){};

    /**
     * Removes the state.
     *
     * No action is taken if the tag does not refer to a valid state.
     * @param {String} name
     */
    this.removeState = function(){};

    /**
     * Begins the state machine execution loop from the given state.
     *
     * If begin state does not refer to a valid state, no action is taken.
     * If done in the middle of a state loop function, any queued 
     * function calls are cancelled.
     * @param {String} name
     */
    this.execute = function(){};

    /**
     * stops all current execution.
     *
     * If done during a state loop, all remaining state loop functions 
     * that would have executed are cancelled.
     */
    this.halt = function(){};



    /**
     * Returns the current state tag. If no execution state is active, the empty string is returned.
     * @type {String}
     */
    this.state = "";

    /**
     * Returns whether or not the machine is in a halted state.
     * @type {Boolean}
     */
    this.halted = false;





    return this;
}
