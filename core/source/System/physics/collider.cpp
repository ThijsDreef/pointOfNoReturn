#include "collider.h"

Collider::Collider()
{

}

Collider::~Collider()
{

}

bool Collider::intersectB(Collider * other)
{
  return false;
}

Vec3<float> Collider::intersectA(Collider * other)
{
  return Vec3<float>();
}

void Collider::setResolver(std::string resolver)
{
  resolve = resolver;
}

void Collider::setPos(Vec3<float> & pos)
{
  p = pos;
}

Vec3<float> & Collider::getPos()
{
  if (posPointer)
    return *posPointer;
  else
    return p;
}

void Collider::syncPos(Vec3<float> * pos)
{
  posPointer = pos;
}

std::string & Collider::getResolver()
{
  return resolve;
}
