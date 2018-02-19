#include "camera.h"

Camera::Camera(Object * object) : Component(object)
{

}

Camera::~Camera()
{

}

void Camera::setMatrix(Matrix<float> * mat)
{
  camera = mat;
}

Matrix<float> * Camera::getMatrix()
{
  return camera;
}
