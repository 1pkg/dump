#include "Color.hpp"

#include <algorithm>
#include <exception>
#include <regex>

Color::P_OneColor::P_OneColor(unsigned int mask) : mask(mask) {}

Color::Color(const std::string &colorHash, const std::string &opacityHash)
    : _color(
          (static_cast<unsigned int>(strtol(colorHash.data(), NULL, 16)) << 8) |
          static_cast<unsigned int>(strtol(opacityHash.data(), NULL, 16))) {

  if (!std::regex_match(colorHash.data(), std::regex("[0-9A-Fa-f]{6}")) ||
      !std::regex_match(opacityHash.data(), std::regex("[0-9A-Fa-f]{2}")))
    throw std::exception();
}

Color::Color() : _color(0) {}

Color::Color(unsigned int mask) : _color(mask) {}

std::string Color::getColor() const {
  char buf[7] = {0};
  std::string str = itoa(_color.mask >> 8, buf, 16);

  while (str.length() < 6)
    str.insert(0, 1, '0');

  return str;
}

std::string Color::getOpacity() const {
  char buf[3] = {0};
  std::string str = itoa(_color.param.opacity, buf, 16);

  while (str.length() < 2)
    str.insert(0, 1, '0');

  return str;
}

std::string Color::serialize() const { return getColor() + "_" + getOpacity(); }

Color Color::unserialize(std::string const &str) {
  std::size_t pos = str.find('_');
  std::string color = str.substr(0, pos);
  std::string opacity = str.substr(pos + 1);

  return Color(color, opacity);
}
