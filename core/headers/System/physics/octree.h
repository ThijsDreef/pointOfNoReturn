#ifndef OCTREE__
#define OCTREE__

struct Collision {
  Collider* hit;
  Collider* other;
  Collision(Collider * h, Collider* o)
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
  std::vector<Collision> queryTreeCollider(Collider * col);
  std::vector<Collision> querTreeLine(Vec3<float> start, Vec3<float> end, Vec3<float> tolerance);
};

#endif
