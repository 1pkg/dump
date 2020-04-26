#include "BinaryElement.hpp"

#include <cassert>

BinaryElement ::BinaryElement(CodeOfOperation code, Element *firstElement,
                              Element *secondElement)
    : _firstElement(firstElement), _secondElement(secondElement), _code(code) {}

bool BinaryElement ::evaluate() const {

  switch (_code) {
  case AND:
    return _firstElement->evaluate() && _secondElement->evaluate();

  case OR:
    return _firstElement->evaluate() || _secondElement->evaluate();
    break;

  case XOR:
    return _firstElement->evaluate() ^ _secondElement->evaluate();
    break;

  default:
    assert(0);
  }
}
