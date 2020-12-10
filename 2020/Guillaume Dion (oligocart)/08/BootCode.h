#pragma once

#include <iostream>
#include <vector>

enum class OpCode { NOP = 0, ACC = 1, JMP = 2 };

std::istream& operator>>(std::istream& in, OpCode& rhs);

struct Instruction
{
    void flip() { if (op != OpCode::ACC) { op = (op == OpCode::NOP) ? OpCode::JMP : OpCode::NOP; } }

    OpCode op;
    int argument;
    bool executed = false;
};

std::istream& operator>>(std::istream& in, Instruction& rhs);

class BootCode
{
public:
    void add_instruction(const Instruction& i) { code.push_back(i); }
    bool execute();
    void reset();
    void flip_op(int op_index);

    auto get_accumulator() const { return accumulator; }
    const auto& get_code() const { return code; }

private:
    void undo_flip_op();

    std::vector<Instruction> code{};
    int accumulator = 0;
    int ip = 0;     // instruction pointer
    int flipped_op_index = -1;  // -1 = aucun op modifié || index de l'op modifiée
};
