/**
 * @class asset
 * @description
 *   Refers to a stored asset from a datastream.
 *
 *   Assets represent a stored chunk of useful data 
 *   encoded into a format that the engine can use. 
 *   Assets are used as the bridge between external resources 
 *   and sandboxe itself.
 *
 */ 
function asset() {

    /**
     * Returns the stored asset object containing usable data.
     */
    this.get = function(){};

    /**
     * Removes the asset from the program.
     */
    this.remove = function(){};

    /**
     * Attempts to dump the asset to a file
     *
     * The encoder extension specifies which encoder
     * should handle writing the file. If the extension is not supported, the write will fail
     * and false will be returned. True is returned if the dump was reported as successful
     * by the encoder.
     * @param {String} encoderExtension The type of file to write on disk. I.e. png 
     * @param {String} Name Name of the file to write.
     */
    this.write = function(arrayOfSamples){};





    /**
     * Returns whether this asset refers to a real asset or not.
     * @type {Boolean}
     */
    this.valid = true;

    /**
     * Returns the name of the asset. Read-only.
     * @type {String}
     */
    this.name = "";

    return this;
}