// AoC 2020-17

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "Grid.h"
#include "Grid4D.h"

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    std::vector<std::string> plane;
    std::copy(std::istream_iterator<std::string>{input_file}, std::istream_iterator<std::string>{}, std::back_inserter(plane));

    // Part 1
    Grid grid1{plane};
    for (int i=0; i < 6; i++) {
        grid1.update();
    }
    std::cout << "Part 1 answer = " << grid1.active_cubes() << '\n';

    // Part 2
    Grid4D grid2{plane};
    // std::cout << grid2 << '\n';
    // std::cout << "---------\n";
    for (int i=0; i < 6; i++) {
        grid2.update();
        // std::cout << grid2 << '\n';
        // std::cout << "---------\n";
    }
    std::cout << "Part 2 answer = " << grid2.active_cubes() << '\n';
}
