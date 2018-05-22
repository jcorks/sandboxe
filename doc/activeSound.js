


/**
 * activeSounds are objects that represent the editable state of an independent
 * waveform that is currently being processed through the audio engine. Since 
 * the waveforms represented here only refer to sounds that exist, an active flag 
 * is maintained, allowing you to check if the sound is still active.
 *
 *
 * @class activeSound
 */
function activeSound() {
    /**
     * Alters the current playback point of the sample. The request 
     * is processed as soon as possible, but the effect is not guaranteed to be instantaneous
     */
    this.seek = function(){};
    this.stop = function(){};
    this.pause = function(){};
    this.resume = function(){};
    
    this.volume = 1.0;
    this.panning = 0.5;
    this.repeat = false;
    this.channel = 0;
    this.valid = true;
    
    
    return this;
}