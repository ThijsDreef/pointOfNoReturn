#include "System/Graphics/Ui/font.h"

Font::Font(std::string fontFileName)
{
    atlas = new Texture(fontFileName + ".png");
    parseFontFile(fontFileName + ".fnt");
}

Font::~Font() 
{
    delete atlas;
}

FontCharacter & Font::getCharacter(char character)
{
    return characters[character];
}

Kerning & Font::getKerning(char first, char second)
{
    std::string combined;
    combined.append(first, second);
    return kernings[combined];
}

void Font::parseFontFile(std::string fileName)
{
    std::fstream file(fileName);
    std::string line;
    std::cout << fileName;
    if (file.is_open()) 
    {
        while (std::getline(file, line))
        {
            if (line.substr(0, 5) == "char ") {
                parseFontCharacter(line);
            }
            else if (line.substr(0, 8) == "kerning ")
                parseKerning(line);
        }
    }
    setUpCharacters();
}

void Font::parseKerning(std::string & line)
{
    Kerning kerning;
    int first, second;
    sscanf(line.c_str(), "kerning first=%d second=%d amount=%d", &first, &second, &kerning.amount);
    std::string combined;
    combined.append((char)first, (char)second);
    kernings[combined] = kerning;
}

void Font::parseFontCharacter(std::string & line)
{
    int id;
    FontCharacter character;
    sscanf(line.c_str(), "char id=%d x=%d y=%d width=%d height=%d xoffset=%d yoffset=%d xadvance=%d",
    &id, &character.x, &character.y, &character.w, &character.h, &character.xOffset, &character.yOffset, &character.xAdvance);
    characters[(char)id] = character;
}

void Font::setUpCharacters()
{
    std::vector<FontGPUData> fontBuffer;
    std::vector<unsigned int> defaultIndices = {1, 2, 0, 1, 3, 2};
    int w = atlas->getWidth();
    int h = atlas->getHeight();
    unsigned int indiceOffset = 0;
    for (auto & i : characters)
    {
        float normalizedW = (float)i.second.w / w;
        float normalizedH = (float)i.second.h / h;
        float normalizedX = (float)i.second.x / w;
        float normalizedY = (float)i.second.y / h;

        i.second.xOffset /= w;
        i.second.yOffset /= h;
        i.second.xAdvance /= w;
        i.second.h /= h;
        i.second.w /= w;
        i.second.x /= w;
        i.second.y /= h;

        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW * -0.5, normalizedH * -0.5), Vec2<float>(normalizedX + normalizedW, normalizedY)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW * 0.5, normalizedH * -0.5), Vec2<float>(normalizedX, normalizedY + normalizedH)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW * -0.5, normalizedH * 0.5), Vec2<float>(normalizedX, normalizedY)));
        i.second.vertices.push_back(FontGPUData(Vec2<float>(normalizedW * 0.5, normalizedH * 0.5), Vec2<float>(normalizedX + normalizedW, normalizedY + normalizedH)));

    }
}

void Font::bindTexture(unsigned int bindingId)
{
    atlas->bind(bindingId);
}
