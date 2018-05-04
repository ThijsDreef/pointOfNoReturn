#include "texture.h"
#include <vector>
#include "glew.h"

class Fbo
{
private:
  int w;
  int h;
  unsigned int renderBufferId;
  unsigned int id;
  std::vector<Texture> textures;
  std::vector<unsigned int> attachments;
public:
  Fbo (int width, int height);
  void attach(unsigned int internal, unsigned int format, unsigned int dataType);
  void attachDepth();
  void bind();
  void prepareDraw();
  unsigned int getDepth();
  unsigned int getTextureIndex(unsigned int attachment);
  virtual ~Fbo ();
};
