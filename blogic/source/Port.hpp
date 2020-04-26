#ifndef PORT_H
#define PORT_H

#include <string>

class Port {
  std::string _str;

protected:
  Port(const std::string &str) : _str(str) {}

public:
  virtual bool getValue() const = 0;

  std::string getName() const { return _str; }
};

#endif