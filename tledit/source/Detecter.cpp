#include "Detecter.hpp"
#include <cmath>
#include <limits.h>

Detecter::Detecter(const RECT &rectA) : rect(rectA) {}

bool Detecter::_withIn(CoordinateDouble topLeft, CoordinateDouble rightBottom,
                       int len, int width) const {
  if ((len > topLeft.x && len < rightBottom.x) &&
      (width > topLeft.y && width < rightBottom.y))
    return true;

  return false;
}

long Detecter::scaleX(unsigned int len) const {

  return static_cast<long>(::ceil(static_cast<double>(rect.right) / len));
}
long Detecter::scaleY(unsigned int width) const {
  return static_cast<long>(::ceil(static_cast<double>(rect.bottom) / width));
}

Coordinate Detecter::click(short len, short width, int x, int y) const {
  double sizeX = static_cast<double>(rect.right) / len;
  double sizeY = static_cast<double>(rect.bottom) / width;

  CoordinateDouble topLeft, rightBottom(sizeX, sizeY);

  for (unsigned short i = 0; i < width; i++) {
    for (unsigned short j = 0; j < len; j++) {

      if (_withIn(topLeft, rightBottom, x, y))
        return Coordinate(i, j);

      topLeft.x += sizeX;
      rightBottom.x += sizeX;
    }
    topLeft.x = 0;
    rightBottom.x = sizeX;
    topLeft.y += sizeY;
    rightBottom.y += sizeY;
  }

  return Coordinate(SHRT_MAX * -1, SHRT_MAX * -1);
}