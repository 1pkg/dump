#include "Format.hpp"

#include "Reader.hpp"
#include "Writer.hpp"

Format::Format() : _wr(nullptr), _rd(nullptr) {}

void Format::writeFile(const std::string &fileName, const ColorDeck &link) {
  _wr = new Writer(fileName, link);
  _wr->write();
  delete _wr;
}

void Format::readFile(const std::string &fileName, ColorDeck &link) {
  _rd = new Reader(fileName, link);
  _rd->read();
  delete _rd;
}
