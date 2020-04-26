#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <exception>
#include <fstream>
#include <sstream>
#include <vector>

class CombinationalCircuit;

class Interpretator {
  std::string _fileName;

  static int _nLine;

  static std::vector<std::pair<std::string, int>> _warnings;
  static std::vector<std::pair<std::string, int>> _errors;

public:
  static void setLine(int line);
  static int getLine();

  static void addWarning(std::string text, int line = -1);
  static void addError(std::string text, int line = -1);

  void showAllTrouble(std::stringstream &problems) const;

  int countError() const;
  int countWarrning() const;

  Interpretator(const std::string &fileName);

  ~Interpretator(){};

  CombinationalCircuit *Parse();
};

#endif