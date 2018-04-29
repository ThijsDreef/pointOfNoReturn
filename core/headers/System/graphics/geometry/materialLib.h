#ifndef MATERIALLIB__
#define MATERIALLIB__

#include "material.h"
#include <vector>
#include <map>
#include "buffer.h"
#include <string>
class MaterialLib
{
private:
  std::map<std::string, Material> map;
  std::map<std::string, unsigned int> loc;
public:
  Buffer matBuffer;

  MaterialLib ();
  void setUpBuffer();
  void addMaterial(const std::string& name, Material mat);
  void removeMaterial(const std::string& name);
  unsigned int getMaterialId(std::string& name);
  unsigned int getMaterialLoc(const std::string& name);
  Material& getMaterial(const std::string& name);
  virtual ~MaterialLib ();
};

#endif
