#include "implicidGrid.h"

ImplicidGrid::ImplicidGrid(unsigned int size)
{
  gridSize = size;
  for (unsigned int i = 0; i < size; i ++)
    colliders.push_back(std::vector<int>());
}

ImplicidGrid::~ImplicidGrid()
{

}

int ImplicidGrid::hash(int sumPos)
{
  unsigned int h = std::abs(sumPos);
  h /= gridSize;
  return h & gridSize;
}

void ImplicidGrid::addCollider(int sumpos, int index)
{
  colliders[hash(sumpos)].push_back(index);
}

std::vector<int> ImplicidGrid::getColliders(int cell)
{
  return colliders[cell];
}

void ImplicidGrid::clear()
{
  for (unsigned int i = 0; i < colliders.size(); i ++)
  {
    unsigned int size = colliders[i].size();
    colliders[i].clear();
    colliders[i].reserve(size);
  }
}
