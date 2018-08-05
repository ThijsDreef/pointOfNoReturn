#ifndef AABB__
#define AABB__
#include "collider.h"
#include <math.h>

class AABB : public Collider {
private:
  Vec3<float> p;
  Vec3<float> r;
public:
  AABB (Vec3<float> pos, Vec3<float> radius);
  AABB ();
  Vec3<float> intersectA(Collider * other);
  bool intersectB(Collider * other);
  Vec3<float> getPos();
  Vec3<float> getRadius();
  void setPos(Vec3<float> pos);
  void setRadius(Vec3<float> rad);
  virtual ~AABB ();
};

#endif
