#pragma once

#include <iostream>
#include <string>

// Operand can be an expression or a simple value
class Operand
{
public:
    Operand() : _value{-1}, _expr{} { }         // undefined
    Operand(long value) : _value{value}, _expr{} { }      // simple value
    Operand(const std::string& expr) : _value{-1}, _expr{expr} { }      // expression
    friend std::istream& operator>>(std::istream& in, Operand& rhs);

    operator bool() const { return _value != -1 || !_expr.empty(); }

    long solve() const;

private:
    std::string _expr;
    long _value;              // -1 means operand is an expression
};

