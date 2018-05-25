/*  A Basic example that shows how to draw simple 2D shapes
    2014, Johnathan Corkery
 */


// First, we want to create our window on the system.
window = sandboxe.view.createDisplay("circle");
sandboxe.view.setMain(window);





// then create a new entity. Entities are the objects that 
// sandboxe interacts with directly. 
circle = sandboxe.entity.create();
sandboxe.engine.setRoot(circle);





// Shapes are drawn through the Shape2D component.
// Components are attachable containers that work off of 
// host entities to grant more functionality. After 
// creation, they need to be attached to make sure the 
// component gets updated with the entity.
circle.shape = sandboxe.component.shape2d.create();
circle.addComponent(circle.shape);

// Color objects can be created from RGB integers, or via
// a string (either the name, or the ubiquitous rgb/rgba hex string with leading '#')
circle.shape.color = 'cyan';

// Now that we have the color of the shape, lets decide what
// the type of the shape is. Shape2D supports basic and complex shapes, 
// but lets just start with a basic rectangle
circle.shape.formCircle(diameter = 200, numSides = 70);


// The Graphics object controls render-ing related attributes, such 
// as the camera. Note that the rendering resolution can differ from the 
// user's window, so we query the rendering camer'as resolution height
centerY = sandboxe.graphics.getRenderCamera().height / 2.0;
centerX = sandboxe.graphics.getRenderCamera().width  / 2.0;


// Let's center the object to the screen. Every entity has a default 
// component called a node. Nodes hold psitional, scale, and rotation 
// information for entities. Note that some components can even have
// their own nodes, such as the shape2d component.
circle.node.position.x = centerX;
circle.node.position.y = centerY;



// To make the example more interesting, lets have the object rotate around.
// Every entity object has an onStep() function. When populated, the function 
// will be called every step of the program. Here, we're going to modify the 
// rotation.
circle.onStep = function() {
    circle.node.rotation.x += 0.4;
    circle.node.rotation.y += 0.5;
    circle.node.rotation.z += 0.3;
}




