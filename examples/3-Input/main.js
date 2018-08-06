/*  An example that demonstrates
    input from the keyboard and mouse.


    2014, Johnathan Corkery
*/




// First, we want to create our window on the system.
window = sandboxe.display.create("Console Example");
sandboxe.display.setMain(window);


// The idea of the example is to get something onscreen to respond to input,
// so we are are going to have a small square move around based on inputs 
// supplied by the user. First, create the entity
inputExample = sandboxe.entity.create();
inputExample.name = 'inputExample';
inputExample.node.position.x = 100;
inputExample.node.position.y = 100
sandboxe.engine.setRoot(inputExample);

// Then create the square itself and center it.
inputExample.visual = inputExample.addComponent(sandboxe.component.type.shape2d);
inputExample.visual.formRectangle(width = 10, height = 10);
inputExample.visual.node.position = '{-5, -5}';
inputExample.visual.color = 'white';



// We're going to have our Entity move in response
// to the left and right arrow keys.

// There are multiple ways to have sandboxe respond to input. One 
// such efficient way is to add buttonListeners. buttonListeners 
// call specified functions once the input is picked up by the system. 

// First, create the listener
listenerLeft = sandboxe.input.buttonListener.create(sandboxe.key_left);

// Populate the onPres, onRelease, and /or onHold properties.
// Here we only care about onHold
listenerLeft.onHold = function() {
    inputExample.node.position.x -= 2;
}




// Repeat same steps for the right key 
listenerRight = sandboxe.input.buttonListener.create(sandboxe.key_right);

// Populate the onPres, onRelease, and /or onHold properties.
// Here we only care about onHold
listenerRight.onHold = function() {
    inputExample.node.position.x += 2;
}



// Along with button listeners, you can also query exact button states 
// of a control per frame. Doing so is less efficient, but can be useful
// and more flexible than listeners.
inputExample.onStep = function() {
    
    // lets make it so that you can drag the box horizontally
    if (sandboxe.input.isHeld(sandboxe.mouse_left)) {
        inputExample.node.position.x = sandboxe.input.mouseX();
    }
}



