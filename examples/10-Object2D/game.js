// game.js 
// Handles and holds the references to the whole example 

sandboxe.script.include('player.js');
sandboxe.script.include('obstacle.js');


game = (function(){
    var obj = {};
    // game.root will hold the root entity that all other entities 
    // attach to.
    obj.root = sandboxe.entity.create();
    obj.root.name = 'root';



    // Let's add a "reset" function. This will remove any existing 
    // objects and add the default objects back to an original state.
    obj.reset = function() {
        
        // Remove existing objects
        var list = game.root.getChildren();
        for(var i = 0; i < list.length; ++i) {
            list[i].remove();
        }
        
        // See player.js
        createPlayer('400, 200', diameter=40);

        // See obstacle.js
        createObstacle('200, 200', diameter=100);
    }


    // For additional ease of use, lets map this reset function to run 
    // when the space bar is pressed
    var resetter = sandboxe.input.buttonListener.create(sandboxe.key_space);
    resetter.onPress = function() {
        obj.reset();
    };


    // never forget to set the root!!
    sandboxe.engine.setRoot(obj.root);
    
    return obj;
})();

