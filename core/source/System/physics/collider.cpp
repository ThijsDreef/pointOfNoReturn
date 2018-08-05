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

void Collider::syncPos(Vec3<float> & pos)
{
  p = pos;
}
