#ifndef ENGINE__
#define ENGINE__
#include "window.h"
#include "geometryLib.h"
#include "shaderManager.h"
#include "scene.h"
#include "util.h"
#include "materialLib.h"
#include "input.h"
#include <stack>
#include <chrono>
class Engine {
private:
  Window window;
  GeometryLib geometryLib;
  MaterialLib materialLib;
  ShaderManager shaderManager;
  Input * input;
  std::stack<Scene*> scene;
  bool running;
  double frameCap;

public:
  Engine (std::string title, int width, int height, int bitDepth, bool fullScreen, double frameCap);
  Engine (double frameCap);
  void start(Scene * start);
  void run();
  void stop();
  GeometryLib * getGeoLib();
  MaterialLib * getMatLib();
  ShaderManager * getShaderManger();
  Input * getInput();
  virtual ~Engine ();
};
#endif
