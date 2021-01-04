// AoC 2020-24

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <set>

#include "HexTile.h"

void remove_whites(std::set<HexTile>& floor)
{
    auto it = std::find_if(floor.begin(), floor.end(), [](const auto& t) { return !t.is_black(); });
    while (it != floor.end()) {
        auto next_it = std::next(it);
        floor.erase(it);
        it = std::find_if(next_it, floor.end(), [](const auto& t) { return !t.is_black(); });
    }
}

void update_floor(std::set<HexTile>& floor)
{
    auto floor_copy{floor};
    std::set<HexTile> adj_whites;

    // check all black tiles
    for (const auto& t : floor_copy) {
        int adj_black_count = 0;
        for (const auto& a : t.adjacent()) {
            if (floor_copy.contains(a))
                adj_black_count++;
            else
                adj_whites.insert(a);
        }
        if (adj_black_count == 0 || adj_black_count > 2) {
            auto it = floor.find(t);
            floor.erase(it);
        }
    }

    // check all adjacent white tiles
    for (const auto& t : adj_whites) {
        int adj_black_count = 0;
        for (const auto& a : t.adjacent()) {
            if (floor_copy.contains(a))
                adj_black_count++;
        }
        if (adj_black_count == 2) {
            floor.insert(t);
        }
    }
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    std::set<HexTile> floor;
    std::string line;
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        HexTile tile;
        Cardinal card;
        while (iss >> card) {
            tile += card;
        }
        auto it = floor.find(tile);
        if (it != floor.cend())
            const_cast<HexTile&>(*it).flip();   // flip() does not modify ordering
        else
            floor.insert(tile);
    }
    remove_whites(floor);
    std::cout << "Part 1 answer = " << floor.size() << std::endl;

    // Part 2
    for (int day=1; day <= 100; day++) {
        update_floor(floor);
        std::cout << "Day " << day << ": " << floor.size() << '\n';
    }
    std::cout << "Part 2 answer = " << floor.size() << std::endl;
}
