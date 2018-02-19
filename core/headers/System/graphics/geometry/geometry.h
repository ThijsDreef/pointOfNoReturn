#ifndef GEOMETRY__
#define GEOMETRY__
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "vec3.h"
#include "vec4.h"
#include "materialLib.h"
#include "vertexFormat.h"
class Geometry
{
private:
  //sort indices per material
  // std::map<std::string, std::vector<unsigned int>> map;
  std::vector<std::vector<unsigned int>> allIndices;
  //set indices with offset for large geo buffer
  // std::map<std::string, std::vector<unsigned int>> offsetIndices;
  std::vector<std::vector<unsigned int>> offsetIndices;
  std::vector<std::string> materials;
  int offset;
  bool parseObj(const std::string& fileName, MaterialLib * materialLib);
public:
  std::string name;
  std::vector<VertexFormat> storedVertices;
  Geometry ();
  Geometry (const char * fileName, const char* name, MaterialLib * materialLib);
  void setIndiceOffset(int offset);
  const std::vector<std::string>& getMaterials();
  const std::vector<unsigned int>& getIndice(int group);
  virtual ~Geometry ();
};
#endif
