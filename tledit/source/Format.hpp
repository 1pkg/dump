#ifndef __FORMAT__HPP__
#define __FORMAT__HPP__

#include <string>

class Writer;
class Reader;

class ColorDeck;

class Format {

  Writer *_wr;
  Reader *_rd;

  Format(const Format &);
  Format &operator=(const Format &);

public:
  Format();

  void writeFile(const std::string &fileName, const ColorDeck &link);
  void readFile(const std::string &fileName, ColorDeck &link);
};

#endif // __FORMAT__HPP__