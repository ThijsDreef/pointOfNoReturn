#ifndef SHADERMANAGER__
#define SHADERMANAGER__
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <glew.h>


class ShaderManager
{
private:
  std::map<std::string, unsigned int> shaderlist;
  std::string readShader(const char* fileName);
  unsigned int createShader(GLenum shadertype, std::string source, const char* shaderName);
public:
  unsigned int getShader(std::string shader);
  void deleteShader(std::string shader);
  unsigned int createShaderProgram(const char* vertex, const char* fragment, std::string shader);
  ShaderManager ();
  virtual ~ShaderManager ();

};
#endif
