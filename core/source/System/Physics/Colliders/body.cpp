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
  float w1, w2, w3;
  getWeights(w1, w2, w3, pos);
  return w1 * positions[0][1] +  w2 * positions[1][1] + w3 * positions[2][1];
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
  float w1, w2, w3;
  getWeights(w1, w2, w3, other.getPos());
  if (w1 > 0 && w2 > 0 && w3 > 0)
    return true;
  return false;
}

void Body::getWeights(float & w1, float & w2, float & w3, Vec3<float> pos)
{
  w1 = (positions[1][2] - positions[2][2]) * (pos[0] - positions[2][0]) + (positions[2][0] - positions[1][0]) * (pos[2] - positions[2][2])
  / (positions[1][2] - positions[2][2]) * (positions[0][0] - positions[2][0]) + (positions[2][0] - positions[1][0]) * (positions[0][2] = positions[2][2]);
  w2 = (positions[2][2] - positions[0][2]) * (pos[0] - positions[2][0]) + (positions[0][0] - positions[2][0]) * (pos[2] - positions[2][2])
  / (positions[1][2] - positions[2][2]) * (positions[0][0] - positions[2][0]) + (positions[2][0] - positions[1][0]) * (positions[0][2] - positions[2][2]);
  w3 = 1 - w1 - w2;
}
