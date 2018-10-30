#ifndef FONT__
#define FONT__

#include "System/Graphics/Resources/texture.h"
#include "System/Graphics/Resources/buffer.h"
#include <vector>
#include <map>
#include "Math/vec2.h"

struct FontGPUData
{
  Vec2<float> vertexPosition;
  Vec2<float> uvCoords;
  FontGPUData(Vec2<float> vtPos, Vec2<float> uv) 
  {
    vertexPosition = vtPos;
    uvCoords = uv;
  }
};

struct FontCharacter
{
  int xOffset;
  int yOffset;
  int x, y, w, h;
  int xAdvance;
  std::vector<unsigned int> indice;
};

struct Kerning 
{
  int amount;
};

class Font 
{
private: 
  Texture * atlas;
  Buffer fontData;
  std::map<char, FontCharacter> characters;
  std::map<std::string, Kerning> kernings;
  void parseFontFile(std::string fileName);
  void parseKerning(std::string & line);
  void parseFontCharacter(std::string & line);
public:
  Font(std::string fontFileName);
  virtual ~Font();
  FontCharacter & getCharacter(char character);
  Kerning & getKerning(char first, char second);
  void fillBuffer();
  Buffer & getBuffer();
};

#endif