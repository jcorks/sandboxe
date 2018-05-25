/*  A Basic example that shows how to work with images
 */


// First, we want to create our window on the system.
window = sandboxe.view.createDisplay("Image Example");
sandboxe.view.setMain(window);





// Create our single object that will hold the image
image = sandboxe.entity.create();
image.name = 'image';
sandboxe.engine.setRoot(image);




// First we need to load the the image into the program.
// To do that, we use Assets::Load. The first argument specifies
// what kind of file we are attempting to load, while the second should be the name of
// the file to load. Each kind of Asset type has a number of file types that
// are recognized. See Assets in the documentation for more information.

// Immediately after loading the image, we call FormImage to transform
// the imageAspect into a drawable rectangle showing the loaded image.
id = sandboxe.assets.load("png", "image.png");
image.shape = sandboxe.component.shape2d.create();
image.shape.formImage(id);
image.addComponent(image.shape);




// The origin of any 2d shape is 0, 0, or the top left.
// So, we want to center it to be useful. Do to so, we take advantage 
// of the image's own personal node object and set the 
// position to be 1/2 of its width and height
imageReference = id.get();
frame = imageReference.getFrame(0);
image.shape.node.position.x = frame.width  * -.5;
image.shape.node.position.y = frame.height * -.5;



// To make it interesting, we use some input to make 
// the image follow the mouse. There is a general function 
// belonging to the mutator that eases to values, which we use here.
image.onStep = function() {
    image.node.position.x = sandboxe.component.mutator.step(image.node.position.x, sandboxe.input.mouseX(), .1);
    image.node.position.y = sandboxe.component.mutator.step(image.node.position.y, sandboxe.input.mouseY(), .1);

    // To make it more interesting, we will secretly rotate the image based on the
    // difference in position of the Mouse pointer's position.
    image.node.rotation.z += sandboxe.input.mouseYDelta();
}


