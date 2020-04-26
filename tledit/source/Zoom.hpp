#ifndef __ZOOM__HPP__
#define __ZOOM__HPP__

#include "ColorDeck.hpp"

class Zoom {
public:
  enum ZOOM_STAGE { LEFT_TOP, RIGHT_TOP, LEFT_BOTTOM, RIGHT_BOTTOM };

private:
  struct list {
    list *prev;
    ColorDeck info;
    ZOOM_STAGE hook;

  } * _current;

  ColorDeck _zoom(ColorDeck, ZOOM_STAGE);
  ColorDeck _unzoom(ColorDeck dest, ColorDeck add, ZOOM_STAGE);

public:
  Zoom();

  Zoom(const Zoom &) = delete;
  Zoom &operator=(const Zoom &) = delete;

  ~Zoom();

  const ColorDeck &getCurrent() const;
  ColorDeck &getCurrent();

  void zoomUp(ZOOM_STAGE);
  bool zoomDown();

  void update();
};

inline const ColorDeck &Zoom::getCurrent() const { return _current->info; }

inline ColorDeck &Zoom::getCurrent() { return _current->info; }

#endif //__ZOOM__HPP__