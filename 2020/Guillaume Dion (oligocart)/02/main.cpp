// AoC 2020-02

#include <chrono>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    // Part 1
    std::vector<int> amount;
    std::string line;
    unsigned valid_count_1, valid_count_2 = 0;
    while (std::getline(input_file, line)) {
        unsigned min, max;
        char ch, dummy;
        std::string passwd;
        std::istringstream iss(line);
        iss >> min >> dummy >> max >> ch >> dummy >> passwd;

        // Part 1
        auto cnt = std::count(passwd.cbegin(), passwd.cend(), ch);
        if (min <= cnt && cnt <= max) {
            valid_count_1++;
        }

        // Part 2
        if ((passwd.at(min-1) == ch || passwd.at(max-1) == ch) &&
            !(passwd.at(min-1) == ch && passwd.at(max-1) == ch)) {
            valid_count_2++;
        }
    }
    std::cout << "Part 1 answer : " << valid_count_1 << '\n';
    std::cout << "Part 2 answer : " << valid_count_2 << '\n';

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
