#ifndef DEFFEREDRENDERMODULE__
#define DEFFEREDRENDERMODULE__
#include "System/module.h"
#include "System/Graphics/matrixBufferer.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "System/Graphics/MatrixBufferObject.h"
#include "Math/matrix.h"
#include "System/Graphics/buffer.h"
#include "Util/util.h"
#include "System/Engine/EngineObjects/transform.h"
#include "System/Window/glew.h"
#include "System/Engine/EngineObjects/object.h"
#include <math.h>
#include <utility>
#include "System/Engine/EngineObjects/camera.h"
#include "System/Graphics/Resources/fbo.h"

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
  int w, h;
public:
  DefferedRenderModule (GeometryLib * geo, MaterialLib * mat, ShaderManager * shader, int width, int height);
  virtual ~DefferedRenderModule ();
  void update();
  void drawGeometry(std::vector<std::vector<std::pair<unsigned int, Transform*>>> & renderList, bool materials);
  void updatePerspective(int width, int height, int fov, float near, float far);
  void addObject(Object * object);
  Matrix<float> * getCameraMatrix();
};
#endif
