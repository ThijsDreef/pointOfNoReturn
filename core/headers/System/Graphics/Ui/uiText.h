#ifndef UITEXT__
#define UITEXT__

#include "System/Engine/EngineObjects/component.h"
#include "Math/vec2.h"

class UIText : public Component
{
private:
  std::string text;
  Vec2<float> pos;
  bool isDirty;
public:
  void setPos(Vec2<float> position);
  void setClean();
  void setText(std::string newText);
  UIText(std::string startText, Vec2<float> position, Object * object);
  virtual ~UIText();
};

#endif