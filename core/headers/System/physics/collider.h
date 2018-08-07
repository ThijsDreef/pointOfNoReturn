#ifndef COLLIDER__
#define COLLIDER__
#include "vec3.h"
#include <string>
class Collider {
private:
  Vec3<float> * posPointer;
  Vec3<float> p;
public:
  std::string resolve = "default";
  Collider ();
  virtual ~Collider ();
  virtual bool intersectB(Collider * other);
  virtual Vec3<float> intersectA(Collider * other);
  void setResolver(std::string resolver);
  void setPos(Vec3<float> & pos);
  Vec3<float> & getPos();
  void syncPos(Vec3<float> * pos);
};

#endif
