#include "point.h"

Point::Point(Vec3<float> & pos, Vec3<float> rad, bool isStatic, Object * object) : Component(object)
{
  position = pos;
  radius = rad;
  this->isStatic = isStatic;
}

Point::~Point()
{

}

Vec3<float> & Point::getRadius()
{
  return radius;
}

Vec3<float> Point::getPos()
{
  return position;
}

void Point::applyForce(Vec3<float> other)
{
  force += other;
}

void Point::moveForce(float delta)
{
  actualForce.lerp(force, 0.5);
  actualForce *= 0.99f;
  force *= 0.99f;
  position += delta * actualForce;

}

bool Point::checkCollision(Point & point)
{
  float dx = std::abs(position[0] - point.getPos()[0]);
  if (dx < point.getRadius()[0] + radius[0])
    return true;
  float dy = std::abs(position[1] - point.getPos()[1]);
  if (dy < point.getRadius()[1] + radius[1])
    return true;
  float dz = std::abs(position[2] - point.getPos()[2]);
  if (dz < point.getRadius()[2] + radius[2])
    return true;
  return false;
}

bool Point::getStatic()
{
  return isStatic;
}
