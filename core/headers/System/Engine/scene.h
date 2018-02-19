#ifndef SCENE__
#define SCENE__
#include <vector>
#include "module.h"
#include "object.h"

class Scene
{
protected:
  std::vector<Object*> objects;
  std::vector<Module*> modules;
public:
  Scene ();
  void addModule(Module * module);
  void addObject(Object * object);
  virtual void update();
  virtual ~Scene ();
};
#endif
