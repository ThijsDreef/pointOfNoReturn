#include "System/Graphics/Ui/font.h"

Font::Font(std::string fontFileName) : fontData("FontData", GL_ARRAY_BUFFER)
{
    atlas = new Texture("fonts/" + fontFileName + ".png");
    parseFontFile("fonts/" + fontFileName + ".fnt");
}

Font::~Font() 
{

}

FontCharacter & Font::getCharacter(char character)
{
    return characters[character];
}

Kerning & Font::getKerning(char first, char second)
{
    std::string combined;
    combined += first + second;
    return kernings[combined];
}

void Font::parseFontFile(std::string fileName)
{

}

Kerning Font::parseKerning(std::string & line)
{
    return Kerning();
}

FontCharacter Font::parseFontCharacter(std::string & line)
{
    return FontCharacter();
}