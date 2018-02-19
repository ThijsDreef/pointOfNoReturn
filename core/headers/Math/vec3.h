#ifndef VEC3__
#define VEC3__
template<class T>
class Vec3
{
private:
  T components[3];
public:
  Vec3 (T x, T y, T z)
  {
    components[0] = x;
    components[1] = y;
    components[2] = z;
  }
  Vec3 ()
  {
    for (int i = 0; i < 3; i ++)
      components[i] = 0;
  };
  T& operator[] (int i)
  {
    return components[i];
  }
  Vec3<T> operator*(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] * other[i];
    return vec3;
  }
  Vec3<T> operator+(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] + other[i];
    return vec3;
  }
  Vec3<T> operator-(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] - other[i];
    return vec3;
  }
  Vec3<T> operator/(Vec3<T> other)
  {
    Vec3<T> vec3;
    for (int i = 0; i < 3; i++)
      vec3[i] = components[i] / other[i];
    return vec3;
  }
  ~Vec3 ()
  {

  };
};
#endif
