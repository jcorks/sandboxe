/*  A Basic example that shows how to draw simple 2D shapes
    2014, Johnathan Corkery
 */


// First, we want to create our window on the system.
window = sandboxe.view.createDisplay("Particle Example");
sandboxe.view.setMain(window);


particle = sandboxe.entity.create();

// test.part in this directory holds the specification for the particle.
// Try editing it to see what different effects you can achieve.
// Check the notes in test.part (comments start with a #)
particle.asset = sandboxe.assets.load("part", "test.part");

// Create and attach the emitter to this entity.
// Particle emitters are their own entity objects, so the will need to be 
// added to the object hierarchy in some way. 
particle.emitter = sandboxe.particleEmitter2D.create();
particle.attach(particle.emitter);
particle.name = 'particle';


var filtered = true;
var translucent = true;

particle.onStep = function() {
    // Lets have the emitter always match the mouse's position  
    particle.node.local.position.x = sandboxe.input.mouseX();
    particle.node.local.position.y = sandboxe.input.mouseY();
    
    //... and let's have the emitter activate when the user clicks.
    if (sandboxe.input.getState(sandboxe.input.mouse_left)) {
        particle.emitter.emitParticle(particle.asset);
    }
    
    
    
    // Pressing 'tab' should toggle whether to enable texture filtering for particles.
    // When texture filtering is enabled, the pixels of the image of the particle are 
    // blended together. When it's disabled, it tends to give a grainy look, but 
    // will also run faster on some machines. The default when emitting is to use 
    // filtering.
    if (sandboxe.input.isPressed(sandboxe.input.key_tab)) {
        particle.emitter.filtered = !particle.emitter.filtered;
        sandboxe.console.info((particle.emitter.filtered ? "Enabled" : "Disabled") + " filtering!\n");
    }

    // Pressing the spacebar will toggle whether to draw the particles in a translicent manner.
    // In this context, "translucency" is equivalent to additive blending, where transparent colors
    // are added together. The event is layered, transparent images appear lighter in color to more 
    // are drawn in one place. The default when emitting is to draw translucently.
    if (sandboxe.input.isPressed(sandboxe.input.key_space)) {
        particle.emitter.translucent = !particle.emitter.translucent;
        sandboxe.console.info((particle.emitter.translucent ? "Enabled" : "Disabled") + " translucency!\n");
    }
}


sandboxe.engine.setRoot(particle);

/*
public:
  Dynacoe::AssetID particle;

  // The emitter for the particles
  Dynacoe::ParticleEmitter2D * particleEmitter;

  ParticlesExample() {

      // test.part in this directory holds the specification for the particle.
      // Try editing it to see what different effects you can achieve
      particle        = Assets::Load("part", "test.part");

      // Create and attach the emitter to this world
      particleEmitter = Dynacoe::Entity::CreateChild<ParticleEmitter2D>(); 
      particleEmitter->SetName("ParticleExample");
  }

  void OnStep() {

      // Lets have the emitter always match the mouse's position
      particleEmitter->node.local.position = {Input::MouseX(), Input::MouseY()};


      //... and let's have the emitter activate when the user clicks.
      if (Input::GetState(Dynacoe::MouseButtons::Left)) {
          particleEmitter->EmitParticle(particle);
      }


      // Thats all we need! Below controls some extra options that could be helful to know.



      // Pressing 'tab' should toggle whether to enable texture filtering for particles.
      // When texture filtering is enabled, the pixels of the image of the particle are 
      // blended together. When it's disabled, it tends to give a grainy look, but 
      // will also run faster on some machines. The default when emitting is to use 
      // filtering.
      if (Input::IsPressed(Dynacoe::Keyboard::Key_tab)) {
          static bool b = false;
          particleEmitter->EnableFiltering(b);
          Console::Info() << (b ? "Enabled" : "Disabled") << " filtering!" << Console::End;
          b = !b;
      }

      // Pressing the spacebar will toggle whether to draw the particles in a translicent manner.
      // In this context, "translucency" is equivalent to additive blending, where transparent colors
      // are added together. The event is layered, transparent images appear lighter in color to more 
      // are drawn in one place. The default when emitting is to draw translucently.
      if (Input::IsPressed(Dynacoe::Keyboard::Key_space)) {
          static bool b = false;
          particleEmitter->EnableTranslucency(b);
          Console::Info() << (b ? "Enabled" : "Disabled") <<  " translucency!" << Console::End;
          b = !b;
      }

  }
*/
