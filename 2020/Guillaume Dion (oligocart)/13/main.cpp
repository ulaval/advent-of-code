// AoC 2020-13

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>

// euclid's gcd simplifié avec std::exchange()
long long gcd(long long a, long long b)
{
    while (b != 0) {
        a = std::exchange(b, a % b);
    }
    return a;
}

// plus petit commun multiple
long long lcm(long long a, long long b)
{
    return a * b / gcd(a, b);
}

// retourne une paire (t, lcm) où t est la valeur cherchée et lcm le plus petit commun multiple des éléments de [begin,end)
std::pair<long long, long long> find_t(std::map<int, int>::const_iterator begin, std::map<int, int>::const_iterator end)
{
    if (std::next(begin) == end)
        return std::make_pair(0, begin->second);

    const auto current = std::prev(end);
    const auto [t0, lcm0] = find_t(begin, current);
    for (int i=0; i<current->second; i++) {
        auto t = lcm0 * i + t0;
        if ((t + current->first) % current->second == 0)
            return std::make_pair(t, lcm(lcm0, current->second));
    }
    throw "that's weird!";
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1 : fait à la calculatrice :-)

    // Part 2
    std::map<int, int> buses;   // key = index in sequence, value = bus id (x's are not stored)
    std::string token;
    input_file >> token;    // discard first line
    int index = 0;
    while (getline(input_file, token, ',')) {
        if (token[0] != 'x')
            buses.insert({ index, std::stoi(token) });
        index++;
    }
    const auto result = find_t(buses.cbegin(), buses.cend());
    std::cout << "Part 2 answer = " << result.first << '\n';
}
