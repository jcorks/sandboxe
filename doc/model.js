/**
 * @class model
 * @description
 * 
 * A 3D object as a collection of meshes and materials.
 * 
 */ 
function model() {

    /**
     * Gets the mesh at the index given.
     * @param {Number} index
     * @returns {mesh}
     */
    this.getSectionMesh = function(){};

    /**
     * Gets the material at the index given.
     * @returns {material}
     */
    this.getSectionMaterial = function(){};

    /**
     * Sets the mesh at the given index
     * @param {Number} index 
     * @param {mesh} mesh Mesh to set at that index.
     */
    this.setSectionMesh = function(){};

    /**
     * Sets the material at the givne index
     * @param {Number} index 
     * @param {material} material Material to set at that index.
     */
    this.setSectionMaterial = function(){};





    /**
     * Removes all section objects.
     */
    this.clear = function(){};

    /**
     * Adds a new section index.
     */
    this.addSection = function(){};

    /**
     * Creates an entity that when 'draw' is called renders all 
     * meshes and materials given to the model.
     * @returns {entity}
     */
    this.create = function(){};








    /**
     * Number of sections that belong to the model.
     * @type {Number}
     */
    this.sectionCount = 0;




    return this;
}
