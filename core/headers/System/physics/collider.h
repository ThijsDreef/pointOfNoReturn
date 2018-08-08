#ifndef COLLIDER__
#define COLLIDER__
#include "vec3.h"
#include <string>
class Collider {
protected:
  Vec3<float> p;
  std::string resolve;
public:
  Collider ();
  virtual ~Collider ();
  virtual bool intersectB(Collider * other);
  virtual Vec3<float> intersectA(Collider * other);
  void setResolver(std::string resolver);
  void setPos(Vec3<float> & pos);
  std::string & getResolver();
  Vec3<float> & getPos();
  void syncPos(Vec3<float> * pos);
private:
  Vec3<float> * posPointer = nullptr;
};

#endif
