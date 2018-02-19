#ifndef MATRIXBUFFEROBJECT__
#define MATRIXBUFFEROBJECT__
#include "matrix.h"
struct MatrixBufferObject
{
  Matrix<float> mvp;
  Matrix<float> modelView;
  Matrix<float> normal;
  char pad[64];
  MatrixBufferObject(Matrix<float>& mvp, Matrix<float>& modelView, Matrix<float>& normal)
  {
    this->mvp = mvp;
    this->modelView = modelView;
    this->normal = normal;
  }
};
#endif
