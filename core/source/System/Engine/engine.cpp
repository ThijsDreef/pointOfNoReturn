#include "engine.h"

Engine::Engine(std::string title, int width, int height, int bitDepth, bool fullScreen, double frameCap)
:
window(title.c_str(), width, height, bitDepth, fullScreen)
{
  this->frameCap = frameCap;
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  shaderManager.createShaderProgram("shaders/defferedStandard.vert", "shaders/defferedStandard.frag", "deffered");
  shaderManager.createShaderProgram("shaders/standard.vert", "shaders/standard.frag", "standard");
  shaderManager.createShaderProgram("shaders/defferedFinish.vert", "shaders/defferedFinish.frag", "deffered-finish");
  UtilLoader::loadResources(geometryLib, materialLib);
  input = window.getInput();
}

Engine::Engine(double frameCap)
:
window("default", 1920, 1080, 32, true)
{
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  this->frameCap = frameCap;
  shaderManager.createShaderProgram("shaders/defferedStandard.vert", "shaders/defferedStandard.frag", "deffered");
  shaderManager.createShaderProgram("shaders/standard.vert", "shaders/standard.frag", "standard");
  shaderManager.createShaderProgram("shaders/defferedFinish.vert", "shaders/defferedFinish.frag", "deffered-finish");

  UtilLoader::loadResources(geometryLib, materialLib);
  input = window.getInput();
}

void Engine::start(Scene * start)
{
  running = true;
  scene.push(start);
  run();
  stop();
}

void Engine::run()
{
  double elapsedTime = 0;
  double inputResetTimer = 0;
  while (!window.done && running)
  {
    auto start = std::chrono::system_clock::now();
    if (elapsedTime > frameCap)
    {
      window.handleMessages();
      scene.top()->update();
      elapsedTime -= frameCap;
      window.updateFrameBuffer();
    }
    else
      std::this_thread::sleep_for(std::chrono::milliseconds((int)((frameCap - elapsedTime) * 1000)));
    if (inputResetTimer > 1.0 / 4.0)
    {
      window.updateInput();
      inputResetTimer -= 1.0 / 4.0;
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    elapsedTime += elapsed.count();
    inputResetTimer += elapsedTime;
  }
  if (!window.done)
    window.killWindow();
}

void Engine::stop()
{
  for (unsigned int i = 0; i < scene.size(); i++)
  {
    delete scene.top();
    scene.pop();
  }
}

void Engine::quit()
{
  running = false;
}

GeometryLib * Engine::getGeoLib()
{
  return &geometryLib;
}

MaterialLib * Engine::getMatLib()
{
  return &materialLib;
}

ShaderManager * Engine::getShaderManger()
{
  return &shaderManager;
}

Input * Engine::getInput()
{
  return input;
}

Engine::~Engine()
{

}
