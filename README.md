Point of no return
--------
#### Make commands

- clean:
  - deletes the build directories
- init
  - creates a build folder
  - creates all subdirectories in build from core/source
- build
 - builds the game to run.exe in exe/

### Documentation

- [structure](#structure)
- [Point of no Return](#Point-of-no-Return)
  - [Engine](#engine)
  - [Scene](#scene)

### structure

**Point of no Return** works trough the use of a entity component system.
You only need to create a [Engine](#engine) and a [Scene](#Scene) then start the engine
with the scene you wish to use. All Objects in the Scene will be added to all modules inside of the current scene then proceeded to be updated at a target rate of the refresh rate held by the Engine.

### Point of no Return

Here you will find all objects explained in more detail.

### engine

Engine is the main class that handles the game loop.

methods
- constructor
  - Engine(std::string title, int width, int height, int bitDepth, bool fullScreen, double frameCap);
  - all variables used to Initiliaze a Window Object for Engine
  - frameCap is set here
  - Engine(double frameCap)
- start([Scene](#Scene))
  - starts the engine
  - does not return
  - pushes the scene on top of the [Scene](#Scene) stack
  - internally calls Engine.run(); to start the game loop
- quit()
  - sets running to false wich stops the main loop


### Scene

Scene is a basic container class wich needs to be extended to create your own scenes

methods
- constructor
  - defaultConstructor
- addModule([Module *](#module))
  - adds the module pointer to a std::vector with all [Modules](#module)
- addObject([Object *](#object))
  - adds the Object pointer to a std::vector with all [Objects](#object)
- virtual void update();
  - used when overriding to update your scene
