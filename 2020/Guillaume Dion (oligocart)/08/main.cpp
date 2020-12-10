// AoC 2020-08

#include <cassert>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

#include "BootCode.h"

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    BootCode program;
    Instruction i;
    while (input_file >> i) {
        program.add_instruction(i);
    }

    // Part 1
    assert(program.execute() == false);
    std::cout << "Part 1 answer = " << program.get_accumulator() << '\n';
    program.reset();

    // Part 2
    const auto& code = program.get_code();
    for (auto opi = code.size(); opi-- > 0; ) {
        if (code[opi].op != OpCode::ACC) {
            program.flip_op(opi);
            if (program.execute()) {
                std::cout << "Part 2 answer = " << program.get_accumulator() << '\n';   
            }
            program.reset();
        }
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
