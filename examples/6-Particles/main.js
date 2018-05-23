/*  A Basic example that shows how to draw simple 2D shapes
    2014, Johnathan Corkery
 */


// First, we want to create our window on the system.
window = sandboxe.view.createDisplay("Particle Example");
sandboxe.view.setMain(window);



particle = sandboxe.entity.create();
particle.asset = sandboxe.assets.load("part", "test.part");
particle.emitter = sandboxe.particleEmitter2D.create();
particle.attach(particle.emitter);
particle.name = 'particle';

particle.onStep = function() {
    particle.node.local.position.x = sandboxe.input.mouseX();
    particle.node.local.position.y = sandboxe.input.mouseY();
    if (sandboxe.input.getState(sandboxe.input.mouse_left)) {
        particle.emitter.emitParticle(particle.asset);
    }
}


sandboxe.engine.setRoot(particle);

/*
public:
  // Once we load the particle, this will hold the reference to it.
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
