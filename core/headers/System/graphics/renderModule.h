#ifndef RENDERMODULE__
#define RENDERMODULE__
#include "module.h"
#include "matrixBufferer.h"
#include "shaderManager.h"
#include "matrix.h"
#include "MatrixBufferObject.h"
#include "buffer.h"
#include "util.h"
#include "transform.h"
#include "wglew.h"
#include "object.h"
#include <iostream>
#include <math.h>
#include <utility>
#include "camera.h"

class RenderModule : public Module
{
private:
  GeometryLib * geoLib;
  MaterialLib * matLib;
  MatrixBufferer bufferer;
  ShaderManager * shaderManager;
  std::vector<Transform*> renderObjects;
  Matrix<float> projection;
  Matrix<float> camera;
  void setUpFormat();
public:
  void update();
  Matrix<float> * getCameraMatrix();
  void updatePerspective(int width, int height, int fov, float near, float far);
  void addObject(Object * transform);
  RenderModule (GeometryLib * geo, MaterialLib * mat, ShaderManager * shader);
  virtual ~RenderModule ();
};
#endif
