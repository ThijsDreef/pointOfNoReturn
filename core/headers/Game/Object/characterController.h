#ifndef CHARACTERCONTROLLER__
#define CHARACTERCONTROLLER__
#include "object.h"
#include "vec3.h"
#include "input.h"
#include "matrix.h"

class CharacterController : public Component
{
private:
  Vec3<float> * target;
  Vec3<float> limit;
  Vec3<float> * rotation;
  Vec3<float> direction;
  Matrix<float> rot;
  float gravity = 0;
  bool goingUp = false;
  bool jump = false;
  float steps;
  Input * input;
public:
  CharacterController (Vec3<float> * target, Vec3<float> * rotation, Vec3<float> limits, float steps ,Input * input, Object * object);
  virtual ~CharacterController ();
  void receiveMessage(const std::string & message, void* data);
  void update();
};

#endif
