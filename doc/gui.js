/**
 * @class gui
 * @extends component
 * @description
 * A component that provides managed input interaction suitable for 
 * making things like buttons, text boxes, etc.
 *
 * Known {@link component} events:</br>
 * <pre>
 * - "on-click"
 * - "on-press"
 * - "on-release"
 * - "on-enter"
 * - "on-leave"
 * - "on-hover"
 * - "on-drag"
 * - "on-focus"
 * - "on-unfocus"
 * </pre>
 *
 * 
 */ 
function gui() {

    /**
     * Attempts to grab the input focus for this GUI.
     *
     * If a GUI grabs the input focus, other GUI's will not have input events pushed 
     * to them. See {@link sandboxe.component.gui.ungrabInput} to ungab input from all gui objects globally.
     */
    this.grabInput = function(){};

    /**
     * Sets this GUI to be the focused widget.
     *
     * Focusing has no inate effect on the GUI except for the return values 
     * from the focus-related set of properties and events.
     */
    this.setFocus = function(){};





    /**
     * The text to appear above a widget if the mouse hovers over it.
     * @type {String}
     */
    this.tooltipText = 0.0;

    /**
     * The width of the gui in 2D coordinates.
     * @type {Number}
     */
    this.width = 0.0;

    /**
     * The height of the gui in 2D coordinates.
     * @type {Number}
     */
    this.height = 0.0;

    /**
     * Whether the gui is focused. This property is read-only.
     * @type {Boolean}
     */
    this.focused = false;

    /**
     * Whether the pointer is hovered over the gui's region. This property is read-only.
     * @type {Boolean}
     */
    this.hovered = false;

    /**
     * Returns whether the user is attempting to drag this gui.
     * @type {Boolean}
     */
    this.beingDragged = false;

    /**
     * The local node of this component.
     * @type {transform}
     */
    this.node = {};




    return this;
}
