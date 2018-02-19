#ifndef OBJECT__
#define OBJECT__
#include <vector>
#include "component.h"

class Object
{
private:
  std::vector<Component*> components;
public:
  Object (std::vector<Component*> comp);
  void updateComponents();
  bool empty();
  void addComponent(Component * comp);
  virtual ~Object ();
  template<class T>
  void removeComponent(int toSkip)
  {
    int found = 0;
    for (unsigned int i = 0; i < components.size(); i ++)
    {
      if (dynamic_cast<T*>(components[i]))
      {
        found++;
        if(found > toSkip)
        {
          delete components[i];
          components.erase(components.begin() + i);
        }
      }
    }
  }
  template<class T>
  void removeComponent()
  {
    removeComponent<T>(0);
  }
  template<class T>
  T * getComponent()
  {
    for (unsigned int i = 0; i < components.size(); i++)
    {
      T * temp = dynamic_cast<T*>(components[i]);
      if (temp != 0)
        return temp;
    }
    return 0;
  }
};
#endif
