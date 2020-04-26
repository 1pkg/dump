#ifndef INPUT_PORT_H
#define INPUT_PORT_H

#include "Port.hpp"

class InputPort : public Port {
  bool _value;

public:
  InputPort(const std::string &str, bool value = false);

  void setValue(bool value);
  virtual bool getValue() const override;
};

#endif