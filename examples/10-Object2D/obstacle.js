// obstacle.js 
// Creates an obstacle object for the player to interact with

// Creates an obstacle object that can get hit around by the player
createObstacle = function(position, diameter) {
    var entity   = sandboxe.entity.create();
    var object2d = entity.add('object2d');
    var shape    = entity.add('shape2d');
    
    entity.name = "obstacle";
    entity.node.position = position;
    
    object2d.collider = [
        0, 0, 
        diameter, 0,        
        diameter, diameter,
        0,  diameter


    ]

    // like the player, let its velocity fade out over time using 
    // the friction attributes
    object2d.frictionX = .01;
    object2d.frictionY = .01;
    
    // To make collisions more impactful, any collision briefly changes the 
    // color to a light pink
    object2d.installHook("on-collide", function() {
        shape.color.r = 1.0;
        shape.color.b = 1.0;
        shape.color.g = .3;
        
    });
    
    // Another circle!
    shape.formRectangle(
        diameter,
        diameter
    );
    shape.color = 'black';
    shape.color.g = .3;


    // We also fade out the red and blue component colors.
    // This restores the color to recreate the flash effect from collisions
    entity.onStep = function() {
        shape.color.r *= .86;
        shape.color.b *= .86;
    }
        
    entity.shape = shape;
    entity.object2d = object2d;
    game.root.attach(entity);
}
