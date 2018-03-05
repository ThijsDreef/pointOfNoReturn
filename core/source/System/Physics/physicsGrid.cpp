#include "physicsGrid.h"

PhysicsGrid::PhysicsGrid(float maxWidth, int cellSize)
{
  cSize = cellSize;
  float stepSize = (maxWidth / cellSize) * 2;
  cStepsize = stepSize;
  cells.reserve(cellSize * cellSize);
  for (int i = 0; i < cellSize * cellSize; i++) cells.push_back(PhysicsCell());
}

PhysicsGrid::~PhysicsGrid()
{

}
int PhysicsGrid::getGrid(Vec3<float> pos)
{
  float fx = pos[0] / cStepsize;
  float fy = pos[2] / cStepsize;
  int x = (fx > 0) ? (int) fx + 0.5 : (int)fx -0.5;
  int y = (fy > 0) ? (int) fy + 0.5 : (int)fy -0.5;
  return x + cSize * y;
}

void PhysicsGrid::trickle(Point * point)
{
  cells[getGrid(point->getPos())].trickle(point);
}

void PhysicsGrid::trickle(Body * body)
{
  cells[getGrid(body->getAveragePos())].trickle(body);
}

PhysicsCell & PhysicsGrid::getPhysicsCell(int x, int y)
{
  return cells[x + y * cSize];
}
