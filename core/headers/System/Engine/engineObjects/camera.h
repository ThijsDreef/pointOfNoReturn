#ifndef CAMERA__
#define CAMERA__
#include "System/Engine/EngineObjects/component.h"
#include "Math/matrix.h"
class Camera : public Component
{
private:
  Matrix<float> * camera;
public:
  Camera (Object * object);
  void setMatrix(Matrix<float> * mat);
  Matrix<float> * getMatrix();
  virtual ~Camera ();
};
#endif
