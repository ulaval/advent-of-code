// AoC 2020-13
// Pour le fun... version constexpr de la partie 2 (100% compile-time calculations)

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>
#include <chrono>

const int bus_count=9;
using arr_t = std::array<int, bus_count>;
using arr_cit = arr_t::const_iterator;

// euclid's gcd simplifié avec std::exchange()
constexpr long long gcd(long long a, long long b)
{
    while (b != 0) {
        auto t = b;
        b = a % b;
        a = t;
        // a = std::exchange(b, a % b);     std::exchange() n'est pas constexpr :-(
    }
    return a;
}

// plus petit commun multiple
constexpr long long lcm(long long a, long long b)
{
    return a * b / gcd(a, b);
}

// retourne une paire (t, lcm) où t est la valeur cherchée et lcm le plus petit commun multiple des éléments de [begin,end)
constexpr std::pair<long long, long long> find_t(arr_cit ind_begin, arr_cit ind_end, arr_cit ids_begin, arr_cit ids_end)
{
    if (std::next(ind_begin) == ind_end)
        return std::make_pair(0, *ids_begin);

    const auto cur_ind = std::prev(ind_end);
    const auto cur_ids = std::prev(ids_end);
    const auto [t0, lcm0] = find_t(ind_begin, cur_ind, ids_begin, cur_ids);
    for (int i=0; i<*cur_ids; i++) {
        auto t = lcm0 * i + t0;
        if ((t + *cur_ind) % *cur_ids == 0)
            return std::make_pair(t, lcm(lcm0, *cur_ids));
    }
    throw "not found!";
}

/* uncomment to build this version (and comment the other main)
int main(int argc, char* argv[])
{
    // Part 2
    // on doit séperer les indices des numéros de bus car std::map n'a pas de constructeur constexpr
    constexpr arr_t indices = { 0, 35, 41, 49, 54, 58, 60, 72, 101 };
    constexpr arr_t bus_ids = { 41, 37, 431, 23, 13, 17, 19, 863, 29 };
    constexpr auto result = find_t(indices.cbegin(), indices.cend(), bus_ids.cbegin(), bus_ids.cend());
    std::cout << "Part 2 answer = " << result.first << '\n';
}
*/