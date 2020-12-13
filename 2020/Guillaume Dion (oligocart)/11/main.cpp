// AoC 2020-11

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>

#include "Seats.h"

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    Seats s1;
    input_file >> s1;

    while (!s1.update());
    std::cout << "Part 1 answer = " << s1.num_occupied() << '\n';

    // Part 2
    input_file.clear();
    input_file.seekg(0, input_file.beg);

    Seats_v2 s2;
    input_file >> s2;

    while (!s2.update());
    std::cout << "Part 2 answer = " << s2.num_occupied() << '\n';
}
