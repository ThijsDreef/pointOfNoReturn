#ifndef AABBRESOLVER__
class Aabb;
class AabbResolver
{
private:
  /* data */

public:
  AabbResolver ();
  virtual ~AabbResolver ();
  virtual void resolve(Aabb & main, Aabb & other);
};
#endif
