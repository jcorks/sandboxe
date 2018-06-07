/**
 * @class activeSound
 * @description
 * Class that assists in working with audio waveforms that are currently being streamed 
 * to the audio manager. 
 
 * {@link outputBuffer}, which aims to be the write-only complement to inputBuffer.
 *
 * @example 
 * // Creates a new inputbuffer from the static helper in sandboxe
 * var myBuffer = sandboxe.inputBuffer.create();
 *
 * // Opens a file named 'binaryFile' and dumps its contents within the buffer.
 * myBuffer.open('binaryFile');
 *
 * // Reads a floating point (decimal) value from the buffer 
 * value1 = myBuffer.read(sandboxe.type.float);
 *
 * // Then reads the next 10 bytes as a UTF8 string.
 * str1 = myBuffer.readString(13);
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
    this.pause = function(){};
    this.resume = function(){};


     
    /**
     * The volume of the sample. 0.0 will result in a silent playback 
     * 1.0 is the default.
     * @type {Number}
     */
    this.volume = 1.0;

    /**
     * @type {Number}
     */
    this.panning = .5;
     

    /**
     * @type {Number}
     */
    this.repeat = false;

    /**
     * @type {Number}
     */
    this.channel = 0;

    /**
     * @type {Number}
     */
    this.valid = true;

    
     
    return this;
}