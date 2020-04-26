#include "BinaryElement.hpp"
#include "CodeOfOperetion.hpp"
#include "CombinationalCircuit.hpp"
#include "Element.hpp"
#include "InputPort.hpp"
#include "InputPortElement.hpp"
#include "Interpreter.hpp"
#include "OutputPort.hpp"
#include "Port.hpp"
#include "UnaryElement.hpp"


#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string.h>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

std::vector<std::pair<std::string, int>> Interpretator ::_warnings;
std::vector<std::pair<std::string, int>> Interpretator ::_errors;

int Interpretator ::_nLine;

void Interpretator ::setLine(int line) { _nLine = line; }

int Interpretator ::getLine() { return _nLine; }

void Interpretator ::addWarning(std::string text, int line) {
  _warnings.push_back(std::make_pair(text, line));
}

void Interpretator ::addError(std::string text, int line) {

  _errors.push_back(std::make_pair(text, line));
}

void Interpretator ::showAllTrouble(std::stringstream &problems) const {
  int size = _errors.size();

  problems << "\nerrors:\n";
  for (int i = 0; i < size; i++) {
    if (_errors.at(i).second == -1)
      problems << "builder error: " << _errors.at(i).first << "\n";
    else
      problems << "parser error: " << _errors.at(i).first << " at line "
               << _errors.at(i).second << "\n";
    ;
  }

  size = _warnings.size();
  problems << "warnings:\n";
  for (int i = 0; i < size; i++) {
    problems << "builder warning: " << _warnings.at(i).first << "\n";
  }
}

int Interpretator ::countError() const { return _errors.size(); }

int Interpretator ::countWarrning() const { return _warnings.size(); }

void getLine(std::ifstream &file, std::string &str) {
  std::getline(file, str);
  Interpretator ::setLine(Interpretator ::getLine() + 1);
}

void cleanWhiteSpaceAtStart(std::string &str) {
  while (str.front() == ' ')
    str.erase(0, 1);
}

std::string readName(std::string &str) {
  static std::string result;
  result.clear();

  int posit = str.find(",");

  if (posit + 1 == str.size())
    Interpretator ::addError("unrecognized charset at",
                             Interpretator ::getLine());

  if (posit == std::string::npos)
    posit = str.size();

  result = str.substr(0, posit);

  str.erase(0, posit + 1);

  return result;
}

std::string createEntytyFile(std::ifstream &file, const std::string &name) {
  std::string fileName = name;
  fileName += ".nty";

  std ::ofstream res(fileName);

  std::regex regular("[A-Za-z]+[A-Za-z0-9]*");

  std::regex end("(end)[ ]*");
  std::regex beginEntity("(begin)[ ]+(entity)[ ]*");
  std::regex in("^(in:)[ ]*");
  std::regex out("^(out:)[ ]*");

  std::regex beginSimulation("(begin)[ ]+(simulation)[ ]*");
  std::regex expression("[A-Za-z]+[A-Za-z0-9]*[ ]+(set)[ ]+(true|false)[ ]*");

  std::regex beginArch("(begin)[ ]+(architecture)[ ]*");
  std::regex signal("^(signal:)[ ]*");
  std::regex start("(start:)[ ]*");

  std::unordered_map<std::string, bool> inputs;

  std::vector<std::string> outputs;

  std::vector<std::string> signals;

  std::unordered_set<std::string> portRegister;

  std::string str;

  while (!file.eof()) {
    getLine(file, str);

    if (std::regex_match(str, beginEntity) && portRegister.empty()) {
      std::string buf;

      getLine(file, str);

      while (!std::regex_match(str, end)) {

        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
          break;
        }

        else if (std::regex_search(str, in) && inputs.empty()) {
          str.erase(0, strlen("in:"));
          cleanWhiteSpaceAtStart(str);

          while (!str.empty()) {
            buf = readName(str);

            if (!std::regex_match(buf, regular)) {
              Interpretator ::addError(buf + " is bad port name",
                                       Interpretator ::getLine());
              break;
            }

            auto it = portRegister.find(buf);

            if (it != portRegister.end()) {
              Interpretator ::addError(buf + " port redefinithion",
                                       Interpretator ::getLine());
              break;
            }

            portRegister.insert(buf);
            inputs.insert(make_pair(buf, false));
          }
        }

        else if (std::regex_search(str, out) && outputs.empty()) {
          str.erase(0, strlen("out: "));
          cleanWhiteSpaceAtStart(str);

          while (!str.empty()) {
            buf = readName(str);

            if (!std::regex_match(buf, regular)) {
              Interpretator ::addError(buf + " is bad port name",
                                       Interpretator ::getLine());
              break;
            }

            auto it = portRegister.find(buf);

            if (it != portRegister.end()) {
              Interpretator ::addError(buf + " port redefinithion",
                                       Interpretator ::getLine());
              break;
            }

            portRegister.insert(buf);
            outputs.push_back(buf);
          }
        }

        else if (str.empty()) {
        }

        else if (std::regex_search(str, in) && !inputs.empty()) {
          Interpretator ::addError("multipy in block",
                                   Interpretator ::getLine());
        }

        else if (std::regex_search(str, out) && !outputs.empty()) {
          Interpretator ::addError("multipy out block",
                                   Interpretator ::getLine());
        }

        else {
          Interpretator ::addError("unrecognized charset",
                                   Interpretator ::getLine());
        }

        getLine(file, str);
      }

    }

    else if (std::regex_match(str, beginSimulation) && !inputs.empty()) {

      std::string portName;

      getLine(file, str);

      std::unordered_set<std::string> unforgotten;

      while (!std::regex_match(str, end)) {

        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
          break;
        }

        else if (std::regex_match(str, expression)) {
          portName = str.substr(0, str.find(" "));
          str.erase(0, str.find(" "));

          auto it = inputs.find(portName);

          if (it != inputs.end()) {

            if (str.find("true") != std::string::npos)
              it->second = true;

            unforgotten.insert(it->first);

          } else {
            Interpretator ::addError(portName + "undefined port",
                                     Interpretator ::getLine());
          }

        }

        else if (str.empty()) {
        } else {
          Interpretator ::addError("unrecognized charset",
                                   Interpretator ::getLine());
        }

        getLine(file, str);
      }

      auto it = inputs.begin();

      while (it != inputs.end()) {
        if (unforgotten.find(it->first) == unforgotten.end())
          Interpretator ::addWarning(it->first + " default false use");
        it++;
      }

    }

    else if (std::regex_match(str, beginArch)) {

      getLine(file, str);
      std::string buf;

      while (!std::regex_match(str, end)) {

        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
          break;
        }

        else if (std::regex_search(str, signal) && signals.empty()) {
          str.erase(0, strlen("signal:"));
          cleanWhiteSpaceAtStart(str);

          while (!str.empty()) {
            buf = readName(str);

            if (!std::regex_match(buf, regular)) {
              Interpretator ::addError(buf + " is bad signal name",
                                       Interpretator ::getLine());
              break;
            }

            auto it = portRegister.find(buf);

            if (it != portRegister.end()) {
              Interpretator ::addError(buf + " signal redefinithion",
                                       Interpretator ::getLine());
              break;
            }

            portRegister.insert(buf);
            signals.push_back(buf);
          }

        } else if (std::regex_search(str, signal) && !signals.empty()) {
          Interpretator ::addError("multipy signal block",
                                   Interpretator ::getLine());
        } else if (std::regex_match(str, start)) {

          while (!std::regex_match(str, end)) {
            getLine(file, str);

            if (file.eof()) {
              Interpretator ::addError("unexpected end of file",
                                       Interpretator ::getLine());
              break;
            }
          }

        }

        else if (str.empty()) {
        }

        else {
          Interpretator ::addError("unrecognized charset",
                                   Interpretator ::getLine());
        }

        if (!std::regex_match(str, end))
          getLine(file, str);
      }

    }

    else if (std::regex_match(str, beginEntity) && !portRegister.empty()) {

      Interpretator ::addError("multipy entity block",
                               Interpretator ::getLine());
    }

    else if (std::regex_match(str, beginSimulation) && inputs.empty()) {
      Interpretator ::addError("no existing ports", Interpretator ::getLine());

    }

    else if (std::regex_match(str, beginArch) && !signals.empty()) {
      Interpretator ::addError("multipy architecture block",
                               Interpretator ::getLine());

    }

    else if (str.empty()) {
    } else {
      Interpretator ::addError("unrecognized charset",
                               Interpretator ::getLine());
    }
  }
  if (Interpretator ::getLine() == 1) {
    Interpretator ::addError("unexpected end of file",
                             Interpretator ::getLine());
  }

  int size = inputs.size();

  res << "IN\n";

  auto it = inputs.begin();
  while (it != inputs.end()) {
    res << it->first << ":" << it->second << "\n";
    it++;
  }

  res << "OUT\n";

  size = outputs.size();

  for (int i = 0; i < size; i++)
    res << outputs[i] << "\n";

  res << "SIGNAL\n";

  size = signals.size();

  for (int i = 0; i < size; i++)
    res << signals[i] << "\n";

  res.close();

  return fileName;
}

void cleanWhiteSpace(std::string &str) {

  int position = str.find(' ');

  while (position != std::string::npos) {
    if ((str.substr(position + 1, 2) == "OR" ||
         str.substr(position + 1, 3) == "XOR" ||
         str.substr(position + 1, 3) == "AND")) {
      str.insert(position + 1, "|");

    }

    else if ((position - 2 > 0 && str.substr(position - 2, 2) == "OR") ||
             (position - 3 > 0 && (str.substr(position - 3, 3) == "XOR" ||
                                   str.substr(position - 3, 3) == "AND" ||
                                   str.substr(position - 3, 3) == "BUF" ||
                                   str.substr(position - 3, 3) == "NOT"))) {

      str.insert(position, "|");
      position = str.find(' ');
    }

    str.erase(position, 1);
    position = str.find(' ');
  }
}

std::string createArchFile(std::ifstream &file, const std::string &name) {
  std::string fileName = name;
  fileName += ".arch";

  std ::ofstream res(fileName);

  std::vector<std::string> operations;

  std::regex end("(end)[ ]*");

  std::regex beginArch("(begin)[ ]+(architecture)[ ]*");
  std::regex signal("^(signal:)[ ]*");
  std::regex start("(start:)[ ]*");

  std::regex beginEntity("(begin)[ ]+(entity)[ ]*");
  std::regex beginSimulation("(begin)[ ]+(simulation)[ ]*");

  std::regex regular("([A-Za-z][A-Za-z0-9]*[ ]*)[=]([ ]*[A-Za-z][A-Za-z0-9]*[ "
                     "]*)(AND|OR|XOR)([ ]*[A-Za-z][A-Za-z0-9]*[ ]*)",
                     std::regex::optimize);
  std::regex regularUnary("([A-Za-z][A-Za-z0-9]*[ ]*)[=][ ]*(NOT|BUF)[ ]*([ "
                          "]*[A-Za-z][A-Za-z0-9]*[ ]*)",
                          std::regex::optimize);

  std::string str;

  while (!file.eof()) {
    getLine(file, str);

    if (std::regex_match(str, beginArch) && operations.empty()) {

      getLine(file, str);

      while (!std::regex_match(str, end)) {

        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
          break;
        }

        else if (std::regex_match(str, start) && operations.empty()) {
          getLine(file, str);

          while (!std::regex_match(str, end)) {

            if (file.eof()) {
              Interpretator ::addError("unexpected end of file",
                                       Interpretator ::getLine());
              break;
            } else if (std::regex_match(str, regular) ||
                       std::regex_match(str, regularUnary)) {
              cleanWhiteSpace(str);
              operations.push_back(str);
            }

            else if (str.empty()) {
            }

            else {
              Interpretator ::addError("unrecognized charset",
                                       Interpretator ::getLine());
            }
            getLine(file, str);
          }

        }

        else if (std::regex_match(str, start) && !operations.empty()) {
          Interpretator ::addError("multipy start block",
                                   Interpretator ::getLine());
        } else if (str.empty() || std::regex_search(str, signal)) {
        }

        else {
          Interpretator ::addError("unrecognized charset",
                                   Interpretator ::getLine());
        }

        if (!std::regex_match(str, end))
          getLine(file, str);
      }

    }

    else if (std::regex_match(str, beginArch) && !operations.empty()) {
      Interpretator ::addError("multipy architecture block",
                               Interpretator ::getLine());

    }

    else if (std::regex_match(str, beginEntity)) {
      while (!std::regex_match(str, end)) {

        getLine(file, str);
        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
        }
      }
    }

    else if (std::regex_match(str, beginSimulation)) {
      while (!std::regex_match(str, end)) {

        getLine(file, str);
        if (file.eof()) {
          Interpretator ::addError("unexpected end of file",
                                   Interpretator ::getLine());
        }
      }
    }

    else if (str.empty()) {
    }

    else {
      Interpretator ::addError("unrecognized charset",
                               Interpretator ::getLine());
    }
  }

  int size = operations.size();

  for (int i = 0; i < size; i++)
    res << operations[i] << "\n";

  res.close();
  return fileName;
}

std::string cleanExpresion(std::string &str) {
  static std::string result;
  result.clear();

  int posit = str.find("=");

  result = str;

  result.erase(posit, str.size());

  str.erase(0, posit + 1);

  return result;
}

CodeOfOperation getCode(const std::string &str) {
  if (str == "NOT")
    return INVERTER;
  else if (str == "BUF")
    return BUFFER;
  else if (str == "OR")
    return OR;
  else if (str == "AND")
    return AND;
  else
    return XOR;
}

Element *createElemenet(
    std::string string, std ::unordered_map<std::string, InputPort *> inputs,
    std ::unordered_map<std::string, InputPortElement *> internalPorts,
    std::vector<Port *> &addithional) {
  Element *tempElement = nullptr;
  InputPortElement *transformElementLeft = nullptr;
  InputPortElement *transformElementRight = nullptr;
  std::string tempInputPortElementLeft;
  std::string tempInputPortElementRight;

  int posit = string.find('|');

  if (string.substr(0, posit) == "NOT" || string.substr(0, posit) == "BUF") {
    tempInputPortElementRight = string.substr(posit + 1, string.size());

    if (inputs.find(tempInputPortElementRight) != inputs.end()) {
      auto it = inputs.find(tempInputPortElementRight);
      transformElementRight =
          new InputPortElement(it->first, it->second->getValue());

      addithional.push_back(transformElementRight);

      tempElement = new UnaryElement(getCode(string.substr(0, posit)),
                                     transformElementRight);
    } else if (internalPorts.find(tempInputPortElementRight) !=
               internalPorts.end()) {
      auto it = internalPorts.find(tempInputPortElementRight);

      tempElement =
          new UnaryElement(getCode(string.substr(0, posit)), it->second);

    }

    else {
      Interpretator ::addError(tempInputPortElementRight + " undefined port");
    }

  }

  else {
    tempInputPortElementLeft = string.substr(0, posit);

    string.erase(0, posit + 1);
    posit = string.find('|');

    tempInputPortElementRight = string.substr(posit + 1, string.size());

    if (inputs.find(tempInputPortElementLeft) != inputs.end() &&
        inputs.find(tempInputPortElementRight) != inputs.end()) {
      auto itRight = inputs.find(tempInputPortElementRight);
      auto itLeft = inputs.find(tempInputPortElementLeft);

      transformElementLeft =
          new InputPortElement(itLeft->first, itLeft->second->getValue());
      transformElementRight =
          new InputPortElement(itRight->first, itRight->second->getValue());

      addithional.push_back(transformElementLeft),
          addithional.push_back(transformElementRight);

      tempElement =
          new BinaryElement(getCode(string.substr(0, posit)),
                            transformElementLeft, transformElementRight);
    } else if (inputs.find(tempInputPortElementLeft) != inputs.end() &&
               internalPorts.find(tempInputPortElementRight) !=
                   internalPorts.end()) {
      auto itRight = internalPorts.find(tempInputPortElementRight);
      auto itLeft = inputs.find(tempInputPortElementLeft);

      transformElementLeft =
          new InputPortElement(itLeft->first, itLeft->second->getValue());

      addithional.push_back(transformElementLeft);

      tempElement = new BinaryElement(getCode(string.substr(0, posit)),
                                      transformElementLeft, itRight->second);

    }

    else if (internalPorts.find(tempInputPortElementLeft) !=
                 internalPorts.end() &&
             inputs.find(tempInputPortElementRight) != inputs.end()) {
      auto itRight = inputs.find(tempInputPortElementRight);
      auto itLeft = internalPorts.find(tempInputPortElementLeft);

      transformElementRight =
          new InputPortElement(itRight->first, itRight->second->getValue());

      addithional.push_back(transformElementRight);

      tempElement = new BinaryElement(getCode(string.substr(0, posit)),
                                      itLeft->second, transformElementRight);
    }

    else if (internalPorts.find(tempInputPortElementLeft) !=
                 internalPorts.end() &&
             internalPorts.find(tempInputPortElementRight) !=
                 internalPorts.end()) {
      auto itRight = internalPorts.find(tempInputPortElementRight);
      auto itLeft = internalPorts.find(tempInputPortElementLeft);

      tempElement = new BinaryElement(getCode(string.substr(0, posit)),
                                      itLeft->second, itRight->second);

    } else {
      if (internalPorts.find(tempInputPortElementLeft) == internalPorts.end() &&
          inputs.find(tempInputPortElementLeft) == inputs.end())
        Interpretator ::addError(tempInputPortElementLeft + " undefined port");
      if (internalPorts.find(tempInputPortElementRight) ==
              internalPorts.end() &&
          inputs.find(tempInputPortElementRight) == inputs.end())
        Interpretator ::addError(tempInputPortElementRight + " undefined port");
    }
  }

  return tempElement;
}

CombinationalCircuit *mainParse(std::pair<std::string, std::string> fileNames) {

  std ::ifstream entity(fileNames.first);

  InputPort *tempInputPort;
  std ::unordered_map<std::string, InputPort *> inputs;

  OutputPort *tempOutputPort;
  std ::unordered_map<std::string, OutputPort *> outputs;

  InputPortElement *tempInputPortElement;
  std ::unordered_map<std::string, InputPortElement *> internalPorts;

  std::string str;

  while (!entity.eof()) {
    if (str != "OUT" && str != "SIGNAL")
      std::getline(entity, str);

    if (str == "IN") {
      std::getline(entity, str);

      while (str != "OUT" && str != "SIGNAL" && !entity.eof()) {
        tempInputPort =
            new InputPort(str.substr(0, str.find(':')),
                          static_cast<bool>(str.at(str.find(':') + 1) - '0'));
        inputs.insert(std::make_pair(tempInputPort->getName(), tempInputPort));

        std::getline(entity, str);
      }
    }

    else if (str == "OUT") {
      std::getline(entity, str);

      while (str != "SIGNAL" && !entity.eof()) {

        tempOutputPort = new OutputPort(str);
        outputs.insert(std::make_pair(str, tempOutputPort));

        std::getline(entity, str);
      }
    }

    else {

      std::getline(entity, str);

      while (!entity.eof()) {
        tempInputPortElement = new InputPortElement(str);
        internalPorts.insert(std::make_pair(str, tempInputPortElement));

        std::getline(entity, str);
      }
    }
  }

  std ::ifstream arch(fileNames.second);

  Element *tempElement;
  std::vector<Element *> elements;
  std::vector<Port *> addithional;

  std::vector<Port *> ports;

  std::string portNameUniq;
  std::unordered_set<std::string> registryPort;

  std::getline(arch, str);

  while (!arch.eof()) {

    portNameUniq = cleanExpresion(str);

    if (registryPort.find(portNameUniq) != registryPort.end()) {
      Interpretator ::addError(portNameUniq + " signal initialized already");
    } else if (internalPorts.find(portNameUniq) != internalPorts.end()) {

      tempElement = createElemenet(str, inputs, internalPorts, addithional);
      elements.push_back(tempElement);

      auto it = internalPorts.find(portNameUniq);

      if (tempElement == nullptr) {
        std::getline(arch, str);
        continue;
      }

      it->second->setValue(tempElement->evaluate());

      registryPort.insert(it->first);
    } else if (outputs.find(portNameUniq) != outputs.end()) {
      tempElement = createElemenet(str, inputs, internalPorts, addithional);
      elements.push_back(tempElement);

      auto it = outputs.find(portNameUniq);
      it->second->setConnect(tempElement);

      registryPort.insert(it->first);
    } else {
      Interpretator ::addError(portNameUniq + " udefined signal using");
    }

    std::getline(arch, str);
  }

  auto internalPortsCheck = internalPorts.begin();
  while (internalPortsCheck != internalPorts.end()) {
    if (registryPort.find(internalPortsCheck->first) == registryPort.end())
      Interpretator::addWarning(internalPortsCheck->first + " unusing signal");

    internalPortsCheck++;
  }

  auto outputsPortsCheck = outputs.begin();
  while (outputsPortsCheck != outputs.end()) {
    if (registryPort.find(outputsPortsCheck->first) == registryPort.end())
      Interpretator::addWarning(outputsPortsCheck->first +
                                " default output port, false use");

    outputsPortsCheck++;
  }

  auto itInput = inputs.begin();

  while (itInput != inputs.end()) {
    ports.push_back(itInput->second);
    itInput++;
  }

  auto itInternal = internalPorts.begin();

  while (itInternal != internalPorts.end()) {
    ports.push_back(itInternal->second);
    itInternal++;
  }

  int size = addithional.size();

  for (int i = 0; i < size; i++)
    ports.push_back(addithional[i]);

  auto itOutput = outputs.begin();

  while (itOutput != outputs.end()) {
    ports.push_back(itOutput->second);
    itOutput++;
  }

  return new CombinationalCircuit(elements.data(), ports.data(),
                                  elements.size(), ports.size(),
                                  outputs.size());
}

Interpretator ::Interpretator(const std::string &fileName)
    : _fileName(fileName) {}

CombinationalCircuit *Interpretator ::Parse() {
  std::pair<std::string, std::string> orderedFiles;

  std::ifstream file(_fileName);

  setLine(0);

  orderedFiles.first = createEntytyFile(file, _fileName);

  file.clear();
  file.seekg(0);
  setLine(0);

  orderedFiles.second = createArchFile(file, _fileName);

  return mainParse(orderedFiles);
}
