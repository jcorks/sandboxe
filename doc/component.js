/**
 * @class component
 * @description
 * Extends the functionality of an {@link entity} as a swappable object. </br></br>
 *
 * To work, all components have hosts; when a host updates, all components do as well.
 * Like {@link entity}, a component can have a Draw and a Step function with an overloadable
 * OnStep / OnDraw. In addition, all component's also have event handling capabilities.
 * Setable with strings, it is possible to maintain and assign functions to run on 
 * certain events and even define your own events for custom components.</br></br>
 *  
 * When making your own components, you will typically also want to include 
 * your own custom events. installEvent() is the function that adds 
 * a new recognized event with the given name. Once installed, emitEvent() should be called 
 * at the appropriate time user functions should be run. </br></br>
 *
 * All components will emit the 2 fallowing events:
 * <pre>
 * - on-attach: Called when the component is attached to an entity.
 * - on-detach: Called when the component is about to be destroyed.
 * </pre>
 *
 * Built-in components, like {@link clock}, have their installed events marked in their 
 * class descriptions.
 * @example 
 
 
 *
 */ 
function component() {

    /**
     * Does the naturally defined step iteration. This invokes the "onStep" property method
     * if defined. For built-in components, this may trigger native code.
     * For hosts that are part of the engine hierarchy, step() is called for you when 
     * the entity step()s.
     */
    this.step = function(){};

    /**
     * Does the naturally defined draw iteration. This invokes the "onDraw" property method
     * if defined. For built-in components, this may trigger native code.
     * For hosts that are part of the engine hierarchy, draw() is called for you when 
     * the entity draw()s.
     */
    this.draw = function(){};

    /**
     * Adds a new event to be recognized by the EventSystem.
     *
     * if mainHandler is undefined, the event is still added, but has no default
     * handler is set. The default handler is always guaranteed to run last for the event.
     * @param {String} eventName The name of the new event to install.
     * @param {Function} mainHandler (optional) The default handler for this event. Always called first before any hooks. See {@link component.installHandler} for parameters passed to handler function objects.
     */
    this.installEvent = function(eventName, mainHandler){};

    /**
     * Removes the event from the component.
     * @param {String} event Event to remove.
     */
    this.uninstallEvent = function(event){};

    /**
     * Triggers the specified event for this component.
     *
     * Returns whether the event was allowed to propogate all the
     * way to the main handler (in other words, lets you know whether
     * all the handlers allowed the event to happen)
     * Source is passed to the handler and is usually the source of the event (but does not have to be)
     * @param {String} eventName Name of the event. This should match the name that was installed.
     * @param {entity} source (Optional) entity that indicates the source of the event. For example, in a collision, this may be the object collided with.
     */
    this.emitEvent = function(eventName, source){};

    /**
     * Returns whether the given event is installed.
     * @param {String} eventName The event to query.
     */
    this.canHandleEvent = function(eventName){};

    /**
     * Adds a hook to the event. 
     *
     * A hook happens at the end of a given event after all the
     * handlers have been run. Hooks occur regardless of event handler propogation.
     * Hook function signatures contain the following parameters: </br></br>
     * <pre>
     * hook(component, componentHost, eventSource)
     * </pre></br></br>
     * Where component is the this component, componentHost is the host entity of this component 
     * , and eventSource is the entity given from the emitEvent() call, if any.
     * @param {String} eventName Name of the installed event.
     * @param {Function} hook The hook to add. See class description for function signature.
     */
    this.installHook = function(eventName, hook){};

    /**
     * Removes the given hook.
     * @param {String} eventName
     */
    this.uninstallHook = function(eventName){};

    /**
     * Adds a handler to an event. 
     *
     * Handlers that are added are run in LIFO order
     * and their return values dictate whether the event should propogate.
     * The last handler run for an event is always the main handler of the event. </br>
     * Handler function signatures contain the following parameters: </br></br>
     * <pre>
     * {boolean} handler(component, componentHost, eventSource)
     * </pre></br></br>
     * Where component is the this component, componentHost is the host entity of this component 
     * , and eventSource is the entity given from the emitEvent() call, if any. The return value 
     * is a boolean determining if the event should continue propogating. If no return value is given, 
     * the value is assumed true, meaning the event should propogate.
     * @param {String} eventName Name of the installed event to add a handler to
     * @param {Function} handler Function to add as the handler.
     */
    this.installHandler = function(eventName, handler){};

    /**
     * Removes a previously installed handler.
     * @param {String} eventName
     */
    this.uninstallHandler = function(eventName){};

    /**
     * Returns a list of all events installed that can be processed.
     * @returns {Array} An array of event name strings.
     */
    this.getKnownEvents = function(){};




    /**
     * Function called on the step iteration of the component.
     * @type {Function}
     */
    this.onStep = {};

    /**
    * Function called on the draw iteration of the component.
     * @type {Function}
     */
    this.onDraw = {};
    
    /**
     * Function called when the component is attached to a host.
     * @type {Function}
     */
    this.onAttach = {};


    /**
     * Identifying tag of the component. The tag can be used in access functions such as {@link entity.queryComponent}.
     * @type {String}
     */
    this.tag = 0;

    /**
     * Human-readable information on this component viable in the inspector/debugger. 
     * For built-in components, this usually contains stats and useful info regarding the current 
     * state of the component.
     * @type {String}
     */
    this.info = 0;

    /**
     * Whether this component should have its step() function called automatically by the engine. 
     * The default is true.
     * @type {Boolean}
     */
    this.isStepping = 0;

    /**
     * Whether this component should have its draw() function called automatically by the engine. 
     * The default is true.
     * @type {Boolean}
     */
    this.isDrawing = 0;

    /**
     * The current host entity of the component. See {@link entity.addComponent}.
     * @type {entity}
     */
    this.host = 0;



    return this;
}
