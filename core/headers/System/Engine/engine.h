#ifndef ENGINE__
#define ENGINE__
#include "System/Window/window.h"
#include "System/Graphics/Geometry/geometryLib.h"
#include "System/Graphics/Shaders/shaderManager.h"
#include "System/Engine/scene.h"
#include "Util/util.h"
#include "System/Graphics/Geometry/materialLib.h"
#include "System/Input/input.h"
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
