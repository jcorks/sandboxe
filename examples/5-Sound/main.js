/*  A Basic example that shows how to play sounds
 */


// First, we want to create our window on the system.
window = sandboxe.view.createDisplay("Sound Example");
sandboxe.view.setMain(window);




// Load resources
// Dynacoe by default can recognize WAVs and OGGs.
// Here we have 3 samples that we are going to play
kickSound  = sandboxe.assets.load("wav", "kick.wav");
snareSound = sandboxe.assets.load("wav", "snare.wav");
clangSound = sandboxe.assets.load("wav", "clang.wav");




// We're also going to draw some visuals, one for each sound 
// Using the circle function, we are going to make a hexagon to represent each sound
// 
kickShape  = sandboxe.component.shape2d.create();
kickShape.formCircle(radius=50, iters=6);
kickShape.color = 'orange';

snareShape = sandboxe.component.shape2d.create();
snareShape.formCircle(radius=50, iters=6);
snareShape.color = 'cyan';

clangShape = sandboxe.component.shape2d.create();
clangShape.formCircle(radius=50, iters=6);
clangShape.color = 'grey';



// Lets put them on the screen. Since theyre circlebased, theyre centered 
// already. We can just divide the screen up
kickShape.node.position.x = sandboxe.graphics.getRenderCamera().width  *.25; 
kickShape.node.position.y = sandboxe.graphics.getRenderCamera().height * .25;

snareShape.node.position.x = sandboxe.graphics.getRenderCamera().width   * .75;
snareShape.node.position.y = sandboxe.graphics.getRenderCamera().height  * .25;

clangShape.node.position.x = sandboxe.graphics.getRenderCamera().width   * .5;
clangShape.node.position.y = sandboxe.graphics.getRenderCamera().height  * .75;


// finally lets make just one entity to hold everything.
// Add the components we made.
entity = sandboxe.entity.create();
entity.addComponent(kickShape);
entity.addComponent(snareShape);
entity.addComponent(clangShape);
sandboxe.engine.setRoot(entity);







var kickSample = undefined;
var snareSample = undefined;
var clangSample = undefined;
entity.onStep = function() {
    
    
    // To actually play a sound, we can call PlayAudio() to immediately hear it. 
    // The Sound modules handles all audio. We're using the simple frame-based input querying 
    // though, inputListeners are usually recommended.
    // We've mapped each sound to a key.
    if (sandboxe.input.isPressed(sandboxe.key_q)) {
        kickSample = sandboxe.sound.playAudio(kickSound);
    }

    if (sandboxe.input.isPressed(sandboxe.key_w)) {
        snareSample = sandboxe.sound.playAudio(snareSound);
    }

    if (sandboxe.input.isPressed(sandboxe.key_e)) {
        clangSample = sandboxe.sound.playAudio(clangSound);
    }



    // Now, we're going to make some "spice" to make it more interesting.
    // The goal is to have each visual react to its sound. This example will 
    // expand the shape for the duration of the sample's playback.
    // We check to see if the sample is playing by using the result 
    // from sandboxe.sound.playAudio(), which is a reference to the active sound.
    kickScale = (kickSample && kickSample.valid ? 2.0 : .5);
    snareScale = (snareSample && snareSample.valid ? 2.0 : .5);
    clangScale = (clangSample && clangSample.valid ? 2.0 : .5);
    
    snareShape.node.scale.x = sandboxe.component.mutator.step(snareShape.node.scale.x, snareScale, .1);
    snareShape.node.scale.y = snareShape.node.scale.x; 

    kickShape.node.scale.x = sandboxe.component.mutator.step(kickShape.node.scale.x, kickScale, .1);
    kickShape.node.scale.y = kickShape.node.scale.x; 

    clangShape.node.scale.x = sandboxe.component.mutator.step(clangShape.node.scale.x, clangScale, .1);
    clangShape.node.scale.y = clangShape.node.scale.x; 

}



// here's a reminder for the user
sandboxe.console.info("Press Q, W, and E!" << "\n");


