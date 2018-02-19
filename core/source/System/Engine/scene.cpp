#include "scene.h"

Scene::Scene()
{

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
