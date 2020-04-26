#include "Printer.hpp"
#include "ColorDeck.hpp"

Printer::Printer(const ColorDeck &deck, const RECT &rect)
    : _deck(deck), _d(rect) {}

CoordinateDouble Printer::print(HDC context, bool pen) const {

  FillRect(context, &_d.rect, static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)));

  unsigned short len = _deck.getLen();
  unsigned short width = _deck.getWidth();
  bool fail = false;

  long sizeX = _d.scaleX(len);
  long sizeY = _d.scaleY(width);

  Coordinate index;
  CoordinateDouble topLeft, rightBottom(sizeX, sizeY);
  HBRUSH hBrush;
  HPEN hPen;

  if (!pen)
    hPen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
  else
    hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

  DeleteObject(SelectObject(context, hPen));

  for (unsigned short i = 0; i < width; i++) {
    for (unsigned short j = 0; j < len; j++) {
      index.x = i;
      index.y = j;

      Color color = _deck.getItem(index, fail);
      if (!fail) {
        hBrush = CreateSolidBrush(
            RGB(color.getBluePart(), color.getGreenPart(), color.getRedPart()));
        DeleteObject(SelectObject(context, hBrush));
      } else {
        DeleteObject(SelectObject(context, GetStockObject(NULL_BRUSH)));
      }

      Rectangle(context, static_cast<int>(topLeft.x),
                static_cast<int>(topLeft.y), static_cast<int>(rightBottom.x),
                static_cast<int>(rightBottom.y));

      topLeft.x += sizeX;
      rightBottom.x += sizeX;

      fail = false;
    }

    topLeft.x = 0;
    rightBottom.x = sizeX;
    topLeft.y += sizeY;
    rightBottom.y += sizeY;
  }

  DeleteObject(hPen);

  return CoordinateDouble(sizeX * len, sizeY * width);
}