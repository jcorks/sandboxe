/**
 * @class mesh
 * @description
 * 
 * 3D object defined by triangle primitives.
 *
 * A mesh contains 2 components: the Mesh itself and a series of faces (face list).
 * The mesh itself provides the base data: vertex positions, normals,
 * UVs, you name it. A face list actually 
 * Using the mesh - meshObject reloationship aptly can allow for flexible
 * control over performance vs. memory cost.
 * 
 */ 
function mesh() {

    /**
     * Explicitly defines the vertices of the mesh.
     *
     * This overwrites any previous geometry data. The array of data 
     * must match numVertices in lenght or the request will be rejected.
     * The numbe rof floats per vertex depends on the given {@link sandboxe.mesh.vertexAttribute}
     * 
     *  @param {Number} attribute The attribute . See {@link sandboxe.mesh.vertexAttribute}
     *  @param {Array} data The array of values to read from.
     */
    this.defineVertices = function(){};

    /**
     * Gets the data for the requested vertex.
     * @param {Number} vertexIndex The index of the vertex to get info for. 
     * @param {Number} attribute The attribute to request.
     * @returns {Array} The data for the vertex requested.
     */
    this.getVertex = function(){};

    /**
     * Sets the data for the requested vertex.
     * @param {Number} vertexIndex The index of the vertex to get info for. 
     * @param {Number} attribute The attribute to request.
     * @param {Array} newData The data for the vertex requested.
     */    
     this.setVertex = function(){};





    /**
     * Adds a faceList to the mesh. When drawn, to the
     * faceList will refer to vertices of this mesh.
     * @param {Array} object The face list to add. If no argument is given, an empty mesh object is added. The array is an array of indices into the mesh's vertices
     */
    this.addObject = function(){};

    /**
     * Retrieves the i'th face list requested.
     * @param {Number} i
     * @returns {Array}
     */
    this.getObject = function(){};

    /**
     * Removes the meshObject requested.
     * @param {Number} i
     */
    this.removeObject = function(){};

    /**
     * Returns the number of face lists that this mesh contains.
     * @returns {Number} Count of face lists.
     */
    this.numObjects = function(){};








    /**
     * Number of vertices that belong to this mesh. vertex count must be set before 
     * starting to modify vertices.
     * @type {Number}
     */
    this.vertexCount = 0;




    return this;
}
