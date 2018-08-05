#include "collisionComponent.h"

CollisionComponent::CollisionComponent(bool isStatic, Collider * collider, Transform * t, Object * object) : Component(object)
{
  moveAble = isStatic;
  coll = collider;
  transform = t;
}

CollisionComponent::~CollisionComponent()
{

}

void CollisionComponent::update()
{
  coll->syncPos(transform->getPos());
}

bool CollisionComponent::getStatic()
{
  return moveAble;
}

Collider * CollisionComponent::getCollider()
{
  return coll;
}

void CollisionComponent::setResolver(std::string resolver)
{
  coll->setResolver(resolver);
}
