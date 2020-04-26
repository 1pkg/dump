#ifndef UNARY_ELEMENT_H
#define UNARY_ELEMENT_H

#include "CodeOfOperetion.hpp"
#include "Element.hpp"

class UnaryElement : public Element {
  Element *_element;
  const CodeOfOperation _code;

public:
  UnaryElement(CodeOfOperation code, Element *element);

  virtual bool evaluate() const override;
};

#endif
