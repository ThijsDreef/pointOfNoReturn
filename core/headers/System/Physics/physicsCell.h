#ifndef PHYSICSCELL__
#define PHYSICSCELL__
#include "point.h"
#include "body.h"
#include <vector>

class PhysicsCell
{
private:
  std::vector<Body*> bodies;
  std::vector<Point*> points;
public:
  PhysicsCell ();
  void trickle(Point * point);
  void trickle(Body * body);
  std::vector<Body*> & getBodies();
  std::vector<Point*> & getPoints();
  virtual ~PhysicsCell ();
};
#endif
