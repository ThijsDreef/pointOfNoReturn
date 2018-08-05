#ifndef RESOLVER__
#define RESOLVER__
#include "collider.h"

class Resolver {
public:
  Resolver ();
  virtual ~Resolver ();
  virtual void resolve(Collider * self, Collider * other);
};

#endif
