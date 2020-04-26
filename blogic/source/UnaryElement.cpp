#include "UnaryElement.hpp"

#include <cassert>

UnaryElement ::UnaryElement(CodeOfOperation code, Element *element)
    : _element(element), _code(code) {}

bool UnaryElement ::evaluate() const {
  switch (_code) {
  case BUFFER:
    return _element->evaluate();

  case INVERTER:
    return !(_element->evaluate());

  default:
    assert(0);
  }
}
