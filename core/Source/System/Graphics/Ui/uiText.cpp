#include "System/Graphics/Ui/uiText.h"

UIText::UIText(std::string startText, Vec2<float> position, Object * object) : Component(object)
{
    text = startText;
    pos = position;
    dirty = true;
    scale = 1.0f;
}

UIText::~UIText()
{

}

void UIText::setClean()
{
    dirty = false;
}

void UIText::setText(std::string newText)
{
    text = newText;
    dirty = true;
}

void UIText::setPos(Vec2<float> position)
{
    pos = position;
    dirty = true;
}

void UIText::setScale(float s)
{
    scale = s;
}

float UIText::getScale()
{
    return scale;
}

bool UIText::isDirty()
{
    return dirty;
}

std::string & UIText::getText()
{
    return text;
}

Vec2<float> & UIText::getPos()
{
    return pos;
}