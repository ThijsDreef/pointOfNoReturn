Point of no return
--------
#### Make commands

- clean:
  - deletes the build directories
- init
  - creates a build folder
  - creates all subdirectories in build from core/source
- -
 - builds the game to run.exe in exe/

### Documentation

- [structure](#structure)
- [Point of no Return](#Point-of-no-Return)
  - [Engine](#engine)
  - [Scene](#scene)

### structure

**Point of no Return** works trough the use of a entity component system.
You only need to create a [Engine](#engine) and a [Scene](#Scene) then start the engine
with the scene you wish to use. All Objects in the Scene will be added to all modules inside of the current scene then proceed to be updated at a target rate of the refresh rate held by the Engine.

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
- getters
  - getGeoLib();
  - getMatLib();
  - getShaderManger();
  - getInput();


### Scene

Scene is a basic container class wich needs to be extended to create your own scenes.

methods
- addModule([Module *](#module))
  - adds the module pointer to a std::vector with all [Modules](#module)
- addObject([Object *](#object))
  - adds the Object pointer to a std::vector with all [Objects](#object)
- virtual void update();
  - used when overriding to update your scene


### module

Module is a base class wich needs to be extended to create your own modules.

methods
- virtual void update()
  - the method that gets called every frame to update this module
- virtual void addObject([Object*](#object))
  - will be used to add [Objects](#object) to this module
  - use [Object](#object).getComponent<>() to check if a object has the desired components for this module
  - add based on if you want to do anything with this Object

### object

Object is the class that holds all Components. Object adds functionality to the list of components trough its methods

methods
- Object(std::vector<Component*>)
  - creates a Object with the list of components
- void updateComponents()
  - calls [component](#component).update() for every component added
  - gets called only by the current [Scene](#scene) if supported by [Scene](#scene)
- bool empty()
  - if the object has no [Component](#component) (left) returns true
- void addComponent([Component*](#component))
  - adds the component to the internal list of object
- void removeComponent<>()
  - removes the first instance found of the template class
- void removeComponent<>(int toSkip)
  - removes the component found after it already found toSkip number of objects
- T * getComponent<>()
  - returns the first instance of the T class found
  - else returns 0

### component

Component is a base class wich needs to be extended to create your own Component.
It provides a garbage collection if used in the Modules that check for garbage collection used in

methods
- Component([Object*](#object))
  - saves the parent in the base class as a protected variable
- bool isDead()
  - returns true if setDead() has been called
- void setDead()
  - sets dead to true;
- void added()
  - increases refCounter
  - call when you add this component to a Module
- void setRemoved()
  - decreases refCounter
- void isRemoved()
  - returns true if no module has a reference and the container can be deleted
