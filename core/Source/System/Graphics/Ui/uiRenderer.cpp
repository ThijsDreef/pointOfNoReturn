#include "System/Graphics/Ui/uiRenderer.h"

UiRenderer::UiRenderer(std::string fontFileName) : fontBuffer("fontGPUData", GL_ARRAY_BUFFER), font(fontFileName)
{

}

UiRenderer::~UiRenderer()
{

}

void UiRenderer::update()
{
    bool hasChanged = false;
    for (unsigned int i = 0; i < textObjects.size(); i++)
    {
        if (textObjects[i]->isDead())
        {
        textObjects[i]->setRemoved();
        textObjects.erase(textObjects.begin() + i);
        }
        if (textObjects[i]->isDirty()) 
        {
            rebuildBuffer();
        }

    }
    if (hasChanged) fontBuffer.bufferData(sizeof(TextGPUData) * textGPUData.size(), &textGPUData[0], GL_DYNAMIC_DRAW);

    font.bindTexture(10);
    glDrawElements(GL_TRIANGLES, textIndices.size(), GL_UNSIGNED_INT, &textIndices[0]);
}

void UiRenderer::addObject(Object * object)
{
    UIText * text = object->getComponent<UIText>();
    if (text) textObjects.push_back(text);
}

void UiRenderer::rebuildBuffer()
{
    textGPUData.clear();
    textIndices.clear();
    std::vector<unsigned int> defaultIndices = {0, 1, 2, 0, 3, 1};
    for (unsigned i = 0; i < textObjects.size(); i++)   
    {
        std::string text = textObjects[i]->getText();
        Vec2<float> offset = textObjects[i]->getPos();
        float scale = textObjects[i]->getScale();
        unsigned int indiceOffset = 0;
        for (unsigned int j = 0; j < text.size(); j++)
        {
            FontCharacter character = font.getCharacter(text[j]);
            for (unsigned int k = 0; k < character.vertices.size(); k++)
            {
                textGPUData.push_back(TextGPUData((character.vertices[k].vertexPosition + offset) * Vec2<float>(scale, scale), character.vertices[k].uvCoords));
            }
            for (unsigned int l = 0; l < defaultIndices.size(); l++)
            {
                textIndices.push_back(defaultIndices[l]);
            }
            indiceOffset += 4;
        }
    }
}