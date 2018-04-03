#ifndef AABB__
#define AABB__
#include "vec3.h"
#include <math.h>
#include "aabbResolver.h"
#include "component.h"
#include <string>

enum CollisionAxis {LEFT = 0, RIGHT = 1, UP = 2, DOWN = 3, FRONT = 4, BACK = 5};

class Aabb : public Component
{
private:
  Vec3<float> & position;
  AabbResolver * resolver;
public:
  std::string name;
  Vec3<float> velocity;
  Vec3<float> radius;
  Aabb (Vec3<float> & position, Vec3<float> radiuses, AabbResolver * resolver, const std::string tag, Object * object);
  int getCollisionAxis(Vec3<float> & pos);
  bool intersect(Aabb & other);
  void resolve(Aabb & other);
  void update();
  Vec3<float> & getPos();
  virtual ~Aabb ();
};
#endif
