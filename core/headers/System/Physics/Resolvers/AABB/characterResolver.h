#include "aabb.h"
#include <iostream>
class CharacterResolver : public AabbResolver
{
private:

public:
  CharacterResolver ();
  virtual ~CharacterResolver ();
  void resolve(Aabb & main, Aabb & other);
};
