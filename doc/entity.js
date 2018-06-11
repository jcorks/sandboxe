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
     *
     */
    this.draw = function(){};

    /**
     *
     */
    this.step = function(){};

    /**
     *
     */
    this.valid = function(){};

    /**
     *
     */
    this.remove = function(){};

    /**
     *
     */
    this.attach = function(){};

    /**
     *
     */
    this.detach = function(){};

    /**
     *
     */
    this.getNumChildren = function(){};

    /**
     *
     */
    this.contains = function(){};

    /**
     *
     */
    this.getChildren = function(){};

    /**
     *
     */
    this.getAllSubEntities = function(){};

    /**
     *
     */
    this.findChildByName = function(){};

    /**
     *
     */
    this.createChild = function(){};

    /**
     *
     */
    this.add = function(){};

    /**
     * 
     */
    this.stepDuration = function(){};

    /**
     *
     */
    this.drawDuration = function(){};

    /**
     *
     */
    this.sepPriority = function(){};


    /**
     *
     */
    this. = function(){};

    /**
     *
     */
    this. = function(){};

    /**
     *
     */
    this. = function(){};

    /**
     *
     */
    this. = function(){};

    /**
     *
     */
    this. = function(){};

    /**
     *
     */
    this. = function(){};



    /**
     * @type {Boolean}
     */
    this.autoRefresh = 0;

    
     
    return this;
}
