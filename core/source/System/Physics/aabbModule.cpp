#include "aabbModule.h"

AabbModule::AabbModule(unsigned int gridSize) : grid(gridSize)
{
  size = gridSize;
}

AabbModule::~AabbModule()
{

}

void AabbModule::addObject(Object * object)
{
  Aabb* aabb = object->getComponent<Aabb>();
  if (aabb)
  {
    colliders.push_back(aabb);
    aabb->added();
  }
}

void AabbModule::update()
{
  grid.clear();
  for (unsigned int i = 0; i < colliders.size(); i++)
  {
    if (colliders[i]->isDead())
    {
      colliders[i]->setRemoved();
      colliders.erase(colliders.begin() + i);
    }
    grid.addCollider(colliders[i]->getPos()[0] + colliders[i]->getPos()[2], i);
  }
  for (unsigned int i = 0; i < size; i++)
  {
    std::vector<int> colliderIndice = grid.getColliders(i);
    for (unsigned int j = 0; j < colliderIndice.size(); j ++)
    {
      for (unsigned int n = j + 1; n < colliderIndice.size(); n++)
      {
        if (colliders[colliderIndice[j]]->intersect(*colliders[colliderIndice[n]]))
        {
          colliders[colliderIndice[n]]->resolve(*colliders[colliderIndice[j]]);
          colliders[colliderIndice[j]]->resolve(*colliders[colliderIndice[n]]);
        }
      }
    }
  }
}
