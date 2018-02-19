#ifndef MATERIAL__
#define MATERIAL__
#include "vec4.h"
struct Material
{
  Vec4<float> color;
  char chars[240];
  Material(const Vec4<float>& color)
  {
    this->color = color;
  }
  Material()
  {
    color = Vec4<float>(1, 1, 1, 1);
  }
};

#endif
