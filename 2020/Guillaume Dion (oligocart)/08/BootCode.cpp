#include <cassert>
#include <string>

#include "BootCode.h"

bool BootCode::execute()
{
    while (ip < code.size()) {
        Instruction& i = code[ip];
        if (i.executed)
            return false;   // loop détecté
        switch (i.op) {
        case OpCode::ACC:
            accumulator += i.argument;
            ip++;
            break;
        case OpCode::JMP:
            ip += i.argument;
            break;
        case OpCode::NOP:
            ip++;
            break;
        }
        i.executed = true;
    }
    return true;    // fin de programme normale
}

void BootCode::reset()
{
    undo_flip_op();
    std::for_each(code.begin(), code.end(), [](auto& i) { i.executed = false; });
    accumulator = 0;
    ip = 0;
}

void BootCode::flip_op(int op_index)
{
    if (flipped_op_index == -1 && code.at(op_index).op != OpCode::ACC) {
        code.at(op_index).flip();
        flipped_op_index = op_index;
    }
}

void BootCode::undo_flip_op()
{
    if (flipped_op_index != -1) {
        code.at(flipped_op_index).flip();
        flipped_op_index = -1;
    }
}

std::istream& operator>>(std::istream& in, OpCode& rhs)
{
    std::string op;
    in >> op;
    if (op == "acc")
        rhs = OpCode::ACC;
    else if (op == "jmp")
        rhs = OpCode::JMP;
    else if (op == "nop")
        rhs = OpCode::NOP;
    else if (op.empty())
        in.setstate(std::ios_base::eofbit);
    else
        in.setstate(std::ios_base::badbit);
    return in;
}

std::istream& operator>>(std::istream& in, Instruction& rhs)
{
    std::string arg;
    if (in >> rhs.op) {
        in >> arg;
        assert(arg[0] == '+' || arg[0] == '-');
        rhs.argument = std::stoi(arg);
    }
    return in;
}