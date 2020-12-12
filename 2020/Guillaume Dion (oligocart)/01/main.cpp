// AoC 2020-01

#include <chrono>
#include <iterator>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    std::vector<int> amount;
    std::copy(std::istream_iterator<int>{input_file}, std::istream_iterator<int>{}, std::back_inserter(amount));

    // Part 1
    for (auto it1 = amount.cbegin(); it1 != amount.cend(); it1++) {
        for (auto it2 = std::next(it1); it2 != amount.cend(); it2++) {
            if (*it1 + *it2 == 2020) {
                std::cout << "Part 1 Answer : " << *it1 * *it2 << " (" << *it1 << ", " << *it2 << ")\n";
            }
        }
    }

    // Part 2
    for (auto it1 = amount.cbegin(); it1 != amount.cend(); it1++) {
        for (auto it2 = std::next(it1); it2 != amount.cend(); it2++) {
            for (auto it3 = std::next(it2); it3 != amount.cend(); it3++) {
                if (*it1 + *it2 + *it3 == 2020) {
                    std::cout << "Part 2 Answer : " << *it1 * *it2 * *it3 << " (" << *it1 << ", " << *it2 << ", " << *it3 << ")\n";
                }
            }
        }
    }

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
