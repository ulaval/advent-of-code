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
    // const std::string input{"389125467"};       // example

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
    cups.print_list(oss, cups.next(1), 8);
    std::cout << "Part 1 answer = " << oss.str() << std::endl;

    // Part 2
    CupList mcups{input, 1'000'000};
    for (int i = 1; i <= 10'000'000; i++) {
        mcups.move();
    }
    std::ostringstream oss2;
    mcups.print_list(oss2, mcups.next(1), 2);
    std::cout << "Part 2 answer = " << oss2.str() << std::endl;

    return 0;
}
