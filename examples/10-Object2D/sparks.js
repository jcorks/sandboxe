// sparks.js 
// creates a visual-only effect. (Note: this would be more efficiently done 
// with a particle effect!!)

// Creates sparks from a collision. around is the position of the collision, 
// direction is the direction of the force generated, and force is the 
// apparent force of the collision
var sparkCache = [];

createSparks = function(around, direction, force) {
    if (sparkCache.length == 0) {
        for(var i = 0; i < 30; ++i) {        
            sparkCache.push(
                (function(){



                    // This object just has a shape and an object2d
                    var entity = sandboxe.entity.create();
                    var shape  = entity.addComponent(sandboxe.component.type.shape2d);
                    var o2d    = entity.addComponent(sandboxe.component.type.object2d);

                    // we also set the original location to be the given "around" 
                    // position, aka, where the effect is happening
                    entity.name = "spark";



                    // as time goes out, the scale gets smaller and 
                    // its color fades out. If the color is below a certain amount, 
                    // the spark removes itself
                    entity.onStep = function() {
                        entity.node.scale.x *= .92;
                        entity.node.scale.y *= .92;

                        shape.color.a *= .84;
                        if (shape.color.a < .06) {
                            game.root.detach(entity);

                        }
                        
                    };
        
                    // add to root
                    entity.shape = shape;
                    entity.o2d = o2d;
                    return entity;

                })()
            );
        }
    }

    // Since this spark is made up of a variable number of 
    // individual sparks, this function is used to create a single spark.
    var makeSingleSpark = function(entity) {
        game.root.attach(entity);



        entity.node.position = around;
        
        // the base spark is just a stretched out write rectangle.
        entity.shape.formRectangle(30, 30);
        entity.shape.color = "white";

        // we alter the scale to make the effect. The force of the 
        // effect makes the spark larger
        var scale = Math.random()*4.5 + .5;
        entity.node.scale.x = scale*force;
        entity.node.scale.y = .07*force;



        
        
        // To create variability, the direction and speed of the spark movements 
        // will be randomized. The general direction is a cone in the direction 
        // of the impact
        var dir = (Math.random()- .5)*180 + direction;
        entity.o2d.setVelocity(
            Math.random()*30+20,
            dir
        );
        
        // dont forget to rotate!
        entity.node.rotation.z = -dir;

    }
    
    

    // based on the force, we create a variable number of 
    // sparks
    var count = 18*force;
    if (count > 30) count = 30;
    for(var i = 0; i < count; ++i) {
        makeSingleSpark(sparkCache[i]);
    }
    
}
