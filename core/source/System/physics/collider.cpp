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
