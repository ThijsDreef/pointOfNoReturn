#include "vec3.h"
#include <math.h>
#include "aabbResolver.h"
#include "component.h"

enum CollisionAxis {LEFT, RIGHT, UP, DOWN, FRONT, BACK};

class Aabb : public Component
{
private:
  Vec3<float> & position;
  AabbResolver * resolver;
public:
  Vec3<float> velocity;
  Vec3<float> radius;
  Aabb (Vec3<float> & position, Vec3<float> radiuses, AabbResolver * resolver, Object * object);
  int getCollisionAxis(Vec3<float> & pos);
  bool intersect(Aabb & other);
  void resolve(Aabb & other);
  Vec3<float> & getPos();
  virtual ~Aabb ();
};
