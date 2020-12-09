// AoC 2020-06

#include <chrono>
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <bitset>

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    std::string line;
    std::set<char> yes;
    std::vector<std::bitset<26>> p2(1);
    auto p1_answer = 0, p2_answer = 0;
    while (getline(input_file, line)) {
        char ch;
        std::istringstream iss(line);
        bool continued = false;
        while (iss >> ch) {
            continued = true;
            yes.insert(ch);
            p2.back().set(ch - 'a');
        }
        if (!continued) {
            p1_answer += yes.size();
            yes.clear();
            auto& sum = p2[0];
            for (auto it = std::next(p2.cbegin()); it != std::prev(p2.cend()); it++)
                sum &= *it;
            p2_answer += sum.count();
            p2.clear();
        }
        p2.push_back(std::bitset<26>());
    }
    p1_answer += yes.size();
    auto& sum = p2[0];
    for (auto it = std::next(p2.cbegin()); it != std::prev(p2.cend()); it++)
        sum &= *it;
    p2_answer += sum.count();
    std::cout << "Part1 answer : " << p1_answer << '\n';
    std::cout << "Part2 answer : " << p2_answer << '\n';

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
