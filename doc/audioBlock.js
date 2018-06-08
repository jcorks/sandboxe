/**
 * @class audioBlock
 * @description
 *   Audio asset object.
 *
 *   An audio waveform is defined in sandboxe as a stream of samples,
 *   where samples are 2 channels of
 *   information representing the amplitude of the
 *   waveform at that point. More specifically,
 *   samples are 16-bit signed integers.
 *  Though, it is important to note that AudioBlocks represent stereo
 *  waveforms, where per sample, there exist two datum values, one for each channel. 
 *  As such, data for the waveform is
 *   interleaved to qualify both channels, where the subsequent sample
 *  corresponds to the channel opposite of the current one.
 *
 *
 *
 */ 
function audioBlock() {

    /**
     * Clears the current data store of the AudioBlock and
     * replaces it with the given data.
     *
     * @param {Array} data The audio samples that the AudioBlock will now consist of. Audio samples ere are pairs of implitudes interpreted as uin16 values.
     */
    this.define = function(arrayOfSamples){};

    /**
     * Retrieves the raw data of the waveform.
     * @returns {Array} An array of audio samples representing the wave form, where audio samples are pairs of uint16 values.
     */
    this.read = function(){};


    /**
     * Creates a new audioblock that is a snippet of this audioBlock.
     * @param {Number} start The sample that the subblock should start at
     * @param {Number} end The sample that the sublock should end at
     * @returns {audioBlock} The new audioBlock
     */
    this.getSubBlock = function(start, end){};

    /**
     * Adds the given audioBlock at the end of this audioBlock
     * @param {audioBlock} block The audioBlock to append to this block
     */
    this.appendBlock = function(block){};

    /**
     * Removes the portion of the audioBlock specified
     * @param {Number} start Where to start removing from in samples
     * @param {Number} end Where to end removing from in samples
     */
    this.removeBlock = function(start, end){};

    /**
     * Inserts the data of the given audioBlock at the sample given 
     * within this audioBlock.
     * @param {Number} position The position to insert the block
     * @param {audioBlock} block The audioBlock to insert 
     */
    this.insertBlock = function(position, block){};

    /**
     * Returns the exact time in seconds that corresponds to the given sample.
     * @param {Number} sample The sample to query.
     */
    this.getSecondsFromSample = function(sample){};

    /**
     * Returns the exact sample that corresponds to the given time in seconds.
     * @param {Number} seconds The seconds to query.
     */
    this.getSampleFromSeconds = function(seconds){};




    /**
     * The base volume of the sample that should be used during playback.
     * Default value: 1.0
     * @type {Number}
     */
    this.volume = 1.0;

    /**
     * The base panning that should be used during playback. Default value: .5
     * @type {Number}
     */
    this.panning = 0.5;

    /**
     * Number of samples within this entire waveform. Writing to this value has no effect.
     * @type {Number}
     */
    this.numSamples = 0;

    /**
     * Total number of bytes that this audioBlock consists of.
     * @type {Number}
     */
    this.numBytes = 0   ;
    
     
    return this;
}