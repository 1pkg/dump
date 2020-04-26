#ifndef __READER__HPP__
#define __READER__HPP__

#include <string>

class ColorDeck;

class Reader {

  const std::string &_fileName;
  const std::string _fileExt;
  ColorDeck &_link;

  void _readXML();
  void _readIMAGE();

public:
  Reader(const Reader &) = delete;
  Reader &operator=(const Reader &) = delete;

  Reader(const std::string &fileName, ColorDeck &link);

  void read();
};

#endif // __READER__HPP__