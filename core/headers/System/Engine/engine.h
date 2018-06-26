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
  void run();
  void stop();
  bool running;
  double frameCap;
  int width, height;

public:
  int getWidth();
  int getHeight();
  Engine (std::string title, int iWidth, int iHeight, int bitDepth, bool fullScreen, double frameCap);
  Engine (double frameCap, int iWidth, int iHeight);
  void start(Scene * start);
  void quit();
  GeometryLib * getGeoLib();
  MaterialLib * getMatLib();
  ShaderManager * getShaderManger();
  Input * getInput();
  virtual ~Engine ();
};
#endif
