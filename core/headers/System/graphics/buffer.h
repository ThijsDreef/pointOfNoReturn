#ifndef BUFFER__
#define BUFFER__
#include "glew.h"
#include <iostream>
#include <string>
class Buffer
{
private:
  unsigned int bufferId;
  unsigned int bufferSize;
  std::string bufferName;
  unsigned int target;
public:
  Buffer (const char * name, unsigned int target);
  void bufferData(unsigned int size, const GLvoid* data, unsigned int usage);
  void bufferSubData(unsigned int offset, unsigned int dataSize, const GLvoid * data);
  void bindBuffer();
  void invalidateBuffer();
  const unsigned int getBufferId();
  std::string getName();
  virtual ~Buffer ();
};
#endif
