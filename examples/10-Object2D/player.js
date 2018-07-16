// player.js
// Allows to make a new player object that responds to input 
// and can collide with obstables


sandboxe.script.include('sparks.js');


// Creates the player obejct. position is the starting position of the 
// object and the diameter is the diameter of the object
createPlayer = function(position, diameter) {
    var entity = sandboxe.entity.create();

    // To prepare, we are going to add the components right away.
    // clock provides timing utilities and object2d provides 
    // advanced 2d movement and interactions.
    var object2d       = entity.add('object2d');    
    var collisionTimer = entity.add('clock');
    var shape          = entity.add('shape2d');

    entity.name = "player";
    entity.node.position = position;

    // Set the timer to expire after 100 ms.
    collisionTimer.set(100);
    
    // sets the friction for the movement, which reduces 
    // the velocity preserved each frame.
    object2d.frictionX = .01;
    object2d.frictionY = .01;

    // Adds a hook, which gives a function to be called when 
    // a certain event is triggered on a component. All 
    // components support events and hooks, including the ability 
    // to add your own events. See the documentation for components.
    object2d.installHook('on-collide', function(o2d, self, other){


        // Since collisions can happen every frame, we are going to 
        // have the collision logic occur every 100 ms at maximum.
        if (collisionTimer.expired) {
            
            // To make the collision feel more impactful, 
            // we have a spark effect be emitted at the position of the collision
            // See sparks.js
            createSparks(
                entity.node.position, 
                object2d.direction+180, // object2d.direction is the direction fo movement
                object2d.speed / 10.0   // object2d.speed is the directionless velocity of the object
            );

            // to emulate physics, we are going to split the velocity of the 
            // player upon collisions and donate it to all members of the collision             
            // Each object is propelled in opposite directions 
            
            object2d.setVelocity(
                object2d.speed*.6,
                object2d.direction+180
            );
            
            
            // Note that if the object members are not accessible, functions like 
            // "queryComponent" can retrieve components regardless of symbol name.
            other.queryComponent('Object2D').addVelocity(
                object2d.speed*.4,
                object2d.direction+180
            )
            
            // Reset the timer so we can record more events
            collisionTimer.reset();
        }
    });

    // To have collisions, the object2d object needs to have colliders to register 
    // when and where collisions can occur. Colliders are invisible, but have tangible geometry.
    // You specify each object2d's collider by setting its "collider" property 
    // as an array of line positions:
    object2d.collider = [

        0, 0, 
        diameter, 0,        
        diameter, diameter,
        0,  diameter

    ];
    
    // the visual is a circle that is blue
    shape.formRectangle(
        diameter,
        diameter

    );
    shape.color = 'cyan';



    // lets add movement using object2d velocities mapped to arrow keys
    var listenerUp = sandboxe.input.buttonListener.create(sandboxe.key_up);
    var listenerDown = sandboxe.input.buttonListener.create(sandboxe.key_down);
    var listenerLeft = sandboxe.input.buttonListener.create(sandboxe.key_left);
    var listenerRight = sandboxe.input.buttonListener.create(sandboxe.key_right);

    
    listenerUp.onHold = function() {
        object2d.addVelocity(.3, -90);
    }

    listenerDown.onHold = function() {
        object2d.addVelocity(.3, 90);
    }

    listenerLeft.onHold = function() {
        object2d.addVelocity(.3, 180);
    }

    listenerRight.onHold = function() {
        object2d.addVelocity(.3, 0);
    }


    // public:
    entity.shape = shape;
    entity.object2d = object2d;    
    game.root.attach(entity);
}















