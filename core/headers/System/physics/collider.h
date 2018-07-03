#ifndef COLLIDER__
#define COLLIDER__
#include "vec3.h"

class Collider {
private:

public:
  Collider ();
  virtual ~Collider ();
  virtual bool intersectB(Collider * other);
  virtual Vec3<float> intersectA(Collider * other);
};

#endif
