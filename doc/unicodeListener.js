/**
 * @class unicodeListener
 * @description
 * An object to listen for typed characters. See {@link sandboxe.input.unicodeListener.create} to instantiate 
 * and enable it. </br></br>
 *
 * unicodeListener allows you to set up more detailed specific behavior as soon 
 * as an input even is recorded for a frame, allowing you to avoid the classic 
 * "query input every frame pattern". </br></br>
 * 
 
 
 
 
 *
 */ 
function unicodeListener() {

    /**
     * The user function to call when a new character is pressed / activated.
     * @type {Function}
     */
    this.onNewUnicode = {};

    /**
     * Removes the button listener from sandboxe.
     */
    this.remove = function(){};



    return this;
}