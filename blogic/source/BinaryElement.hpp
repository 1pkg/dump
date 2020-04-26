#ifndef BINARY_ELEMENT_H
#define BINARY_ELEMENT_H

#include <vector>

#include "CodeOfOperetion.hpp"
#include "Element.hpp"

class BinaryElement : public Element {
  Element *_firstElement;
  Element *_secondElement;
  const CodeOfOperation _code;

public:
  BinaryElement(CodeOfOperation code, Element *firstElement,
                Element *_secondElement);

  virtual bool evaluate() const override;
};

#endif
