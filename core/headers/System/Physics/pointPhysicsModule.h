#ifndef POINTPHYSICSMODULE__
#define POINTPHYSICSMODULE__
#include "module.h"
#include "object.h"
#include "physicsGrid.h"
#include <iostream>

class PointPhysicsModule : public Module
{
private:
  PhysicsGrid grid;
  unsigned int gridSize;
  bool checkBodyPoint(Body & body, Point & point);
  bool checkPointPoint(Point & point, Point & other);
  void resolveHeight(Body & body, Point & point);
  void resolvePoints(Point & point, Point & other);
  void checkCells(PhysicsCell & cell, PhysicsCell & other);
  void checkAllPoints(std::vector<Point*> & points, std::vector<Body*> & bodies);
  void checkPointsToPoints(std::vector<Point*> & points, std::vector<Point*> & other);
  void removeDynamic(std::vector<Point*> & points);
public:
  PointPhysicsModule (float maxWidth, int cellSize);
  virtual ~PointPhysicsModule ();
  void update();
  void addObject(Object * obj);
};
#endif
