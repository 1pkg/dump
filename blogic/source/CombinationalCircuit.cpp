#include "CombinationalCircuit.hpp"
#include "Element.hpp"
#include "Port.hpp"

CombinationalCircuit ::CombinationalCircuit(Element **elements, Port **ports,
                                            int countElements, int countPorts,
                                            int countOutpusts)
    : _elements(elements, elements + countElements),
      _ports(ports, ports + countPorts), _countOutpusts(countOutpusts) {}

CombinationalCircuit ::~CombinationalCircuit() {

  int size = _elements.size();

  for (int i = 0; i < size; i++)
    delete _elements[i];

  size = _ports.size();

  for (int i = 0; i < size; i++)
    delete _ports[i];
}

void CombinationalCircuit ::exute(std::stringstream &stream) const {

  int size = _ports.size();

  for (int i = size - _countOutpusts; i < size; i++) {
    stream << _ports[i]->getName() << ":" << _ports[i]->getValue() << "\n";
  }
}