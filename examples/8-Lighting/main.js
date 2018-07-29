/*  A example that shows how to work with lighting
    2018, Johnathan Corkery
 
    Since this example is more complicated, let's go over what we want it to 
    show. This demo will demonstrate a simple scene that has the following things:
     - A moveable camera 
     - A ground / floor in 3D space
     - An object loaded from a model file
     - A "sky light"
     - A light in 3D space

    All are annotated below in how they work

 */
 

// First, we want to create our window on the system.
window = sandboxe.display.create("Lighting Example");
sandboxe.display.setMain(window);

// We are going to have multiple independent objects in this example, 
// so this is a good time to talk more in-depth about the entity hierarchy.
// Entities are organized in a tree-like way: the program has a root entity,
// and each entity can have its own children. The transforms of each child are 
// inherited.
root = sandboxe.entity.create();
sandboxe.engine.setRoot(root);



// Let's start with the camera.
// Since we're working in 3D space, it will be helpful to let the user 
// move around where they want. We are mapping the controls to WASD and EQ
// to control movement in X Y Z.
// Since this example is more complex, ive used anonymous functions to 
// generate each entity and keep them separate. 
camera = (function(){
    var ent = sandboxe.entity.create();
    ent.name = 'Light_Camera';
    
    // lets get local voersions of these namespaces so we save 
    // on some access time and some typing
    var buttonListener = sandboxe.input.buttonListener;
    var target = ent.node.position;
    
    // This camera will actively update the graphics render camera 
    // to match this position. We are going to space this camera out 
    // away from the scene to start with.
    ent.node.position = '0, .5, 7';
    
    
    // Here we quickly define the key mappings for X Y Z movement.
    // This should be review from the input tutorial.
    buttonListener.create(sandboxe.key_w).onHold = function(){target.y += .4;};
    buttonListener.create(sandboxe.key_s).onHold = function(){target.y -= .4;};
    buttonListener.create(sandboxe.key_a).onHold = function(){target.x -= .4;};
    buttonListener.create(sandboxe.key_d).onHold = function(){target.x += .4;};
    buttonListener.create(sandboxe.key_e).onHold = function(){target.z -= .4;};
    buttonListener.create(sandboxe.key_q).onHold = function(){target.z += .4;};


    // On the step function, we will have the camera "ease" toward the camera.
    // This will make the movement a lot more smooth
    ent.onStep = function() {
        
        // 3D has a separate camera from 2D operations since the positional spaces are 
        // different (Screen-coordinate space vs. World space)
        var position = sandboxe.graphics.getCamera3d().node.position; 
        
        position.x = sandboxe.ease(position.x, ent.node.position.x, .1);
        position.y = sandboxe.ease(position.y, ent.node.position.y, .1);
        position.z = sandboxe.ease(position.z, ent.node.position.z, .1);
    }
    
    // Return the new object form the anonymous function
    return ent;
})();



// Then lets make An object that represents the ground 
ground = (function(){
    var ent = sandboxe.entity.create();
    ent.name = 'Light_Ground';
    
    // When working wit 3D geometry, we'll need to work with the renderMesh component.
    // It is the 3D counterpart of shape2d and is generaic to all 3d operations.
    ent.mesh = ent.addComponent(sandboxe.component.type.renderMesh);
    
    // For renderMesh objects to function, we need to supply 3D geometry.
    // In this example, we are goin gto make an object by hand! We will 
    // be supplying a mesh object as a result of another anonymouse function
    ent.mesh.addMesh((function(){
        
        // Mesh objects hold 3d geometry information. 
        var mesh = sandboxe.mesh.create();
        
        // Before defining vertices, the mesh needs to know how many vertices 
        // the shape will have, so we set it here.
        mesh.vertexCount = 4;
        
        // 3D vertices have a few different "data channels" that help express data: 
        // position, normals, UV (texture coordinates), and UserData. In this example 
        // we will by expressing lighting, so we will want positional and normal data.

        // The ground is a simple square, so the coordinates are straightfoward.
        // We want it to be large, so each side of the square is 2000 units.
        mesh.defineVertices(
            sandboxe.mesh.vertexAttribute.position,
            [
                -1000, 0, -1000,
                 1000, 0, -1000,
                 1000, 0,  1000,
                -1000, 0,  1000
            ]
        );
        
        // Since the ground is a flat square, the normals are simply pointing upward
        mesh.defineVertices(
            sandboxe.mesh.vertexAttribute.normal,
            [
                0, 1, 0,
                0, 1, 0,
                0, 1, 0,
                0, 1, 0
            ]
        );
        
        // Now that we have the supplied vertices, we need to specify the actual 
        // vertex list to form triangles of the solid object.  This are just indices 
        // into the vertices that we specified above
        mesh.addObject([
            0, 1, 2, // first triangle
            2, 3, 0  // second triangle
        ]);
        
        // now that the mesh is finished, we return the mesh object
        return mesh;
    })());

    // Dont forget! when specifying 3D geometry, you also have freedom over 
    // what primitive you want to use to express the 3D data.
    // 99% of the time, triangles are the most appropriate.
    ent.mesh.primitive = sandboxe.component.renderMesh.polygon.triangle;


    

    // Well, now that we specified the geometry, we need to tell sandboxe 
    // how to display the actual 3d object. We need material data.
    // Since this is a lighting example, lets make a material that responds to 
    // lights.
    
    // Recall that in the phong lighting model, there are 3 main colors for 
    // lighting material: ambient, diffuse, and speculr colors.
    
    // Ambient specifies the base color in absence of light or from ambient 
    // reflection. Usually this should be dark.
    ent.mesh.material.ambient = sandboxe.color.create(.05, .05, .05, 1);
    
    // Diffuse light is general light impact from a light at a wide angle.
    ent.mesh.material.diffuse = sandboxe.color.create(.4, .4, .4,    1);;
    
    // Specular light is the "highlight" colors when the eye position is closely 
    // alight with the surface reflection normal. This is where the light is the 
    // brightest.
    ent.mesh.material.specular = sandboxe.color.create(.8 , .8 , .8,  1);;
    
    // Shininess of the surface. Higher number means more shiny
    ent.mesh.material.shininess = 16;
    
    // The program of the material is essentially the "rendering engine" to 
    // use for the object. sandboxe provides 2 defaults, basic and lighting. 
    // It is possible to generate your own using shaders. This is shown in 
    // the next example
    ent.mesh.material.program = sandboxe.material.coreProgram.lighting;
    
    
    // Since its a ground, lets lower the position of the object.
    ent.node.position.y = -1;
    
    // All done!!
    return ent;
})();






model = (function(){
    
    // Models are an asset that can handle geometry and material information.
    // Once loaded, the appear in a staging "model" asset object.
    // There, you can modify / examine the model file's geometyr and material 
    // before using it. Once ready to use, you can "create" an entity that represents 
    // the whole object
    var modelRef = sandboxe.assets.load('obj', 'test.obj').get();

    
    // By default the model's material is flat. We want to modify it to have lighting 
    // So, we will just use the ground material we made from scratch and apply to each 
    // section of the mesh.
    for(var i = 0; i < modelRef.sectionCount; ++i) {
        modelRef.setSectionMaterial(i, ground.mesh.material);        
    }
    
    // This produces an entity that represents the whole model we loaded. 
    // Recall that models can come in different sections. An entity is able to 
    // encapsulate everything needed.
    var ent =  modelRef.create();
    
    // Give it a useful name so we can observe it in the debugger
    ent.name = 'Light_Model';
    
    // lets rotate it slowly, make it more interesting     
    ent.onStep = function() {
        ent.node.rotation.y += .02;
    }
    
    // all done!
    return ent;
})();


// Now that we have some geometry that can respond to light, Let's actually 
// add lights to the scene.
//
// Sandboxe can currently work with 2 types of lights by default:
// point lights (light at a specific point in space) and directional light 
// (light uniformaly distributed from a location-indendent direction).
// This example will use both to show the effects of each type.
//
// This first object will be our directional light. It will be blue in the scene
skyLight = (function(){
    // Make the entity like usual!
    var out = sandboxe.entity.create();
    
    // Lights are maintained using renderLight components, so lets create one.
    var directional = out.add('renderLight');
    
    // This first example will be a directional light, so the type should be set accordingly.
    directional.type = sandboxe.component.renderLight.type.directional;

    // Every light has an intensity. You'll need to play around with it 
    // to get an intensity you like.
    directional.intensity = 2.0;
    
    // Every light also can have its own color. This will interact with the 
    // material colors.
    directional.color = sandboxe.color.create(.2, .35, .47, 1);
    
    // For a directional light, the "position" is the directional vector 
    // in 3D space. Since positions are X Y Z, this is pointing "down" (negative y)
    // and "back" (negative z)
    directional.position = '{0, -1, -.4}';
    
    // Don;t forget to name this object!!
    out.name = 'Light_SkyLight';

    // All done!
    return out;
})();



// finally lets make the point light.
// The properties of each type of light are the same.
light = (function(){
    // The entity object that will hold the light
    var out = sandboxe.entity.create();
    
    // Like before lets set these properties.
    var point = out.add('renderLight');
    point.type = sandboxe.component.renderLight.type.point;
    point.intensity = 20;
    
    // this light will be green to let you see the different effects of 
    // each light
    point.color = '#00FF00';
    
    // Lets move this light up and towards the camera
    point.position = '0, 1, 3';

    // Set the name as usual
    out.name = 'Light_PointLight';
    
    // Finish!
    return out;
})();


// And finally, add all our entities to the scene.
// Since they will be children of an entity set as the root, 
// The will be updated automatically for us.
root.attach(ground);
root.attach(camera);
root.attach(model);
root.attach(skyLight);
root.attach(light);

