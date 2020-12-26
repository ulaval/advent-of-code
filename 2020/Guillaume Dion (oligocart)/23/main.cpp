// AoC 2020-23

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "CupList.h"

int main(int argc, char* argv[])
{
    const std::string input{"789465123"};

    // Part 1
    CupList cups{input};
    for (int i = 1; i <= 100; i++) {
        std::cout << "-- move " << i << " --\n";
        std::cout << cups << '\n';
        cups.move();
        std::cout << std::endl;
    }
    std::cout << cups << '\n';
    std::ostringstream oss;
    cups.print_list(oss, cups.next(cups.find(1)), 8);
    std::cout << "Part 1 answer = " << oss.str() << std::endl;

    // Part 2
    CupList mcups{input, true};

    return 0;
}
