#ifndef AABB__
#define AABB__
#include "collider.h"

class AABB : public Collider {
private:
  Vec3<float> p;
  Vec3<float> r;
public:
  AABB (Vec3<float> pos, Vec3<float> radius);
  Vec3<float> intersectA(Collider & other);
  bool intersectB(Collider & other);
  Vec3<float> getPos();
  Vec3<float> getRadius();
  virtual ~AABB ();
};

#endif
