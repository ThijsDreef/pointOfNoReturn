#include "System/Window/glew.h"
#include <string>
#ifndef TEXTURE__
#define TEXTURE__ 

class Texture
{
private:
  int w;
  int h;
  unsigned int id;
  unsigned int iFormat;
  unsigned int format;
  unsigned int filter;
  unsigned int dataType;
  std::string name;
public:
  Texture (int width, int height, std::string textureName);
  Texture (int width, int height, void* data, std::string textureName);
  Texture (int width, int height, unsigned int internal, unsigned int format, void* data, std::string textureName);
  Texture (int width, int height, unsigned int internal, unsigned int format, unsigned int filter, unsigned int dataType, void* data, std::string textureName);
  void bufferData(int width, int height, std::string textureName, void* data);
  void bufferData(int width, int height, void* data);
  void bufferData(int width, int height, unsigned int internal, unsigned int format, void* data);
  void bufferData(int width, int height, unsigned int internal, unsigned int format, std::string textureName, void* data);
  void bind(unsigned int bindingPoint);
  void setFilter(unsigned int filter);
  virtual ~Texture ();
  unsigned int getId();
};

#endif