#ifndef FONT__
#define FONT__

#include "System/Graphics/Resources/texture.h"
#include "System/Graphics/Resources/buffer.h"
#include <vector>
#include <map>

struct FontCharacter
{
  float xOffset;
  float yOffset;
  float x, y;
  float xAdvance;
  std::vector<unsigned int> indice;
};

struct Kerning 
{
  float amount;
};

class Font 
{
private: 
  Texture * atlas;
  Buffer fontData;
  std::map<char, FontCharacter> characters;
  std::map<std::string, Kerning> kernings;
  void parseFontFile(std::string fileName);
  Kerning parseKerning(std::string & line);
  FontCharacter parseFontCharacter(std::string & line);
public:
  Font(std::string fontFileName);
  virtual ~Font();
  FontCharacter & getCharacter(char character);
  Kerning & getKerning(char first, char second);
  void fillBuffer();
};

#endif