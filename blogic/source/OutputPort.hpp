#ifndef OUTPUT_PORT_H
#define OUTPUT_PORT_H

#include "Port.hpp"

class Element;

class OutputPort : public Port {
  Element *_element;

public:
  OutputPort(const std::string &str, Element *element = nullptr);

  void setConnect(Element *element);
  void breakConnect();

  virtual bool getValue() const override;
};

#endif