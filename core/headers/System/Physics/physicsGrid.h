#ifndef PHYSICSGRID__
#define PHYSICSGRID__

#include "physicsCell.h"

class PhysicsGrid
{
private:
  int cSize;
  int cStepsize;
  std::vector<PhysicsCell> cells;
  int getGrid(Vec3<float> pos);
public:
  PhysicsGrid (float maxWidth, int cellSize);
  virtual ~PhysicsGrid ();
  void trickle(Point* point);
  void trickle(Body* body);
  PhysicsCell & getPhysicsCell(int x, int y);
};
#endif
