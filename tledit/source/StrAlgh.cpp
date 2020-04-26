#include "StrAlgh.hpp"

#include <algorithm>
#include <regex>

static std::string clearName(const std::string fileName) {
  std::string s;

  auto it = fileName.rbegin();

  while (*it != '\\') {
    s += *it;
    it++;
  }

  std::reverse(s.begin(), s.end());
  return s;
}

std::string getFileExt(std::string string) {
  return string.substr(string.find('.') + 1);
}

bool rightName(const std::string string, const std::string &extens) {

  std::string reg = "[A-Za-z0-9_]{1}[A-Za-z0-9_ -]+(" + extens + ")?";
  return std::regex_match(clearName(string), std::regex(reg));
}