#ifndef ROTATETRANSFORM__
#define ROTATETRANSFORM__
#include "transform.h"
#include "input.h"
#include "orbitalCamera.h"
#include "object.h"
class RotateTransform : public Transform
{
private:
  Vec3<float> rotationSpeed;
  int lastX, lastY;
  Input * input;
public:
  RotateTransform (Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Vec3<float> rotSpeed, Input * input, Object * object);
  void update();
  virtual ~RotateTransform ();
};
#endif
