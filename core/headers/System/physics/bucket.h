#ifndef BUCKET__
#define BUCKET__

class Bucket {
private:
  Bucket * parent;
  std::vector<Bucket> children;
  std::vector<AABB*> staticNodes;
  std::vector<AABB*> dynamicNodes;
  AABB bb;
public:
  Bucket (AABB aabb, Bucket * top, int & recursiveCount);
  virtual ~Bucket ();
  void addStaticNode(AABB * aabb);
  void addDynamicNode(AABB * aabb);
  bool removeStaticNode(AABB * node);
  bool removeDynamicNode(AABB * node);
  const std::vector<Bucket*> queryAABB(AABB aabb);
  const std::vector<Bucket*> getChildren();
  const std::vector<AABB*> getStatic();
  const std::vector<AABB*> getDynamic();
};

#endif
