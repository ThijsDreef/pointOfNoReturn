#ifndef UIRENDERER__
#define UIRENDERER__

#include "System/module.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Graphics/Ui/uiText.h"
#include "System/Graphics/Resources/buffer.h"
#include "System/Graphics/Ui/font.h"


struct TextGPUData
{
  Vec2<float> vertex;
  Vec2<float> uv;
  TextGPUData(Vec2<float> vert, Vec2<float> texCoord)
  {
    vertex = vert;
    uv = texCoord;
  }
};


class UiRenderer : public Module
{
private:
  Buffer fontBuffer;
  Font font;
  std::vector<TextGPUData> textGPUData;
  std::vector<unsigned int> textIndices;
  std::vector<UIText*> textObjects;
public:
  void rebuildBuffer();
  UiRenderer(std::string fontFileName);
  virtual ~UiRenderer();
  void update();
  void addObject(Object * object);

};

#endif