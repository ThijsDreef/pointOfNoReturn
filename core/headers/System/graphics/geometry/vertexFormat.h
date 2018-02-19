#ifndef VERTEXFORMAT__
#define VERTEXFORMAT__

#include "vec2.h"
#include "vec3.h"
struct VertexFormat
{
  Vec3<float> pos;
  Vec3<float> normal;
  Vec2<float> uv;
  VertexFormat(const Vec3<float>& pos, const Vec3<float>& normal, const Vec2<float>& uv)
  {
    this->pos = pos;
    this->normal = normal;
    this->uv = uv;
  }
};
#endif
