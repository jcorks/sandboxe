/**
 * outputBuffers, like {@link inputBuffer}s assist in working with raw binary data 
 * as a basic datastream. Much of its functionality mimics inputBuffer, but with 
 * write-only equivalents
 *
 * @example
 * // Creates a new, empty outputBuffer.
 * var myBuffer = sandboxe.outputBuffer.create();
 *
 * // Writes a decimal value to the outputBuffer. (standard single precision of 4 bytes)
 * myBuffer.write(sandboxe.type.float, 3.14);
 *
 * // Writes a string to the buffer as well
 * myBuffer.writeString('Hello, world!');
 *
 * // Send all written data to a binary file
 * myBuffer.commit('binaryFile');
 * @class outputBuffer
 */
function outputBuffer() {
    
    /**
     * Appends the data to the outputBuffer.
     * @param {Number} type Refer to {@link sandboxe.type} for valid values to be read.
     * @param {Number} data The data to write to the outputBuffer 
     */
    this.write = function(type, data){};


    /**
     * Appends the given byte data to the outputBuffer.
     * @param {Array} bytes The array of byte values to write.
     */
    this.writeBytes = function(bytes){};

    
    /**
     * Appends the given string to the outputBuffer. Only the UTF8 data is 
     * written to the string.
     * @param {String} string The string object to write.
     */
    this.writeString = function(string){};
    
    /**
     * Returns a copy of the written data as an array of raw byte values.
     * This does not modify the outputBuffer in any way.
     * @returns {Array} An array of raw byte values.
     */
    this.getData = function(){};
        
    /**
     * Removes all written bytes to the outputBuffer and puts the outputBuffer in a default state.
     */
    this.clear = function(){};
    
    /**
     * Writes a file containing exactly the bytes written to the outputBuffer
     * @param {String} path The path to write the file to.
     */
    this.commit = function(path){}
    
    
    
    
    /**
     * The total size of the data written to the outputBuffer in bytes.
     * @type {Number}
     */
    this.size = 0;
    
    return this;
}