#ifndef OBJECT__
#define OBJECT__
#include <vector>
#include <string>
#include <map>
#include "component.h"

class Object
{
private:
  std::vector<Component*> components;
  std::map<std::string, std::vector<Component*>> event;
public:
  Object (std::vector<Component*> comp);
  void updateComponents();
  bool empty();
  void addComponent(Component * comp);
  void sendMessage(const std::string & message, void* data);
  void subscribe(const std::string & message, Component * c);
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
