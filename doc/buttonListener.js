/**
 * @class buttonListener
 * @description
 * An object to listen to input. See {@link sandboxe.input.buttonListener.create} to instantiate 
 * and enable it. </br></br>
 *
 * buttonListener allows you to set up more detailed specific behavior as soon 
 * as an input even is recorded for a frame, allowing you to avoid the classic 
 * "query input every frame pattern". </br></br>
 * 
 * Example: </br></br>
 * @example 
 // creates the button listener and automatically links it 
 // to start listening for the button. In this case, the space key
 listener = sandboxe.input.buttonListener.create(sandboxe.key_space);

 // Sets the message for the press event
 listener.onPress = function() {
     sandboxe.console.info('Space was pressed!\n');
 }

 // Sets the message for the hold event
 listener.onHold = function() {
     sandboxe.console.info('Space was held!\n');
 }

 // Sets the message for the release event
 listener.onRelease = function() {
     sandboxe.console.info('Space was released!\n');
 }
 
 
 
 
 *
 */ 
function buttonListener() {

    /**
     * The user function to call when the input is pressed / activated
     * @type {Function}
     */
    this.onPress = {};

    /**
    * The user function to call when the input is held. It is called 
    * every frame that it is held until it is release.
    * @type {Function}
     */
    this.onHold = {};

    /**
     * The user function to call when the input is released.
     * @type {Function}
     */
    this.onRelease = {};

    /**
     * Removes the button listener from sandboxe.
     */
    this.remove = function(){};



    return this;
}