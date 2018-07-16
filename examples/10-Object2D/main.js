/*
 A more substantial example that shows how to work with object2d,
 multiple scripts, and component event handling.
 

 */


// In more implex projects, it is useful to "include"
// scripts. Scripts are are only included one time. 
// When included, all the contents of the script 
// are run.
sandboxe.script.include("game.js");


// Creates the window
window = sandboxe.display.create("Testing!!");
sandboxe.display.setMain(window);



sandboxe.console.info('(Spacebar resets the example.)\n');
sandboxe.console.info('Use the arrow keys to hit the object!\n');


// Resets the game. see game.js
game.reset();



