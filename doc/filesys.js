/**
 * @class filesys
 * @description
 * Abstracts the system's means of storing files. Instantiates with {@link sandboxe.filesys.create()} </br></br>
 *
 * Provides abstractions for files and / or directories. Success of a file operation 
 * can depend on a number of factors that aren't acessible from this program and change 
 * based on what system the user is on. This includes things like: path characters, 
 * permissions, etc.
 *
 * 
 */ 
function filesys() {

    /**
     * Sets the current directory of the filesys object 
     *
     * On most systems relative paths are accepted.
     * @param {String} path The path to change to.
     * @returns {Boolean} Returns whether the operation was successful
     */
    this.changeDir = function(path){};


    /**
     * Changes the current directory to the name of a child.
     *
     * This is the object name, as contained in {@link filesys.getNames()}
     *
     * @param {String} child Name of the child directory.
     * @returns {Boolean} Returns whether the operation was successful
     */
    this.goToChild = function(path){};

    /**
     * Changes the current directory to the parent directory, if one exists.
     *
     * @returns {Boolean} Returns whether the operation was successful
     */
    this.goToParent = function(){return false;};


    /**
     * Changes the current directory to the parent directory, if one exists.
     *
     * @returns {Array} Returns strings of all the names of child objects. This is a collection of files and directories
     */
    this.getNames = function(){return [];};



    /**
     * Returns whether the given name is a child of the current directory
     *
     * @param {String} child Name of the child object to look for.
     * @returns {Boolean} Returns whether the child exists.
     */
    this.query = function(path){ return false;};


    /**
     * Returns whether the given name is a child file. If false, on most system this denotes a directory.
     *
     * @param {String} child Name of the child object to examine.
     * @returns {Boolean} Returns whether the child is a file.
     */
    this.isFile = function(path){return false;};



    /**
     * Full path of the current working directory.
     * @type {String}
     */
    this.cwd = '';




    return this;
}
