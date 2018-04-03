#ifndef IMPLICIDGRID__
#include <vector>
#include <math.h>
class ImplicidGrid
{
private:
  std::vector<std::vector<int>> colliders;
  int hash(int sumPos);
  unsigned int gridSize;
public:
  ImplicidGrid(unsigned int size);
  ~ImplicidGrid();
  void addCollider(int sumpos, int index);
  std::vector<int> getColliders(int cell);
  void clear();
};
#endif
