#ifndef SCENE__
#define SCENE__
#include <vector>
#include "System/module.h"
#include "System/Engine/EngineObjects/object.h"

class Scene
{
protected:
  std::vector<Object*> objects;
  std::vector<Module*> modules;
public:
  Scene (std::vector<Object*> startObjects, std::vector<Module*> startModules);
  void addModule(Module * module);
  void addObject(Object * object);
  virtual void update();
  virtual ~Scene ();
};
#endif
