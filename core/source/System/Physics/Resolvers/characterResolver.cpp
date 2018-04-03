#include "CharacterResolver.h"

CharacterResolver::CharacterResolver()
{

}

CharacterResolver::~CharacterResolver()
{

}

void CharacterResolver::resolve(Aabb & main, Aabb & other)
{
  int axis = main.getCollisionAxis(other.getPos());
  switch (axis)
  {
    case LEFT:
      main.getPos()[0] = other.getPos()[0] - (main.radius[0] + other.radius[0]);
      break;
    case RIGHT:
      main.getPos()[0] = other.getPos()[0] + main.radius[0] + other.radius[0];
      break;
    case UP:
      main.getPos()[1] = other.getPos()[1] + main.radius[1] + other.radius[1];
      break;
    case DOWN:
      main.getPos()[1] = other.getPos()[1] - (main.radius[1] + other.radius[1]);
      break;
    case FRONT:
      main.getPos()[2] = other.getPos()[2] - (main.radius[2] + other.radius[2]);
      break;
    case BACK:
      main.getPos()[2] = other.getPos()[2] + main.radius[2] + other.radius[2];
      break;
  }
}
