#include "InputPort.hpp"

InputPort ::InputPort(const std::string &str, bool value)
    : Port(str), _value(value) {}

void InputPort ::setValue(bool value) { _value = value; }

bool InputPort ::getValue() const { return _value; }