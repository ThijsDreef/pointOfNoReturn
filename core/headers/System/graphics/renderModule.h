#ifndef RENDERMODULE__
#define RENDERMODULE__
#include "System/module.h"
#include "System/Graphics/matrixBufferer.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "Math/matrix.h"
#include "System/Graphics/MatrixBufferObject.h"
#include "System/Graphics/buffer.h"
#include "Util/util.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Window/wglew.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/EngineObjects/camera.h"
#include <iostream>
#include <math.h>
#include <utility>

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
