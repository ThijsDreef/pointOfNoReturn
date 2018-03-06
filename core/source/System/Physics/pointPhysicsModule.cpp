#include "pointPhysicsModule.h"

PointPhysicsModule::PointPhysicsModule(float maxWidth, int cellSize) : grid(maxWidth, cellSize)
{
  gridSize = cellSize;
}

PointPhysicsModule::~PointPhysicsModule()
{

}

void PointPhysicsModule::update()
{
  //all cells check x+1
  //all cells check y+1
  //all cells check x+1 || y+1
  //if cell % 2 x-1||y-1
  for (unsigned int x = 0; x < gridSize; x++)
  {
    for (unsigned int y = 0; y < gridSize; y++)
    {
      if (x != gridSize -1)
        checkCells(grid.getPhysicsCell(x, y), grid.getPhysicsCell(x + 1, y));
      if (y != gridSize -1)
        checkCells(grid.getPhysicsCell(x, y), grid.getPhysicsCell(x, y + 1));
      if (x != gridSize -1 && y != gridSize -1)
        checkCells(grid.getPhysicsCell(x, y), grid.getPhysicsCell(x + 1, y + 1));

      // removeDynamic(grid.getPhysicsCell(x, y).getPoints());
    }
  }

}

void PointPhysicsModule::removeDynamic(std::vector<Point*> & points)
{
  unsigned int toPop = 0;
  for (unsigned int i = 0; i < points.size(); i++)
  {
    if (points[i]->getStatic())
    {
      std::swap(points[i], points[points.size() - 1 - toPop]);
      toPop++;
    }
  }
  std::vector<Point*> pop;
  pop.reserve(toPop);
  for (unsigned int i = 0; i < toPop; i++)
  {
    pop.push_back(points[points.size() - i]);
    points.pop_back();
  }
  for (unsigned int i = 0; i < pop.size(); i++)
    grid.trickle(pop[i]);

}

void PointPhysicsModule::checkCells(PhysicsCell & cell, PhysicsCell & other)
{
  checkAllPoints(cell.getPoints(), cell.getBodies());
  checkAllPoints(other.getPoints(), other.getBodies());
  checkPointsToPoints(cell.getPoints(), other.getPoints());
}

void PointPhysicsModule::checkPointsToPoints(std::vector<Point*> & points, std::vector<Point*> & other)
{
  for (unsigned int i = 0; i < points.size(); i++)
    for (unsigned int j = 0; j < other.size(); j++)
      if (checkPointPoint(*points[i], *other[j]))
        resolvePoints(*points[i], *other[j]);
}

void PointPhysicsModule::checkAllPoints(std::vector<Point*> & points, std::vector<Body*> & bodies)
{
  for (unsigned int i = 0; i < points.size(); i++)
  {
    for (unsigned int b = 0; b < bodies.size(); b++)
    {
      if (checkBodyPoint(*bodies[b], *points[i]))
      {
        resolveHeight(*bodies[b], *points[i]);
        break;
      }
    }
    for (unsigned int j = i + 1; j < points.size(); j++)
    {
      if (checkPointPoint(*points[i], *points[j]))
        resolvePoints(*points[i], *points[j]);
    }
  }
}

void PointPhysicsModule::addObject(Object * object)
{
  Point * point = object->getComponent<Point>();
  Body * body = object->getComponent<Body>();
  if (body)
  {
    body->added();
    grid.trickle(body);
  }
  if (point)
  {
    point->added();
    grid.trickle(point);
  }
}

void PointPhysicsModule::resolveHeight(Body & body, Point & point)
{
  float height = body.getHeight(point.getPos());
  point.getPos()[1] = height;
  std::cout << height;
}

void PointPhysicsModule::resolvePoints(Point & point, Point & other)
{

}

bool PointPhysicsModule::checkBodyPoint(Body & body, Point & point)
{
  return body.getCollision(point);
}

bool PointPhysicsModule::checkPointPoint(Point & point, Point & other)
{
  return point.checkCollision(other);
}
