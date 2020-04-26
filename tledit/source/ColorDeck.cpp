#include "ColorDeck.hpp"

#include <algorithm>
#include <limits.h>

ColorDeck::ColorDeck() : _lenght(0), _width(0) {}
ColorDeck::ColorDeck(unsigned short lenght, unsigned short width)
    : _lenght(lenght), _width(width) {
  if (_lenght <= MIN_SIZE || _width <= MIN_SIZE)
    throw std::exception();
}

Color ColorDeck::getItem(Coordinate index) const {
  auto search = _deck.find(index);
  if (search == _deck.end())
    throw std::exception();

  return search->second;
}

Color &ColorDeck::getItem(Coordinate index) {
  auto search = _deck.find(index);
  if (search == _deck.end())
    throw std::exception();

  return search->second;
}

void ColorDeck::setItem(Coordinate index, const Color &color) {

  if (_deck.find(index) != _deck.end())
    throw std::exception();

  if (!Color::isWhite(color))
    _deck.insert(std::make_pair(index, color));
}

Color ColorDeck::getItem(Coordinate index, bool &fail) const {
  auto search = _deck.find(index);
  if (search == _deck.end()) {
    fail = true;
    return Color("FFFFFF", "00");
  }

  return search->second;
}

void ColorDeck::setItem(Coordinate index, const Color &color, bool &fail) {

  if (_deck.find(index) != _deck.end()) {
    fail = true;
    return;
  }

  if (!Color::isWhite(color))
    _deck.insert(std::make_pair(index, color));
}

void ColorDeck::deleteItem(Coordinate index) {
  auto search = _deck.find(index);
  if (search == _deck.end())
    throw std::exception();

  _deck.erase(index);
}

std::stringstream ColorDeck::serialize() const {
  std::stringstream res;

  std::for_each(_deck.begin(), _deck.end(),
                [&res](std::unordered_map<Coordinate, Color>::value_type it) {
                  res << it.first.x;
                  res << ",";
                  res << it.first.y;
                  res << "=";
                  res << it.second.serialize();
                  res << "\n";
                });

  res << "\0";
  return res;
}

ColorDeck ColorDeck::unserialize(std::stringstream &stream,
                                 unsigned short lenght, unsigned short width) {
  std::string str, color;
  ColorDeck colorDeck(lenght, width);
  Coordinate index;

  while (stream >> str) {
    index.x = atoi(str.substr(0, str.find(',')).data());
    index.y = atoi(str.substr(str.find(',') + 1, str.find('=')).data());
    color = str.substr(str.find('=') + 1);
    colorDeck.setItem(index, Color::unserialize(color));
  }

  return colorDeck;
}
