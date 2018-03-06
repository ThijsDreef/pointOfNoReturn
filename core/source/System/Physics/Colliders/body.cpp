#include "body.h"

Body::Body(std::vector<Vec3<float>> pos, Object * object) : Component(object)
{
  positions = pos;
  for (unsigned int i = 0; i < pos.size(); i++)
    averagePos += pos[i];
  averagePos /= (float)pos.size();
}

Body::~Body()
{

}

Vec3<float> Body::getAveragePos()
{
  return averagePos;
}

float Body::getHeight(Vec3<float> & pos)
{
  if (positions.size() > 3 || positions.size() < 3)
    return 0;
  Vec3<float> weights = getWeights(pos);
  return weights[0] * positions[0][1] + weights[1] * positions[1][1] + weights[2] * positions[2][1];
}

bool Body::getCollision(Point & other)
{
  for (unsigned int i = 0; i < positions.size(); i++)
  {
    float dx = std::abs(positions[i][0] - other.getPos()[0]);
    if (dx < other.getRadius()[0])
      return true;
    float dy = std::abs(positions[i][1] - other.getPos()[1]);
    if (dy < other.getRadius()[1])
      return true;
    float dz = std::abs(positions[i][2] - other.getPos()[2]);
    if (dz < other.getRadius()[2])
      return true;
  }
  Vec3<float> weights = getWeights(other.getPos());
  if (weights[0] > 0 && weights[1] > 0 && weights[2] > 0)
    return true;
  return false;
}

Vec3<float> Body::getWeights(Vec3<float> pos)
{
  Vec3<float> v0 = positions[1] - positions[0];
  Vec3<float> v1 = positions[2] - positions[0];
  Vec3<float> v2 = pos - positions[0];
  float d00 = v0.dot(v0);
  float d01 = v0.dot(v1);
  float d11 = v1.dot(v1);
  float d20 = v2.dot(v0);
  float d21 = v2.dot(v1);
  float denom = d00 * d11 - d01 * d01;
  float w1 = (d11 * d20 - d01 * d21) / denom;
  float w2 = (d00 * d21 - d01 * d20) / denom;
  float w3 = 1.0f - w1 - w2;
  return Vec3<float>(w1, w2, w3);
}
