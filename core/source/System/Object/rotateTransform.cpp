#include "rotateTransform.h"

RotateTransform::RotateTransform(Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Vec3<float> rotSpeed, Input * input, Object* object)
:
Transform(pos, scale, rot, model, materials, object)
{
  this->input = input;
  input->setMouseLock(true);
  rotationSpeed = rotSpeed;
}

void RotateTransform::update()
{
  if (input->getMouseButtonDown(0))
  {
    rotationSpeed[0] = (input->getDy() / 3);
    rotationSpeed[1] = (input->getDx());
    lastX = input->getDx();
    lastY = input->getDy();
  }
  else
  {
    rotationSpeed[0] = 0;
    rotationSpeed[1] = 0;
  }
  if (input->getKeyDown(37))
    pos[2] += 0.01f;
  if (input->getKeyDown(38))
    pos[0] += 0.01f;
  if (input->getKeyDown(39))
    pos[2] -= 0.01f;
  if (input->getKeyDown(40))
    pos[0] -= 0.01f;
  rot = rot + rotationSpeed;
}

RotateTransform::~RotateTransform()
{

}
