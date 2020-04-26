#ifndef __DETECTER__HPP__
#define __DETECTER__HPP__

#include "ColorDeck.hpp"
#include <Windows.h>

struct CoordinateDouble {
  double x, y;
  CoordinateDouble(double x, double y) : x(x), y(y) {}
  CoordinateDouble() : x(0), y(0) {}
};

class Detecter {

  bool _withIn(CoordinateDouble topLeft, CoordinateDouble rightBottom, int len,
               int width) const;

public:
  RECT rect;

  Detecter(const RECT &rect);

  long scaleX(unsigned int count) const;
  long scaleY(unsigned int count) const;

  Coordinate click(short len, short width, int x, int y) const;
};

#endif //__DETECTER__HPP__