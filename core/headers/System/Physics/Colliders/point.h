#ifndef POINT__
#define POINT__
#include "component.h"
#include "vec3.h"
#include <math.h>

class Point : public Component
{
private:
  Vec3<float> position;
  Vec3<float> radius;
  Vec3<float> force;
  Vec3<float> actualForce;
  bool isStatic;
public:
  Point(Vec3<float> & pos, Vec3<float> rad, bool isStatic, Object * object);
  virtual ~Point();
  Vec3<float> & getRadius();
  Vec3<float> getPos();
  void moveForce(float delta);
  void applyForce(Vec3<float> other);
  bool checkCollision(Point & point);
  bool getStatic();
};
#endif
