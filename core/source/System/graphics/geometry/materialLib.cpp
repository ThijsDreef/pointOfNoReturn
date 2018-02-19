#include "materialLib.h"

MaterialLib::MaterialLib() : matBuffer("matBuffer", GL_UNIFORM_BUFFER)
{
  map["Material"] = Material();
}

void MaterialLib::addMaterial(const std::string& name, Material mat)
{
  map[name] = mat;
}

void MaterialLib::removeMaterial(const std::string& name)
{
  map.erase(name);
}

Material& MaterialLib::getMaterial(const std::string& name)
{
  return map[name];
}

unsigned int MaterialLib::getMaterialLoc(const std::string& name)
{
  return loc[name];
}

void MaterialLib::setUpBuffer()
{
  unsigned int size = 0;
  unsigned int indiceOffset = 0;
  //get the total buffer size
  std::vector<Material> allMats;
  //and prepare a buffer
  for (auto & i : map)
  {
    loc[i.first] = indiceOffset;
    allMats.push_back(i.second);
    size += sizeof(Material);
    indiceOffset += sizeof(Material);
  }
  //create a buffer with that size;
  matBuffer.bufferData(size, &allMats[0], GL_STATIC_DRAW);
  //print buffer size for fun !
  std::cout << "buffer size: in Bytes: " << size << "\n";
  std::cout << "buffer size: in KyloBytes: " << size / 1000.0<< "\n";
  std::cout << "buffer size: in MegaBytes: " << size / 1000000.0 << "\n";
  glBindBufferBase(GL_UNIFORM_BUFFER, 0,matBuffer.getBufferId());
  glBindBufferRange (GL_UNIFORM_BUFFER, 0, matBuffer.getBufferId(), 16, 16);


}

MaterialLib::~MaterialLib()
{

}
