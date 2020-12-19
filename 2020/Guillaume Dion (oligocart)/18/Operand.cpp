#include <cassert>
#include <sstream>

#include "Operand.h"

long Operand::solve() const
{
    if (_value != -1) {
        return _value;
    }

    assert(!_expr.empty());
    std::istringstream iss(_expr);
    Operand op1, op2;
    char operation;
    iss >> op1;
    while (iss >> operation) {
        iss >> op2;
        if (operation == '+')
            op1 = op1.solve() + op2.solve();
        else if (operation == '*')
            op1 = op1.solve() * op2.solve();
    }
    return op1.solve();
}

std::istream& operator>>(std::istream& in, Operand& rhs)
{
    in >> std::ws;
    char ch = in.peek();
    if (in.good()) {
        if (std::isdigit(ch)) {
            // read simple value
            in >> rhs._value;
            rhs._expr.clear();
        }
        else if (ch == '(') {
            // read expression
            std::ostringstream oss;
            in >> ch;
            int level = 1;
            while (level != 0) {
                in >> std::ws;
                ch = in.peek();
                if (ch == '(') {
                    level++;
                }
                else if (ch == ')') {
                    level--;
                }
                in >> ch;
                if (level != 0)
                    oss << ch;
            }
            rhs._expr = oss.str();
            rhs._value = -1;
        }
        else if (ch == EOF) {
            in.setstate(std::ios_base::eofbit);
        }
        else {
            in.setstate(std::ios_base::badbit);
        }
    }
    return in;
}