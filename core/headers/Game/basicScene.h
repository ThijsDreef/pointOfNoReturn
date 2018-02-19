#ifndef BASICSCENE__
#define BASICSCENE__
#include "scene.h"
class BasicScene : public Scene
{
private:
public:
  BasicScene(std::vector<Object*> startObjects, std::vector<Module*> startModules);
  virtual ~BasicScene();
  void update();
};
#endif
