#ifndef __PRINTER__HPP__
#define __PRINTER__HPP__

#include "Detecter.hpp"
#include <map>


class ColorDeck;

class Printer {
  const ColorDeck &_deck;
  Detecter _d;

public:
  Printer(const ColorDeck &deck, const RECT &rect);

  CoordinateDouble print(HDC context, bool) const;
};

#endif //__PRINTER__HPP__