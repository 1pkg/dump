#ifndef INPUT_PORT_ELEMENT_H
#define INPUT_PORT_ELEMENT_H

#include "Element.hpp"
#include "InputPort.hpp"

class InputPortElement : public InputPort, public Element {
public:
  InputPortElement(const std::string &str, bool value = false);

  virtual bool evaluate() const override;
};

#endif
