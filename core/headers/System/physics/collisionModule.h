#ifndef COLLISIONMODULE__
#define COLLISIONMODULE__


#include "System/module.h"
#include "System/Physics/octree.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Physics/collisionComponent.h"

class CollisionModule : public Module
{
private:
  Octree octree;
  std::vector<CollisionComponent*> staticColliders;
  std::vector<CollisionComponent*> dynamicColliders;
  std::map<std::string, Resolver*> resolvers;
public:
  CollisionModule(int width, int octreeDepth);
  virtual ~CollisionModule();
  void update();
  void addResolver(Resolver * resolve, std::string name);
  void addObject(Object * object);
};

#endif
