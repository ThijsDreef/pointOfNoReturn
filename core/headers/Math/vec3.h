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
  void operator +=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] += other[i];
  }
  void operator -=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] -= other[i];
  }
  void operator /=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] /= other[i];
  }
  void operator *=(Vec3<T> other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] *= other[i];
  }
  Vec3<T> operator-()
  {
    Vec3<T> other;
    for (unsigned int i = 0; i < 3; i++)
      other[i] = -components[i];
    return other;
  }
  Vec3<T> operator* (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] * other;
    return vec3;
  }
  Vec3<T> operator- (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] - other;
    return vec3;
  }
  Vec3<T> operator/ (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] / other;
    return vec3;
  }
  Vec3<T> operator+ (T other)
  {
    Vec3<T> vec3;
    for (unsigned int i = 0; i < 3; i++)
      vec3[i] = components[i] + other;
    return vec3;
  }
  void operator*= (T other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] *= other;
  }
  void operator/= (T other)
  {
    for (unsigned int i = 0; i < 3; i++)
      components[i] /= other;
  }
  void lerp(Vec3<T> target, float speed)
  {
    (*this) += speed * (target - (*this));
  }
  friend Vec3<T> operator/ (T other, Vec3<T> otherVec)
  {
    return otherVec / other;
  }
  friend Vec3<T> operator- (T other, Vec3<T> otherVec)
  {
    return otherVec - other;
  }
  friend Vec3<T> operator+ (T other, Vec3<T> otherVec)
  {
    return otherVec + other;
  }
  friend Vec3<T> operator* (T other, Vec3<T> otherVec)
  {
    return otherVec * other;
  }

  ~Vec3 ()
  {

  };
};
#endif
