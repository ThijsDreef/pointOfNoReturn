#ifndef INPUT__
#define INPUT__
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include <Windowsx.h>


class Input
{
private:
  int delta = 0;
  bool keys[256];
  bool mouse[3];
  float dx, dy;
  int x, y;
  int lockX;
  int lockY;
  bool lockMouse = false;
public:
  Input ();
  int getMouseWheelDelta();
  bool getMouseLock();
  void setLockCoords(int lx, int ly);
  void setMouseLock(bool lock);
  bool proccesWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, HWND hWnd);
  bool getKeyDown(int keyCode);
  bool getMouseButtonDown(int buttonCode);
  float getDx();
  float getDy();
  void resetDelta();
  int getLockX();
  int getLockY();
  int getMouseX();
  int getMouseY();
  virtual ~Input ();
};
#endif
