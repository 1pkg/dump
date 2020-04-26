#include "Zoom.hpp"

Zoom::Zoom() {
  _current = new list;
  _current->prev = nullptr;
}

ColorDeck Zoom::_unzoom(ColorDeck dest, ColorDeck add, ZOOM_STAGE stage) {
  Color color;
  bool flag = false;
  int i, j;
  i = j = 0;
  ColorDeck ret = dest;

  if (stage == LEFT_TOP) {

    for (int k = 0, i = 0; i < ret.getWidth() / 2; i++, k++)
      for (int n = 0, j = 0; j < ret.getLen() / 2; j++, n++) {
        color = add.getItem(Coordinate(k, n), flag);

        if (!flag) {

          try {
            ret.setItem(Coordinate(i, j), color);
          } catch (std::exception) {
            ret.getItem(Coordinate(i, j)) = color;
          }
        }

        flag = false;
      }

    return ret;
  }

  else if (stage == RIGHT_TOP) {

    for (int k = 0, i = 0; i < ret.getWidth() / 2; i++, k++) {
      for (int n = 0, j = ret.getLen() / 2; j < ret.getLen(); j++, n++) {
        color = add.getItem(Coordinate(k, n), flag);

        if (!flag) {

          try {
            ret.setItem(Coordinate(i, j), color);
          } catch (std::exception) {
            ret.getItem(Coordinate(i, j)) = color;
          }
        }

        flag = false;
      }
      j = ret.getLen() / 2;
    }

    return ret;
  }

  else if (stage == LEFT_BOTTOM) {

    for (int k = 0, i = ret.getWidth() / 2; i < ret.getWidth(); i++, k++) {
      for (int n = 0, j = 0; j < ret.getLen(); j++, n++) {
        color = add.getItem(Coordinate(k, n), flag);

        if (!flag) {

          try {
            ret.setItem(Coordinate(i, j), color);
          } catch (std::exception) {
            ret.getItem(Coordinate(i, j)) = color;
          }
        }

        flag = false;
      }
    }

    return ret;
  }

  else {

    for (int k = 0, i = ret.getWidth() / 2; i < ret.getWidth(); i++, k++) {
      for (int n = 0, j = ret.getLen() / 2; j < ret.getLen(); j++, n++) {
        color = add.getItem(Coordinate(k, n), flag);

        if (!flag) {

          try {
            ret.setItem(Coordinate(i, j), color);
          } catch (std::exception) {
            ret.getItem(Coordinate(i, j)) = color;
          }
        }

        flag = false;
      }
      j = ret.getLen() / 2;
    }

    return ret;
  }
}

ColorDeck Zoom::_zoom(ColorDeck deck, ZOOM_STAGE stage) {
  Color color;
  bool flag = false;
  int i, j;

  if (stage == LEFT_TOP) {
    ColorDeck ret(deck.getLen() / 2, deck.getWidth() / 2);

    for (i = 0; i < deck.getWidth() / 2; i++)
      for (j = 0; j < deck.getLen() / 2; j++) {
        color = deck.getItem(Coordinate(i, j), flag);

        if (!flag)
          ret.setItem(Coordinate(i, j), color);

        flag = false;
      }

    return ret;
  }

  else if (stage == RIGHT_TOP) {
    ColorDeck ret(deck.getLen() - deck.getLen() / 2, deck.getWidth() / 2);

    for (int k = 0, i = 0; i < deck.getWidth() / 2; i++, k++) {
      for (int n = 0, j = deck.getLen() / 2; j < deck.getLen(); j++, n++) {
        color = deck.getItem(Coordinate(i, j), flag);

        if (!flag)
          ret.setItem(Coordinate(k, n), color);

        flag = false;
      }
      j = deck.getLen() / 2;
    }

    return ret;
  }

  else if (stage == LEFT_BOTTOM) {
    ColorDeck ret(deck.getLen() / 2, deck.getWidth() - deck.getWidth() / 2);

    for (int k = 0, i = deck.getWidth() / 2; i < deck.getWidth(); i++, k++) {
      for (int n = 0, j = 0; j < deck.getLen(); j++, n++) {
        color = deck.getItem(Coordinate(i, j), flag);

        if (!flag)
          ret.setItem(Coordinate(k, n), color);

        flag = false;
      }
    }

    return ret;
  }

  else {
    ColorDeck ret(deck.getLen() - deck.getLen() / 2,
                  deck.getWidth() - deck.getWidth() / 2);

    for (int k = 0, i = deck.getWidth() / 2; i < deck.getWidth(); i++, k++) {
      for (int n = 0, j = deck.getLen() / 2; j < deck.getLen(); j++, n++) {
        color = deck.getItem(Coordinate(i, j), flag);

        if (!flag)
          ret.setItem(Coordinate(k, n), color);

        flag = false;
      }
      j = deck.getLen() / 2;
    }

    return ret;
  }
}

void Zoom::zoomUp(ZOOM_STAGE stage) {
  list *temp = new list;
  temp->prev = _current;
  temp->hook = stage;
  temp->info = _zoom(_current->info, stage);
  _current = temp;
}
bool Zoom::zoomDown() {
  list *temp;
  ColorDeck tempDeck;
  if (_current->prev) {
    temp = _current;
    tempDeck = _unzoom(_current->prev->info, _current->info, _current->hook);
    _current->prev->info = tempDeck;
    _current = _current->prev;

    delete temp;
    return true;
  }

  return false;
}

void Zoom::update() {
  list *start = _current;
  start->prev = nullptr;

  list *temp;
  while (_current->prev) {
    temp = _current;
    _current = _current->prev;
    delete temp;
  }
  _current = start;
}

Zoom::~Zoom() {
  list *temp;
  while (_current->prev) {
    temp = _current;
    _current = _current->prev;
    delete temp;
  }
  delete _current;
}
