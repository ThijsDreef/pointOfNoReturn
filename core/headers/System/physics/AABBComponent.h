#ifndef AABBCOMPONENT__
#define AABBCOMPONENT__
#include "transform.h"
#include "AABB.h"


class AABBComponent : public Component {
private:
  AABB bb;
  Transform * transform;
public:
  AABBComponent (AABB aabb, Transform * t, Object * object);
  virtual ~AABBComponent ();
  void update();
};
#endif
