#include "aabb.h"

Aabb::Aabb(Vec3<float> & position, Vec3<float> radiuses, AabbResolver * resolver, Object * object) : Component(object), position(position)
{
  radius = radiuses;
}

Aabb::~Aabb()
{
  if (resolver)
    delete resolver;
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
  float dx = pos[0] - position[0];
  float dy = pos[1] - position[1];
  float dz = pos[2] - position[2];
  float adx = std::abs(dx);
  float ady = std::abs(dy);
  float adz = std::abs(dz);
  if (adx < adz && adx < ady)
  {
    //return right or left
    if (dx > 0)
      return RIGHT;
    else
      return LEFT;
  }
  else if (ady < adz)
  {
    // return top or bottom
    if (dy > 0)
      return UP;
    else
      return DOWN;
  }
  else
  {
    // return front or back
    if (dz > 0)
      return FRONT;
    else
      return BACK;
  }
}
