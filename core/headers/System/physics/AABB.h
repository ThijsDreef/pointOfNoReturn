#ifndef AABB__
#define AABB__

class AABB {
private:
  Vec3<float> p;
  Vec3<float> r;
public:
  AABB (Vec3<float> pos, Vec3<float> radius);
  Vec3<float> intersectA(AABB & other);
  bool intersectB(AABB & other);
  virtual ~AABB ();
};

#endif
