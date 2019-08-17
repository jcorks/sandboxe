/**
 * @class dataTable
 * @extends component
 * @description
 * A component that can store and import arbitrary data. Instantiates with {@link sandboxe.dataTable.create()} </br></br>
 *
 * Provides a convenient interface for placing and retrieving named properties.</br></br>
 * Often with programs, there is a need to preserve data beyond the execution of the 
 * program. Sometimes, it is enough to simply write to a text file, but this isn't 
 * always flexible, and has little resistance against device errors, forms 
 * of corruption, and user tampering. dataTable provides a non-sequential, corruption-resistant 
 * way to store data. Using the Write functions, you can store named variables 
 * , data, and even other dataTables in a safe manner. Then getState() can be 
 * used to retrieve a data buffer that represents the dataTable's exact state,
 * which can then be used later in another instance.</br></br>
 *
 * Known {@link component} events:</br>
 * <pre>
 * - on-read: after reading a piece of data. 
 * - on-write: before writing a piece of data. The default handler actually performs the write, so stopping propogation will prevent writing.
 * - on-remove: before removing a piece of data. The default handler actually performs the removal, so stopping propogation will prevent removal. 
 * - on-read-state: after successfully reading a state
 * </pre>
 *
 * 
 */ 
function dataTable() {

    /**
     * Associates a datum with a name.
     *
     * @param {String} name The name that the data will be associated with 
     * @param {String} i    The data to store 
     */
    this.writeString = function(name, i){};

    /**
     * Associates a datum with a name. 
     *
     * @param {String} name The name that the data will be associated with 
     * @param {Array} byteData    The data to store as an array of numbers, each being a byte value 
     */
    this.writeByteArray = function(name, yteData){};

    /**
     * Retrieves a datum associated with a name. If there is no such association,
     * an empty string is returned.
     * 
     * @param {String} name The name associated with the data.
     * @returns {String} The data for that name.
     */
    this.readString = function(name){};

    /**
    * Retrieves a datum associated with a name. If there is no such association,
    * an empty Array is returned.
    * 
    * @param {String} name The name associated with the data.
    * @returns {Array} The data for that name.
     */
    this.readByteArray = function(name){};



    /**
     * Returns whether there is a datum-name association 
     * with the given name.
     * @param {String} name The name to look up.
     * @returns {boolean}
     */
    this.query = function(name){};


    /**
     * Removes the datum-name association.
     * @param {String} name The name to remove.
     */
    this.remove = function(){};



    /**
     * Removes all stored associations and data entries, restoring 
     * the container back to a default state.
     */
    this.clear = function(){};



    /**
     * Writes a pure data-form of the table's contents. This can then be 
     * passed into setState() turn the calling object into an exact copy 
     * of this one.
     *
     * getState() / setState() were intended to be used in tandem to preserve data contents of 
     * the dataTable across program invocations. Along with writing the exact state of 
     * the dataTable, the data includes header and checksum data to improve parity across 
     * execution states.
     * @returns {String} A string of hexified byte values to later be re-read with setState()
     */
    this.getState = function(){};


    /**
     * Sets the dataTable state to reflect the state
     * defined by the input buffer.
     *
     * The buffer is implied to have been produced from a getState call.
     * If not, or corruption on some device has occurred, 
     * there is a good chance that this function will detect it before applying the data. 
     * In the case that an error does occur, false will be returned and no action taken.
     * @param {String} data A string of hexified byte data from getState()
     */
    this.setState = function(){};
    





    return this;
}
