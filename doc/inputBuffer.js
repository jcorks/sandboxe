/**
 * Class that assists in reading byte-based datastreams. granting 
 * the ability to read wherever in the stream you wish. You can convert 
 * groups of byte data into familiar types, or just retrieve the raw data itself.
 *
 * When working with binary assets, it's often necessary to work with raw byte data. 
 * Inherently, Javascript doesn't provide many ways to handle 
 * non-text data manipulation. inputBuffer Allows for reading that sort of 
 * data to be interpreted later, or read stream-wise. This contrasts with 
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
 * @class inputBuffer
 */ 
 function inputBuffer() {
     
     /**
      * Opens the given array as the source of an input buffer. The data is copied and 
      * placed within the input buffer, so the input array does not need to be preserved.
      *
      * @param {Array} array An array of raw byte values. 
      */     
     this.openBuffer = function(array){};

     /**
      * Opens the given file as the source of an input buffer. 
      *
      * @param {String} path Path to the file to open as an input buffer.
      */     
     this.open = function(path){};
     
     /**
      * Reads a UTF8 string object from the input buffer.
      *
      * @param {Number} numBytes The number of characters to read from the buffer.
      */          
     this.readString = function(numBytes){};
     
     
     /**
      * Reads the next object from the given byte stream.
      * @param {Number} type Refer to {@link sandboxe.type} for valid values to be read.
      * @returns {Object} The value requested.
      */
     this.read = function(){};
     
    /**
     * Size of the input bufer stream in bytes. Writing this property does nothing.
     * @type {Number}
     *
     */
    this.size = 0;
    
    /**
     * The current byte index being read. The position is automatically updated 
     * when reading using {@link inputBuffer.read} and similar functions
     * @type {Number}
     */
    this.position = 0;
     

    
    
    
     
    return this;
}