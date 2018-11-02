#include "System/Graphics/Ui/uiRenderer.h"

UiRenderer::UiRenderer(std::string fontFileName, ShaderManager * shader) : fontBuffer("fontGPUData", GL_ARRAY_BUFFER), font(fontFileName)
{
    shaderManager = shader;
    shader->createShaderProgram("shaders/font.vert", "shaders/font.frag", "font");
    setupFormat();

}

UiRenderer::~UiRenderer()
{

}

void UiRenderer::setupFormat()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribFormat(0, 2, GL_FLOAT, false,  0); // position
    glVertexAttribBinding(0, 0); // position -> stream 0
    glEnableVertexAttribArray(1);
    glVertexAttribFormat(1, 2, GL_FLOAT, false, 8); // uv
    glVertexAttribBinding(1, 0); 
}

void UiRenderer::update()
{
    glEnable (GL_BLEND); 
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    bool hasChanged = false;
    for (unsigned int i = 0; i < textObjects.size(); i++)
    {
        if (textObjects[i]->isDead())
        {
            textObjects[i]->setRemoved();
            textObjects.erase(textObjects.begin() + i);
        }
        if (textObjects[i]->isDirty() && !hasChanged) 
        {
            rebuildBuffer();
            hasChanged = true;
            textObjects[i]->setClean();
        } 
        else if (textObjects[i]->isDirty()) 
        {
            textObjects[i]->setClean();
        }

    }
    if (hasChanged) fontBuffer.bufferData(sizeof(TextGPUData) * textGPUData.size(), &textGPUData[0], GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glUseProgram(shaderManager->getShader("font"));
    font.bindTexture(10);
    glBindVertexBuffer(0, fontBuffer.getBufferId(), 0, 16);
    
    glDrawElements(GL_TRIANGLES, textIndices.size(), GL_UNSIGNED_INT, &textIndices[0]);
    glDisable(GL_BLEND);
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
        
        unsigned int indiceOffset = 0;
        for (unsigned int j = 0; j < text.size(); j++)
        {
            FontCharacter character = font.getCharacter(text[j]);
            for (unsigned int k = 0; k < character.vertices.size(); k++)
            {
                Vec2<float> vt = character.vertices[k].vertexPosition;
                vt = vt + offset;
                // vt[1] += character.yOffset;
                vt[0] += character.xOffset;
                textGPUData.push_back(TextGPUData(vt, character.vertices[k].uvCoords));
            }
            for (unsigned int l = 0; l < defaultIndices.size(); l++)
            {
                textIndices.push_back(defaultIndices[l] + indiceOffset);
            }
            offset[0] += character.xAdvance;
            indiceOffset += 4;
        }
    }
}