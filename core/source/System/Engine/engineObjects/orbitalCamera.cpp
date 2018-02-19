#include "orbitalCamera.h"

OrbitalCamera::OrbitalCamera(float offset, Vec3<bool> locked, Vec3<float> camRot, Vec3<float> * rotation, Vec3<float> * pos, Object * object) : Camera(object)
{
  this->offset = offset;
  this->locked = locked;
  rot = camRot;
  rotPoint = rotation;
  posPoint = pos;
}

OrbitalCamera::~OrbitalCamera()
{

}

void OrbitalCamera::update()
{
  getMatrix()->translateMatrix(Vec3<float>(0, 0, offset));
  Matrix<float> temp;
  if (locked[0])
    temp.setAxisrotation(rot[0], X);
  else
    temp.setAxisrotation(-(*rotPoint)[0] + rot[0], X);
  *getMatrix() = getMatrix()->multiplyByMatrix(temp);
  if (locked[2])
    temp.setAxisrotation(rot[2], Z);
  else
    temp.setAxisrotation(-(*rotPoint)[2] + rot[2], Z);
  *getMatrix() = getMatrix()->multiplyByMatrix(temp);
  if (locked[1])
    temp.setAxisrotation(rot[1], Y);
  else
    temp.setAxisrotation(-(*rotPoint)[1] + rot[1], Y);
  *getMatrix() = getMatrix()->multiplyByMatrix(temp);
  temp.translateMatrix(Vec3<float>(-(*posPoint)[0], -(*posPoint)[1], -(*posPoint)[2]));
  *getMatrix() = getMatrix()->multiplyByMatrix(temp);
}

float * OrbitalCamera::getOffset()
{
  return &offset;
}
