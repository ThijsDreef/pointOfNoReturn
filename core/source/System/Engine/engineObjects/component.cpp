#include "component.h"

Component::Component(Object * object)
{
  this->object = object;
}

Component::~Component()
{

}

void Component::start()
{
  
}
bool Component::isDead()
{
  return dead;
}

bool Component::isRemoved()
{
  return refCounter < 0;
}

void Component::setDead()
{
  dead = true;
}

void Component::setRemoved()
{
  refCounter--;
}

void Component::added()
{
  refCounter++;
}

void Component::update()
{

}
