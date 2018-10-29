#ifndef UIRENDERER__
#define UIRENDERER__

#include "System/module.h"
#include "System/Engine/EngineObjects/object.h"
#include "System/Engine/Graphics/Ui/uiText.h"

class UiRenderer : public Module
{
private:
  std::vector<UIText> textObjects;
public:
  UiRenderer();
  virtual ~UiRenderer();
  void update();
  void addObject(Object * object);

};

#endif