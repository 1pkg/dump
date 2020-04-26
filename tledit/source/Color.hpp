#ifndef __COLOR__HPP__
#define __COLOR__HPP__

#include <string>

class Color {

  union P_OneColor {
    unsigned int mask;

    struct {
      unsigned short opacity : 8;
      unsigned short blue : 8;
      unsigned short green : 8;
      unsigned short red : 8;
    } param;

    P_OneColor(unsigned int mask);

  } _color;

public:
  Color();
  Color(const std::string &colorHash, const std::string &opacityHash);
  Color(unsigned int mask);

  std::string getColor() const;
  std::string getOpacity() const;
  void changeColor(const std::string &colorHash,
                   const std::string &opacityHash);

  unsigned short getRedPart() const;
  unsigned short getGreenPart() const;
  unsigned short getBluePart() const;
  unsigned short getOpacityMask() const;
  unsigned int getMask() const;

  void setRedPart(unsigned short red);
  void setGreenPart(unsigned short green);
  void setBluePart(unsigned short blue);
  void setOpacityMask(unsigned short opacity);
  void changeColor(unsigned int mask);

  static bool isWhite(const Color &color);

  std::string serialize() const;
  static Color unserialize(std::string const &str);
};

inline void Color::changeColor(const std::string &colorHash,
                               const std::string &opacityHash) {
  *this = Color(colorHash, opacityHash);
}

inline unsigned short Color::getRedPart() const { return _color.param.red; }
inline unsigned short Color::getGreenPart() const { return _color.param.green; }
inline unsigned short Color::getBluePart() const { return _color.param.blue; }
inline unsigned short Color::getOpacityMask() const {
  return _color.param.opacity;
}
inline unsigned int Color::getMask() const { return _color.mask; }

inline void Color::changeColor(unsigned int mask) { _color.mask = mask; }

inline void Color::setRedPart(unsigned short red) { _color.param.red = red; }
inline void Color::setGreenPart(unsigned short green) {
  _color.param.green = green;
}
inline void Color::setBluePart(unsigned short blue) {
  _color.param.blue = blue;
}
inline void Color::setOpacityMask(unsigned short opacity) {
  _color.param.opacity = opacity;
}

inline bool Color::isWhite(const Color &color) {
  return (color.getBluePart() == 255 && color.getGreenPart() == 255 &&
          color.getRedPart() == 255);
}

#endif //__COLOR__HPP__