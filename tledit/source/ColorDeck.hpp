#ifndef __COLOR__DECK__HPP__
#define __COLOR__DECK__HPP__

#include "Color.hpp"

#include <sstream>
#include <unordered_map>

struct Coordinate {
  short x, y;

  bool operator==(Coordinate const &second) const {
    return ((x == second.x) && (y == second.y));
  }

  Coordinate(short x, short y) : x(x), y(y) {}

  Coordinate() : x(0), y(0) {}
};

namespace std {
template <> struct hash<Coordinate> {
  std::size_t operator()(const Coordinate &coord) const {
    return ((hash<int>()(coord.x) | (hash<int>()(coord.y))));
  }
};
} // namespace std

class ColorDeck {

  std::unordered_map<Coordinate, Color> _deck;

  unsigned short _lenght;
  unsigned short _width;

public:
  ColorDeck();
  ColorDeck(unsigned short lenght, unsigned short _width);

  unsigned short getLen() const;
  unsigned short getWidth() const;

  void grow();
  void compress();

  // throwable
  void setItem(Coordinate index, const Color &color);
  Color getItem(Coordinate index) const;
  Color &getItem(Coordinate index);

  // nonthrowable
  void setItem(Coordinate index, const Color &color, bool &fail);
  Color getItem(Coordinate index, bool &fail) const;
  Color &getItem(Coordinate index, bool &fail);

  void deleteItem(Coordinate index);

  void clear();
  bool empty() const;

  std::stringstream ColorDeck::serialize() const;
  static ColorDeck unserialize(std::stringstream &stream, unsigned short lenght,
                               unsigned short width);

  std::unordered_map<Coordinate, Color>::iterator begin();
  std::unordered_map<Coordinate, Color>::iterator end();
};

inline unsigned short ColorDeck::getLen() const { return _lenght; }

inline unsigned short ColorDeck::getWidth() const { return _width; }

inline void ColorDeck::clear() { _deck.clear(); }

inline bool ColorDeck::empty() const { return _deck.empty(); }

inline std::unordered_map<Coordinate, Color>::iterator ColorDeck::begin() {
  return _deck.begin();
}
inline std::unordered_map<Coordinate, Color>::iterator ColorDeck::end() {
  return _deck.end();
}

#endif // __COLOR__DECK__HPP__