/**
 * @class inputListener
 * @description
 * An object to listen to input. See {@link sandboxe.input.addKeyListener}, {@link sandboxe.input.addPointerListener}, {@link sandboxe.input.addMappedListener}, and {@link sandboxe.input.addPadListener} to instantiate 
 * and enable it. </br></br>
 *
 * inputListener allows you to set up more detailed specific behavior as soon 
 * as an input even is recorded for a frame, allowing you to avoid the classic 
 * "query input every frame pattern". </br></br>
 * 
 * Example: </br></br>
 * @example 
 // creates the button listener and automatically links it 
 // to start listening for the button. In this case, the space key.
 // Which listener you instiate depends on what device you want to 
 // listen to. Here, we're listening to the keyboard, but it is
 // possible to also listen to the pointer and auxiliary input 
 // pads.
 listener = sandboxe.input.addKeyListener()

 // Sets the message for the press event
 listener.onPress = function() {
     sandboxe.console.info('Space was pressed!\n');
 }

 // Sets the message for the active event
 listener.onActive = function() {
     sandboxe.console.info('Space was held!\n');
 }

 // Sets the message for the change event
 listener.onChange = function() {
     sandboxe.console.info('Space state changed!\n');
 }


 // Sets the message for the release event
 listener.onRelease = function() {
     sandboxe.console.info('Space was released!\n');
 }
 
 
 
 
 *
 */ 
function inputListener() {

    /**
     * The user function to call when the input is pressed / activated
     * @type {Function}
     */
    this.onPress = {};

    /**
    * The user function to call when the input is non-zero. It is called 
    * every frame that it is active until it is release.
    * @type {Function}
     */
    this.onActive = {};

    /**
    * The user function to call when the input state has changed. It is called 
    * on ever state change, which may include multiple per frame.
    * @type {Function}
     */
    this.onChange = {};


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
