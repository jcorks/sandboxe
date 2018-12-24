sandboxe.script.include('sparks.js');

wall = function(w, h) {
    var entity = sandboxe.entity.create();
    var object2d = entity.addComponent(sandboxe.component.type.object2d);
    var frame = 0;
    // Set the timer to expire after 100 ms.

    entity.name = "wall";
    object2d.collider = [
        0, 0,
        w, 0,
        w, h,
        0, h
    ];

    var reflect;
    if (h > w) {
        reflect = function(o2d) {
            o2d.velocityX = -1*o2d.velocityX;
        };
    } else {
        reflect = function(o2d) {o2d.velocityY = -1*o2d.velocityY;};
    }
    
    entity.onStep = function() {
        
        frame++;
    };


    // Adds a hook, which gives a function to be called when 
    // a certain event is triggered on a component. All 
    // components support events and hooks, including the ability 
    // to add your own events. See the documentation for components.
    object2d.installHook('on-collide', function(o2d, self, other){

        // Since collisions can happen every frame, we are going to 
        // have the collision logic occur every few frames
        if (frame >= 5) {

            if (other.name == 'wall') return;

            frame = 0;

            // Note that if the object members are not accessible, functions like 
            // "queryComponent" can retrieve components regardless of symbol name.
            var otherO2D = other.queryComponent('Object2D'); 

            reflect(otherO2D);
            
            createSparks(
                other.node.position, 
                otherO2D.direction+180, // object2d.direction is the direction fo movement
                otherO2D.speed / 10.0   // object2d.speed is the directionless velocity of the object
            );

        }

    });
    entity.object2d = object2d;
    game.root.attach(entity);    
    return entity;
} 
