#ifndef ELEMENT_H
#define ELEMENT_H

class Element {

protected:
  Element() {}

public:
  virtual bool evaluate() const = 0;

  virtual ~Element() {}
};

#endif