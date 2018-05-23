#ifndef DEFFEREDRENDERMODULE__
#define DEFFEREDRENDERMODULE__
#include "module.h"
#include "matrixBufferer.h"
#include "shaderManager.h"
#include "MatrixBufferObject.h"
#include "matrix.h"
#include "buffer.h"
#include "util.h"
#include "transform.h"
#include "glew.h"
#include "object.h"
#include <math.h>
#include <utility>
#include "camera.h"
#include "fbo.h"

class DefferedRenderModule : public Module
{
private:
  GeometryLib * geoLib;
  MaterialLib * matLib;
  MatrixBufferer matBufferer;
  ShaderManager * shaderManager;
  std::vector<Transform*> transforms;
  Fbo renderFbo;
  Fbo shadowFbo;
  Matrix<float> camera;
  Matrix<float> projection;
  void setUpFormat();
public:
  DefferedRenderModule (GeometryLib * geo, MaterialLib * mat, ShaderManager * shader);
  virtual ~DefferedRenderModule ();
  void update();
  void updatePerspective(int width, int height, int fov, float near, float far);
  void addObject(Object * object);
  Matrix<float> * getCameraMatrix();
};
#endif
