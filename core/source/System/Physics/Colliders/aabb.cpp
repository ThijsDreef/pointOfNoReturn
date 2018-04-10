#include "aabb.h"
#include <iostream>

Aabb::Aabb(Vec3<float> & position, Vec3<float> radiuses, AabbResolver * resolver, const std::string tag, Object * object) : Component(object), position(position)
{
  name = tag;
  this->resolver = resolver;
  radius = radiuses;
}

Aabb::~Aabb()
{
}

bool Aabb::intersect(Aabb & other)
{
  if ((std::abs(position[0] - other.getPos()[0]) > radius[0] + other.radius[0])) return false;
  if ((std::abs(position[1] - other.getPos()[1]) > radius[1] + other.radius[1])) return false;
  if ((std::abs(position[2] - other.getPos()[2]) > radius[2] + other.radius[2])) return false;
  return true;
}

Vec3<float> & Aabb::getPos()
{
  return position;
}

void Aabb::resolve(Aabb & other)
{
  if (resolver)
    resolver->resolve(*this, other);
}

int Aabb::getCollisionAxis(Vec3<float> & pos)
{

  float dx = (position[0] + radius[0]) - pos[0];
  float dy = (position[1] + radius[1]) - pos[1];
  float dz = (position[2] + radius[2]) - pos[2];
  float adx = std::fabs(dx);
  float ady = std::fabs(dy);
  float adz = std::fabs(dz);
  if (adx < adz && adx < ady)
  {
    //return right or left
    if (dx < 0)
      return RIGHT;
    else
      return LEFT;
  }
  else if (ady < adz)
  {
    // return top or bottom
    if (dy < 0)
      return UP;
    else
      return DOWN;
  }
  else
  {
    // return front or back
    if (dz > 0)
      return BACK;
    else
      return FRONT;
  }
}

void Aabb::update()
{
  position += velocity;
}
