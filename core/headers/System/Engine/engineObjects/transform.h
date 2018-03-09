#ifndef TRANSFORM__
#define TRANSFORM__
#include "matrix.h"
#include "component.h"
#include "object.h"
#include <string>
#include "matrixBufferObject.h"
#include <iostream>

class Transform : public Component
{
protected:
  Vec3<float> pos;
  Vec3<float> scale;
  Vec3<float> rot;
public:
  std::vector<std::string> materials;
  std::string model;
  unsigned int bufferIndex;
  Transform (std::string model, std::vector<std::string> materials, Object * object);
  Transform (Vec3<float> pos, Vec3<float> scale, Vec3<float> rot, std::string model, std::vector<std::string> materials, Object * object);
  Vec3<float> & getPos();
  Vec3<float> & getScale();
  Vec3<float> & getRot();
  MatrixBufferObject getBuffer(Matrix<float>& view, Matrix<float>& p);
  virtual ~Transform ();
};
#endif
