#include "basicScene.h"

BasicScene::BasicScene(std::vector<Object*> startObjects, std::vector<Module*> startModules)
{
  objects = startObjects;
  modules = startModules;
  for (unsigned int i = 0; i < modules.size(); i++)
    for (unsigned int j = 0; j < objects.size(); j++)
      modules[i]->addObject(objects[j]);
}

BasicScene::~BasicScene()
{

}

void BasicScene::update()
{
  for (unsigned int i = 0; i < modules.size(); i++)
    modules[i]->update();
  for (unsigned int i = 0; i < objects.size(); i++)
    if (!objects[i]->empty())
      objects[i]->updateComponents();
}
