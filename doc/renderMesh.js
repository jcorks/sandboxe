/**
 * @class renderMesh
 * @extends component
 * @description
 * Component that cna render a 3D object that reduces to a Mesh.
 *
 * Meshess are typically loaded from files or data buffers via {@link sandboxe.assets.load}.
 * See {@link mesh}.
 * 
 */ 
function renderMesh() {

    /**
     * Adds a mesh to this renderer.
     * @param {mesh} mesh
     */
    this.addMesh = function(){};

    /**
     * Retrieves the mesh at the given index if any.
     * @param {Number} index
     * @returns {mesh}
     */
    this.getMesh = function(){};

    /**
     * Clears out all references to meshes within this renderer.
     */
    this.clear = function(){};



    /**
     * Type of rendering primitive.
     * The defualt is a triangle.
     * See {@link sandboxe.renderMesh.polygon} for possible choices.
     * @type {Number}
     */
    this.primitive = 0;

    /**
     * Sets/gets the material to use with this renderer.
     * @type {material}
     */
    this.material = {};

    /**
     * The node of this renderMesh.
     * @type {node}
     */
    this.node = {};

    /**
     * Returns the numer of mesh objects that are being used by this renderMesh
     * @type {Number}
     */
    this.meshCount = 0;





    return this;
}