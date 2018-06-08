/**
 * @class activeSound
 * @description
 * Class that assists in working with audio waveforms that are currently being streamed 
 * to the audio manager. </br></br>
 *
 * Once an audio asset ({@link audioBlock}) is requested to be played through 
 * {@link sandboxe.sound.playAudio}, activeSound objects allow you to interact 
 * with the playing waveform to allow for more dynamic behavior. Since 
 * activeSounds reflect a temporary object on the audio engine, activeSounds 
 * are not directly instantiable. </br></br>
 * 
 * Example: </br>
 * @example 
 // Once we play a sound, we get the activeSound reference.
 var sound = sandboxe.sound.playAudio(myAudioAsset);

 // Since we want to interact with the sound over time, lets 
 // make an entity and insert its behavior into its step function.
 var fader = sandboxe.entity.create();

 fader.onStep = function() {
     // We're going to make the sound fade out over time by setting its volume
     sound.volume *= .99;
     
     // if the volume is too low, halt the sound and remove the object
     if (sound.volume < .1) {
         sandboxe.console.info('Sound halted!\n');        
         sound.stop();
         fader.remove();
     }

     // If the sound stopped natrually before the volume was low enough, 
     // just remove the object and report it.
     if (!sound.valid) {
         fader.remove();
         sandboxe.console.info('Sound ended on its own!\n');
     }
 }

 sandboxe.engine.setRoot(fader);
 *
 *
 */ 
function activeSound() {
     

    /**
     * Requests that the sound manager change its playback position of the active sound to 
     * a new location.
     * @param {Number} seconds Seconds of progress within the sample to seek.  
     */
    this.seek = function(){};
    
    /**
     * Requests that the sound manager halt playing this sound.
     */
    this.stop = function(){};

    /**
     * Requests that the sound manager temporary halt the playback of this sound.
     * If the process is acknowledged, the sample will be suspended until 
     * resume() is called.
     */
    this.pause = function(){};

    /**
     * Requests that the sound manager continue playing this sample.
     */
    this.resume = function(){};


     
    /**
     * The volume of the sample. 0.0 will result in a silent playback 
     * 1.0 is the default.
     * @type {Number}
     */
    this.volume = 1.0;

    /**
     * The panning of the sample playback. The default is 0.5, meaning evenly 
     * split between the 2 output channels. 0.0 is leftmost, 1.0 is rightmost.
     * @type {Number}
     */
    this.panning = .5;
     

    /**
     * Sets whether the sample should be repeated once all samples have been exhausted.  
     * This reference to the active sound will be valid until repeat is over.
     * @type {Boolean}
     */
    this.repeat = false;

    /**
     * The output channel of the sound sample. Changing this requests a new output channel for the buffer.
     * The default is the channel that the sound was played on.
     * @type {Number}
     */
    this.channel = 0;

    /**
     * Whether this activeSound still refers to a valid sound. Writing over this 
     * value has no effect.
     * @type {Boolean}
     */
    this.valid = true;

    
     
    return this;
}