// AoC 2020-09

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());
    
    std::vector<unsigned long> numbers;
    std::copy(std::istream_iterator<int>{input_file}, std::istream_iterator<int>{}, std::back_inserter(numbers));

    // Part 1
    constexpr int p_length = 25;     // preamble length
    auto p_end = numbers.cbegin() + p_length;   // preamble start and end
    for (auto p_start = numbers.cbegin(); p_end != numbers.cend(); p_start = std::next(p_start), p_end = std::next(p_end)) {
        bool found = false;
        for (auto p_n1 = p_start; p_n1 != std::prev(p_end); p_n1++) {
            if (std::find_if(std::next(p_n1), p_end, [&](auto x){ return (*p_n1 + x == *p_end) && (*p_n1 != x); }) != p_end) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Part 1 answer = " << *p_end << '\n';
            break;
        }
    }
    

    // Part 2
    for (auto it1 = numbers.cbegin(); it1 != p_end; it1++) {
        auto it2 = std::next(it1);
        unsigned long sum = *it1 + *it2;
        while (sum < *p_end) {
            it2 = std::next(it2);
            sum += *it2;
        }
        if (sum == *p_end) {
            auto minmax = std::minmax_element(it1, it2);
            std::cout << "Part 2 answer = " << *minmax.first + *minmax.second << '\n';
        }
    }
}
