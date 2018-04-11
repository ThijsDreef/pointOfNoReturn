#include "characterController.h"

CharacterController::CharacterController(Vec3<float> * target, Vec3<float> * rotation, Vec3<float> limits, float steps, Input * input, Object * object) : Component(object)
{
  this->target = target;
  this->steps = steps;
  this->input = input;
  this->rotation = rotation;
  object->subscribe("collided", this);
  limit = limits;
}

CharacterController::~CharacterController()
{

}

void CharacterController::update()
{
  rot = rot.rotation(*rotation);
  //87 == w
  if (input->getKeyDown(87))
  {
    direction[2] -= limit[2] / steps;
    if (direction[2] < -limit[2]) direction[2] = -limit[2];
  }
  // 83 == s
  else if (input->getKeyDown(83))
  {
    direction[2] += limit[2] / steps;
    if (direction[2] > limit[2]) direction[2] = limit[2];
  }
  // 65 == a
  if (input->getKeyDown(65))
  {
    direction[0] -= limit[0] / steps;
    if (direction[0] < -limit[0]) direction[0] = -limit[0];
  }
  //68 == d
  else if (input->getKeyDown(68))
  {
    direction[0] += limit[0] / steps;
    if (direction[0] > limit[0]) direction[0] = limit[0];
  }
  //applying space to jump
  if ((input->getKeyDown(32) && jump) || goingUp)
  {
    gravity += (gravity - -limit[1] * 2) * 0.4;
    jump = false;
    goingUp = true;
    if (gravity >= limit[1] * 3)
      goingUp = false;
  }
  gravity -= (gravity - -limit[1]) * 0.15;
  gravity = (gravity > -limit[1]) ? gravity : -limit[1];
  direction[1] = gravity;
  target->lerp(rot.multiplyByVector(direction), 0.25);
  direction.lerp(Vec3<float>(0, 0, 0), 0.1);

}

void CharacterController::receiveMessage(const std::string & message, void* data)
{
  if (message == "collided")
  {
    jump = true;
    gravity = 0;
  }
}
