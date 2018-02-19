#ifndef CAMERA__
#define CAMERA__
#include "component.h"
#include "matrix.h"
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
