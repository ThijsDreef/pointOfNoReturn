#ifndef COLLISIONCOMPONENT__
#define COLLISIONCOMPONENT__

#include "System/Physics/collider.h"
#include "System/Physics/resolver.h"
#include "System/Engine/EngineObjects/transform.h"

class CollisionComponent : public Component
{
private:
  Collider * coll;
  Transform * transform;
  bool moveAble;
public:
  CollisionComponent (bool isStatic, Collider * collider, Transform * transform, Object * object);
  void setResolver(std::string resolver);
  bool getStatic();
  Collider * getCollider();
  virtual ~CollisionComponent ();
  void update();
};

#endif
