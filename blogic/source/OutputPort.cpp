#include "OutputPort.hpp"
#include "Element.hpp"

OutputPort ::OutputPort(const std::string &str, Element *element)
    : Port(str), _element(element) {}

void OutputPort ::setConnect(Element *element) { _element = element; }

void OutputPort ::breakConnect() { _element = nullptr; }

bool OutputPort ::getValue() const {
  if (_element != nullptr)
    return _element->evaluate();

  return false;
}