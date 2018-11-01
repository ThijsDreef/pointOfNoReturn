#ifndef UITEXT__
#define UITEXT__

#include "System/Engine/EngineObjects/component.h"
#include "Math/vec2.h"

class UIText : public Component
{
private:
  std::string text;
  Vec2<float> pos;
  float scale = 1.f;
  bool dirty;
public:
  void setPos(Vec2<float> position);
  Vec2<float> & getPos();
  void setClean();
  void setScale(float s);
  float getScale();
  bool isDirty();
  void setText(std::string newText);
  std::string & getText();
  UIText(std::string startText, Vec2<float> position, Object * object);
  virtual ~UIText();
};

#endif