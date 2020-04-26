#ifndef __WRITER__HPP__
#define __WRITER__HPP__

#include <string>

class ColorDeck;

class Writer {
  const std::string &_fileName;
  const std::string _fileExt;
  const ColorDeck &_link;

  void _writeXML() const;
  void _writeIMAGE() const;

public:
  Writer(const Writer &) = delete;
  Writer &operator=(const Writer &) = delete;

  Writer(const std::string &fileName, const ColorDeck &link);

  void write() const;
};

#endif // __WRITER__HPP__