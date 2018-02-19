#ifndef MATRIXBUFFERER__
#define MATRIXBUFFERER__
#include "buffer.h"
#include "transform.h"
#include "matrixBufferObject.h"
#include <vector>

class MatrixBufferer
{
private:
  unsigned int maxSize = 512;
  std::vector<MatrixBufferObject> bufferObjects;
  Buffer matrixBuffer;
public:
  int getBufferId();
  MatrixBufferer ();
  void setBuffer(std::vector<Transform*> & transforms, Matrix<float>& view, Matrix<float>& perspective);
  virtual ~MatrixBufferer ();
};
#endif
