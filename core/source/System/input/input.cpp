#include "System/Input/input.h"

Input::Input()
{
  for (unsigned int i = 0; i < 256; i++)
    keys[i] = false;
  for (unsigned int i = 0; i < 2; i++)
    mouse[i] = false;
}

Input::~Input()
{

}

int Input::getMouseWheelDelta()
{
  return delta;
}
bool Input::proccesWindowMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, HWND hWnd)
{
  switch (uMsg)
  {
    case WM_KEYDOWN:
    {
      keys[wParam] = true;
      return true;
    }
    case WM_KEYUP:
    {
      keys[wParam] = false;
      return true;
    }
    case WM_MOUSEWHEEL:
    {
      delta += GET_WHEEL_DELTA_WPARAM(wParam);
    }
    case WM_MOUSEMOVE:
    {
      POINT pt;
      pt.x = GET_X_LPARAM(lParam);
      pt.y = GET_Y_LPARAM(lParam);
      ScreenToClient(hWnd, &pt);
      dx += (lockX - x) * 0.1;
      dy += (lockY - y) * 0.1;
      dx = (dx > 10) ? 10 : (dx < -10) ? -10 : dx;
      dy = (dy > 10) ? 10 : (dy < -10) ? -10 : dy;
      x = pt.x;
      y = pt.y;
      return true;
    }
    case WM_LBUTTONDOWN:
    {
      mouse[0] = true;
      return true;
    }
    case WM_LBUTTONUP:
    {
      mouse[0] = false;
      return true;
    }
    case WM_MBUTTONDOWN:
    {
      mouse[1] = true;
      return true;
    }
    case WM_MBUTTONUP:
    {
      mouse[1] = false;
      return true;
    }
    case WM_RBUTTONDOWN:
    {
      mouse[2] = true;
      return true;
    }
    case WM_RBUTTONUP:
    {
      mouse[2] = false;
      return true;
    }
    default:
    {
      return false;
    }
  }
  return false;
}

void Input::resetDelta()
{
  dx *= 0.6;
  dy *= 0.6;
  delta = 0;
}

float Input::getDx()
{
  return dx;
}

float Input::getDy()
{
  return dy;
}

bool Input::getMouseLock()
{
  return lockMouse;
}

void Input::setLockCoords(int lx, int ly)
{
  lockX = lx;
  lockY = ly;
}

int Input::getLockX()
{
  return lockX;
}

int Input::getLockY()
{
  return lockY;
}

void Input::setMouseLock(bool lock)
{
  lockMouse = lock;
}

bool Input::getKeyDown(int keyCode)
{
  return keys[keyCode];
}

bool Input::getMouseButtonDown(int buttonCode)
{
  return mouse[buttonCode];
}

int Input::getMouseX()
{
  return x;
}

int Input::getMouseY()
{
  return y;
}
