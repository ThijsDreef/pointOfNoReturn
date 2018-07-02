#ifndef OCTREE__
#define OCTREE__

struct Collision {
  AABB* hit;
  AABB* other;
  Vec3<float> resolve;
  Collision(AABB * h, AABB* o)
  {
    hit = h;
    other = o;
  }
};

class Octree {
private:
  Bucket * root;
  AABB tree;
public:
  Octree (AABB size, int layers);
  virtual ~Octree ();
  std::vector<Collision> getDynamicCollisions();
  std::vector<Collision> getStaticCollisions();
  std::vector<Collision> queryTreeAABB(AABB * aabb);
  std::vector<Collision> querTreeLine(Vec3<float> start, Vec3<float> end, Vec3<float> tolerance);

};

#endif
