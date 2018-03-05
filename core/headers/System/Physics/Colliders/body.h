#ifndef BODY__
#define BODY__
#include "vec3.h"
#include "point.h"
#include <vector>
#include <math.h>
#include "component.h"

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
  void getWeights(float & w1, float & w2, float & w3, Vec3<float> pos);
};
#endif
