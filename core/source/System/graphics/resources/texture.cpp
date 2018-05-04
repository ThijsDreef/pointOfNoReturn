#include "texture.h"

Texture::Texture(int width, int height, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(int width, int height, unsigned int internal, unsigned int format, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  iFormat = internal;
  this->format = format;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, GL_FLOAT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::Texture(int width, int height, unsigned int internal, unsigned int format, unsigned int filter, unsigned int dataType, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  iFormat = internal;
  this->format = format;
  this->filter = filter;
  this->dataType = dataType;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, dataType, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

Texture::Texture(int width, int height, void* data, std::string textureName)
{
  w = width;
  h = height;
  name = textureName;
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Texture::~Texture()
{

}

void Texture::bufferData(int width, int height, std::string textureName, void* data)
{
  name = textureName;
  bufferData(width, height, data);
}

void Texture::bufferData(int width, int height, unsigned int internal, unsigned int format, void* data)
{
  iFormat = internal;
  this->format = format;
  bufferData(width, height, data);
}

void Texture::bufferData(int width, int height, unsigned int internal, unsigned int format, std::string textureName, void* data)
{
  name = textureName;
  bufferData(width, height, internal, format, data);
}
void Texture::bufferData(int width, int height, void* data)
{
  w = width;
  h = height;
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, iFormat, width, height, 0, format, GL_FLOAT, data);
}

void Texture::setFilter(unsigned int filter)
{
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
}

void Texture::bind(unsigned int bindingPoint)
{
  glActiveTexture(GL_TEXTURE0 + bindingPoint);
  glBindTexture(GL_TEXTURE_2D, id);
}

unsigned int Texture::getId()
{
  return id;
}