#include "physicsCell.h"

PhysicsCell::PhysicsCell()
{
  bodies.reserve(5);
  points.reserve(10);
}

PhysicsCell::~PhysicsCell()
{
  
}

void PhysicsCell::trickle(Body * body)
{
  bodies.push_back(body);
}

void PhysicsCell::trickle(Point * point)
{
  points.push_back(point);
}

std::vector<Body*> & PhysicsCell::getBodies()
{
  return bodies;
}

std::vector<Point*> & PhysicsCell::getPoints()
{
  return points;
}
