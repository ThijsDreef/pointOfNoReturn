#include "System/Engine/scene.h"

Scene::Scene(std::vector<Object*> startObjects, std::vector<Module*> startModules)
{
  objects = startObjects;
  modules = startModules;
  for (unsigned int i = 0; i < modules.size(); i++)
    for (unsigned int j = 0; j < objects.size(); j++)
      modules[i]->addObject(objects[j]);
}

Scene::~Scene()
{
  for (unsigned int i = 0; i < modules.size(); i++)
    delete modules[i];
  for (unsigned int i = 0; i < objects.size(); i++)
    delete objects[i];
}

void Scene::update()
{
  for (unsigned int i = 0; i < objects.size(); i++)
    if (!objects[i]->empty())
      objects[i]->updateComponents();
  for (unsigned int i = 0; i < modules.size(); i++)
    modules[i]->update();
}

void Scene::addObject(Object * object)
{
  for (unsigned int i = 0; i < modules.size(); i++)
    modules[i]->addObject(object);
  objects.push_back(object);
}

void Scene::addModule(Module * module)
{
  for (unsigned int i = 0; i < objects.size(); i++)
    module->addObject(objects[i]);
  modules.push_back(module);
}
