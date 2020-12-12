// AoC 2020-04

#include <chrono>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Passport.h"

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    std::string line, item;
    std::vector<Passport> pp(1);
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        bool continued = false;
        while (iss >> item) {
            continued = true;
            pp.back().add_attribute(std::move(item));
        }
        if (!continued) {
            pp.push_back(Passport());
        }
    }
    
    // Part 1
    auto valid_count1 = std::count_if(pp.cbegin(), pp.cend(), [](const auto& x) { return x.is_valid_p1(); });
    std::cout << "Part 1 answer : " << valid_count1 << '\n';

    // Part 2
    auto valid_count2 = std::count_if(pp.cbegin(), pp.cend(), [](const auto& x) { return x.is_valid_p2(); });
    std::cout << "Part 2 answer : " << valid_count2 << '\n';

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
