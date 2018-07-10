#include "engine.h"

Engine::Engine(std::string title, int iWidth, int iHeight, int bitDepth, bool fullScreen, double frameCap)
:
window(title.c_str(), iWidth, iHeight, bitDepth, fullScreen)
{
  width = iWidth;
  height = iHeight;
  this->frameCap = frameCap;
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  UtilLoader::loadResources(geometryLib, materialLib);
  input = window.getInput();
  window.vsync(true);
}

Engine::Engine(double frameCap, int iWidth, int iHeight)
:
window("default", iWidth, iHeight, 32, true)
{
  width = iWidth;
  height = iHeight;
  unsigned int vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  this->frameCap = frameCap;
  UtilLoader::loadResources(geometryLib, materialLib);
  input = window.getInput();
  window.vsync(true);
  
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

int Engine::getWidth()
{
  return width;
}

int Engine::getHeight()
{
  return height;
}
