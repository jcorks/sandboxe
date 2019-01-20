/**
 * @class entity
 * @description
 * extensible behavior object updated by the engine. Created with 
 * {@link sandboxe.entity.create}</br></br>
 *
 * Entities are the base object that provides means to easily 
 * include custom update behavior. Along with calling custom step and draw 
 * functions over time, with {@link component}s you can provide
 * a more manageable software platform fior youtr project. </br></br>
 *
 * Entities are arranged in a hierarchical fashion, where the root
 * is assigned using {@link sandboxe.engine.setRoot} 
 */

function entity() {

    /**
     * Performs the normal draw iteration, which calls onDraw() for this entity,
     * draw() for all children entities, and draw() for all attached components.
     */
    this.draw = function(){};

    /**
     * Performs the normal draw iteration, which calls onStep() for this entity,
     * step() for all children entities, and step() for all attached components.
     */
    this.step = function(){};

    /**
     * Returns whether the entity has been removed from sandboxe. It will 
     * still be accessible, but not usable.
     * @returns {Boolean} Whether this entity is still valid.
     */
    this.valid = function(){};

    /**
     * Detaches and marks this entity for deletion.
     */
    this.remove = function(){};

    /**
     * Adds the given entity as a child. When a child, an Entity will be
     * updated when the World is updated.
     * @param {entity} child
     */
    this.attach = function(){};

    /**
     * Removes the child-parent relationship, detaching this entity from its parent.
     */
    this.detach = function(){};

    /**
     * Returns the number of children belonging to this entity.
     * @returns {Number}
     */
    this.getNumChildren = function(){};

    /**
     * Returns whether the given entity is contained within this entity.
     * @param {entity} queriedEntity 
     * @returns {Boolean}
     */
    this.contains = function(){};

    /**
     * Returns the i'th Entity starting at 0.
     *
     * Entities are ordered by priority, where the first entity
     * is guaranteed to be the one with the lowest Priority value.
     * @returns {Array} children
     */
    this.getChildren = function(){};

    /**
     * Returns all Entities that are within this Entity's hierarchy.
     * @returns {Array} allSubEntities
     */
    this.getAllSubEntities = function(){};

    /**
     * Returns all bound entities with the name equivalent to the one given within 
     * this entity's hierarchy.
     * @returns {Array} searchResults
     */
    this.findChildByName = function(){};

    /**
     * Convenienve function to create a new entity that is set 
     * as a child of this entity.
     * @returns {entity}
     */
    this.createChild = function(){};

    /**
     * Creates a new component as part of this entity.
     * @param {Number} type The component type to use. See {@link sandboxe.component.type} 
     * @returns {component} The component created.
     */
    this.addComponent = function(){};

    /**
     * Returns the last recorded amount of milliseconds it took the
     * Entity, iedentified by id, to complete its step cycle. A step cycle consists of the Entities
     * Step function and any attached components' step.
     * @returns {Number} 
     */
    this.stepDuration = function(){};

    /**
     * Returns the last recorded amount of milliseconds it took the
     * Entity, iedentified by id, to complete its draw cycle. A draw cycle consists of the Entities
     * Draw function and any attached components' draw.
     * @returns {Number}
     */
    this.drawDuration = function(){};

    /**
     * Alters the priority of this entity.
     *
     * Priorty determines the order in which this
     * entity is updated. A lower priority means it will be drawn and updated earlier.
     * It is undefined which entity is updated first if both have the same priority.
     * @param {Number} p The new priority.
     */
    this.setPriority = function(){};


    /**
     * Sends the entity of the ID to
     * be the last of in line for drawing and updates.
     */
    this.setPriorityLast = function(){};

    /**
     * Sends the entity to be drawn and updated as the last in the queue
     * causing it to be on top when drawing.
     */
    this.setPriorityFirst = function(){};

    /**
     * Returns the priority of the this entity.
     * @returns {Number} priority value
     */
    this.getPriority = function(){};

    /**
     * Returns the parent of the entity.
     * @returns {entity} 
     */
    this.getParent = function(){};

    /**
     * Returns whether this entity has a parent.
     * @returns {Boolean}
     */
    this.hasParent = function(){};


    /**
     * Returns whether or not there is currently an attached component of the
     * tag given if it exists. If there a multiple, the earliest component 
     * added is returned.
     * @returns {component}
     */
    this.queryComponent = function(){};

    /**
     * Returns all components that belong to the Entity.
     * @returns {Array} array of all components
     */
    this.getComponents = function(){};

    /**
     * Removes the first occurrance of a component
     * with the tag given.
     *
     * @param {String} tag The tag that identifies the component to remove.
     */
    this.removeComponent = function(){};



    /**
     * Returns wether or not the engine is handling calling step() automatically,
     * taking into account the Entity's hierarchy.
     *
     * @type {Boolean}
     */
    this.isStepping = 0;

    /**
     * Returns wether or not the Engine is handling calling Draw() automatically,
     * taking into account the Entity's hierarchy.
     *
     * @type {Boolean}
     */
    this.isDrawing = 0;

    /**
     * The entity's unique ID.
     *
     * The ID uniquely identifies an entity. 
     * @type {Number}
     */
    this.id = 0;

    /**
     * The name identifier of the entity.
     * The name is settable only the first time it is set. 
     * Afterward, any further setting will have no effect.
     * @type {String}
     */
    this.name = 0;

    /**
     * The Node of the Entity, holding info such as the position and rotation.
     *
     * @type {transform}
     */
    this.node = 0;

    /**
     * The global X position of this entity that considers all parents of this entity.
     */
    this.globalX = 0;    

    /**
     * The global Y position of this entity that considers all parents of this entity.
     */
    this.globalY = 0;    

    /**
     * The global Z position of this entity that considers all parents of this entity.
     */
    this.globalZ = 0;    

     
    return this;
}
