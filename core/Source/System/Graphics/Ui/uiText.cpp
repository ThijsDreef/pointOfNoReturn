#include "System/Graphics/Ui/uiText.h"

UIText::UIText(std::string startText, Vec2<float> position, Object * object) : Component(object)
{
    text = startText;
    pos = position;
    isDirty = true;
}

UIText::~UIText()
{

}

void UIText::setClean()
{
    isDirty = false;
}

void UIText::setText(std::string newText)
{
    text = newText;
    isDirty = true;
}

void UIText::setPos(Vec2<float> position)
{
    pos = position;
    isDirty = true;
}
