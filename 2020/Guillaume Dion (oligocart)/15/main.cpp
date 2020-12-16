// AoC 2020-15

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <chrono>

int main(int argc, char* argv[])
{
    std::vector<int> spoken = { 16,12,1,0,15,7,11 };

    // Part 1
    while (spoken.size() < 2020) {
        auto rit = spoken.crbegin();
        auto prit = std::find(std::next(spoken.crbegin()), spoken.crend(), *rit);
        spoken.push_back((prit == spoken.crend()) ? 0 : std::distance(rit, prit));
    }
    std::cout << "Part 1 answer = " << *spoken.crbegin() << '\n';

    // Part 2
    std::vector<int> first(30'000'000, 0);
    std::vector<int> second(30'000'000, 0);
    second[16] = 1;
    second[12] = 2;
    second[1] = 3;
    second[0] = 4;
    second[15] = 5;
    second[7] = 6;
    second[11] = 7;
    auto mrsn = 11;
    for (int t=8; t <= 30'000'000; t++) {
        mrsn = (first[mrsn] == 0) ? 0 : second[mrsn] - first[mrsn];
        auto& f = first[mrsn];
        auto& s = second[mrsn];
        f = std::exchange(s, t);
    }
    std::cout << "Part 2 answer = " << mrsn << '\n';
}
