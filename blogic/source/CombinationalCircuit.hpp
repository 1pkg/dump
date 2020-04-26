#ifndef COMBINATIONAL_CIRCUIT_H
#define COMBINATIONAL_CIRCUIT_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

class Element;
class Port;

class CombinationalCircuit {
  std::vector<Element *> _elements;
  std::vector<Port *> _ports;

  int _countOutpusts;

  CombinationalCircuit(CombinationalCircuit &circuit);
  CombinationalCircuit operator=(CombinationalCircuit &circuit);

public:
  CombinationalCircuit(Element **elements, Port **ports, int countElements,
                       int countPorts, int countOutpusts);
  ~CombinationalCircuit();

  void exute(std::stringstream &stream) const;
};

#endif