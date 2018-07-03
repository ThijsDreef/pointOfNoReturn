#ifndef BUCKET__
#define BUCKET__

#include "AABB.h"
#include <vector>

class Bucket {
private:
  Bucket * parent;
  std::vector<Bucket> children;
  std::vector<Collider*> staticNodes;
  std::vector<Collider*> dynamicNodes;
  AABB bb;
public:
  Bucket (AABB aabb, Bucket * top, int & recursiveCount);
  virtual ~Bucket ();
  void addStaticNode(Collider * aabb);
  void addDynamicNode(Collider * aabb);
  bool removeStaticNode(Collider * node);
  bool removeDynamicNode(Collider * node);
  const std::vector<Bucket*> queryAABB(AABB aabb);
  const std::vector<Bucket*> getChildren();
  const std::vector<Collider*> getStatic();
  const std::vector<Collider*> getDynamic();
};

#endif
