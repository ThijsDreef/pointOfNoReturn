#ifndef BODY__
#define BODY__
#include "vec3.h"
#include "point.h"
#include <vector>
#include <math.h>
#include "component.h"
#include <iostream>

class Body : public Component
{
private:
  std::vector<Vec3<float>> positions;
  Vec3<float> averagePos;
public:
  Body (std::vector<Vec3<float>> pos, Object * object);
  virtual ~Body ();
  Vec3<float> getAveragePos();
  float getHeight(Vec3<float> & pos);
  bool getCollision(Point & other);
  Vec3<float> getWeights(Vec3<float> pos);
};
#endif
