#include "AABBComponent.h"

AABBComponent::AABBComponent(AABB aabb, Transform * t, Object * object) : Component(object)
{
  bb = aabb;
  transform = t;
}

AABBComponent::~AABBComponent()
{

}

void AABBComponent::update()
{
  bb.setPos(transform->getPos());
}
