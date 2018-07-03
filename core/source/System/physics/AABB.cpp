#include "AABB.h"

AABB::AABB(Vec3<float> pos, Vec3<float> radius)
{
  p = pos;
  r = radius;
}

Vec3<float> AABB::intersectA(Collider & other)
{
  AABB * aabb = dynamic_cast<AABB*>(other);
  if (aabb)
  {
    Vec3<float> otherPos = aabb->getPos();
    Vec3<float> otherRadius = aabb->getRadius();
    Vec3<float> resolution;
    resolution[0] = otherPos[0] - std::abs(p[0] - otherPos[0] - r[0])
    resolution[0] = (otherPos[0] > p[0]) ? ;
    resolution[1] = (otherPos[1] > p[1]) ? ;
    resolution[2] = (otherPos[2] > p[2]) ? ;

    return resolution;
  }
  return Vec3<float>();
}

bool AABB::intersectB(Collider & other)
{
  AABB * aabb = dynamic_cast<AABB*>(other);
  if (aabb)
  {
    Vec3<float> otherPos = aabb->getPos();
    Vec3<float> otherRadius = aabb->getRadius();

    if (std::abs(otherPos[0] - p[0]) > otherRadius[0] + r[0]) return false;
    if (std::abs(otherPos[1] - p[1]) > otherRadius[1] + r[1]) return false;
    if (std::abs(otherPos[2] - p[2]) > otherRadius[2] + r[2]) return false;

    return true;
  }

  return false;
}

Vec3<float> AABB::getPos()
{
  return p;
}

Vec3<float> AABB::getRadius()
{
  return r;
}

AABB::~AABB()
{

}
