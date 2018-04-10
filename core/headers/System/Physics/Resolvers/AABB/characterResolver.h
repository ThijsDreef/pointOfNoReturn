#include "aabb.h"
#include <string>
class CharacterResolver : public AabbResolver
{
private:

public:
  CharacterResolver ();
  virtual ~CharacterResolver ();
  void resolve(Aabb & main, Aabb & other);
};
