#include "InputPortElement.hpp"

InputPortElement ::InputPortElement(const std::string &str, bool value)
    : InputPort(str, value) {}

bool InputPortElement ::evaluate() const { return InputPort::getValue(); }
