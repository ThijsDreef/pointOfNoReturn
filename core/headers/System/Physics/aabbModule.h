#ifndef AABBMODULE__
#include "aabb.h"
#include "module.h"
#include "object.h"
#include "implicidGrid.h"
#include <iostream>

class AabbModule : public Module
{
private:
  std::vector<Aabb*> colliders;
  ImplicidGrid grid;
  unsigned int size;
public:
  AabbModule(unsigned int gridSize);
  ~AabbModule();
  void update();
  void addObject(Object * object);
};
#endif
