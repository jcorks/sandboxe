/*  A example that shows how to work with shaders
    2018, Johnathan Corkery
 
 */
 

// First, we want to create our window on the system.
window = sandboxe.display.create("Shader Example");
sandboxe.display.setMain(window);



// In this example, we will have one entity drawn as a cube 
// with a shader being used to colorfully paint its surfaces
example = (function(){
    
    // Create the entity
    var ent = sandboxe.entity.create();

    // Since we're workign with 3D, lets add a mesh renderer
    ent.renderer = ent.add('renderMesh');
    
    // In the previous example, we added our own meshes, one 
    // from scratch, and one from a file. Here, we will use a 
    // built-in function to generate a basic mesh.
    ent.renderer.addMesh(sandboxe.mesh.createCube());
    
    
    // Since we're working with external data, this is a good time to 
    // use the inputBuffer utility. inputBuffers allow you to read binary and 
    // text data. We will use 2, one for each shader source file.
    var vertexSrc = sandboxe.inputBuffer.create();
    var fragmentSrc = sandboxe.inputBuffer.create();
    
    // Lets open these file to transfer their data into memory
    // Recall that the GLSL shader model includes a vertex processing stage 
    // and a fragment processing stage. 
    vertexSrc.open('cube_vertex.glsl');
    fragmentSrc.open('cube_fragment.glsl');
    
    // Create the object representing the custom shader program
    var program = sandboxe.shader.create();

    // Lets read and add the vertex shader. You can view its source 
    // within cube_vertex.glsl
    program.addStage(
        sandboxe.shader.stage.vertexProcessor,
        vertexSrc.readString(vertexSrc.size)
    );

    // Lets read and add the fragment shader. You can view its source 
    // within cube_fragment.glsl
    program.addStage(
        sandboxe.shader.stage.fragmentProcessor,
        fragmentSrc.readString(fragmentSrc.size)
    );
    
    // Now we can comile the program.
    program.compile();
    
    // Lets make sure the compilation was successful
    if (program.status != sandboxe.shader.status.success) {
        sandboxe.console.error(program.log + '\n');
        return undefined;
    }

    // Now that everything looks good, we can use the program. 
    // Shader objects are used by setting the 'program' component.
    // In the previous example, we would populate this with either 
    // sandboxe.material.coreProgram.basic|lighting, which are 
    // built-in programs that sandboxe provides.
    ent.renderer.material.program = program;


    // Lets make the object bigger so we can see whats going on. 
    // Note that we didn't change the position, so both the cube and 
    // the camera are at the origin, and the 
    ent.node.scale = '3, 3, 3';
    
    
    
    // To make it more interesting, we will slowly rotate the object
    ent.onStep = function() {
        ent.node.rotation.x += .1;
        ent.node.rotation.y += .1;
        ent.node.rotation.y += .1;
    };
    return ent;
})();




// Lets add this to the engine!
sandboxe.engine.setRoot(example);










