#include "object.h"

Object::Object(std::vector<Component*> comp)
{
  components = comp;
}

Object::~Object()
{
  for (unsigned int i = 0; i < components.size(); i++)
    delete components[i];
}

bool Object::empty()
{
  return (components.size() == 0);
}

void Object::addComponent(Component * component)
{
  components.push_back(component);
}

void Object::updateComponents()
{
  for (unsigned int i = 0; i < components.size(); i++)
  {
    if (components[i]->isRemoved())
    {
      components.erase(components.begin() + i);
      i--;
    }
    if (components[i]->isDead())
      continue;
    components[i]->update();
  }
}
