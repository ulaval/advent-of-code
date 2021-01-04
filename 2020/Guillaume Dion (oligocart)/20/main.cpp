// AoC 2020-20

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>
#include <numeric>
#include <cmath>

#include "Tile.h"

bool match_left(std::vector<Tile>::iterator it, int signature, bool can_rotate_or_flip)
{
    if (signature == -1)
        return true;

    auto tile_copy{*it};
    bool found = false;
    for (int s=0; s<8; s++) {
        if (tile_copy.sig[s] == signature) {
            assert(found == false);     // two sides with same signature?
            found = true;
            if (can_rotate_or_flip) {
                // rotate or flip tile to match left
                switch (s) {
                case 0:
                    it->rotate_left();
                    it->flip_h();
                    break;
                case 1:
                    it->rotate_180();
                    it->flip_h();
                    break;
                case 2:
                    it->rotate_right();
                    break;
                case 3:
                    // perfect!
                    break;
                case 4:
                    it->rotate_left();
                    break;
                case 5:
                    it->rotate_180();
                    break;
                case 6:
                    it->rotate_right();
                    it->flip_h();
                    break;
                case 7:
                    it->flip_h();
                    break;
                }
            }
        }
    }
    return it->sig[LEFT] == signature;
}

bool match_top(std::vector<Tile>::iterator it, int signature, bool can_rotate_or_flip)
{
    if (signature == -1)
        return true;

    auto tile_copy{*it};
    bool found = false;
    for (int s=0; s<8; s++) {
        if (it->sig[s] == signature) {
            assert(found == false);     // two sides with same signature?
            found = true;
            if (can_rotate_or_flip) {
                // rotate or flip tile to match left
                switch (s) {
                case 0:
                    // perfect!
                    break;
                case 1:
                    it->rotate_left();
                    break;
                case 2:
                    it->rotate_180();
                    it->flip_v();
                    break;
                case 3:
                    it->rotate_right();
                    it->flip_v();
                    break;
                case 4:
                    it->flip_v();
                    break;
                case 5:
                    it->rotate_left();
                    it->flip_v();
                    break;
                case 6:
                    it->rotate_180();
                    break;
                case 7:
                    it->rotate_right();
                    break;
                }
            }
        }
    }
    return it->sig[TOP] == signature;
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    Tile t;
    std::vector<Tile> tile;
    constexpr std::size_t max_distinct_sides = 1 << Tile::tile_size;
    std::vector<int> occurences(max_distinct_sides, 0);
    while (input_file >> t) {
        tile.push_back(t);
        for (const auto x : t.sig)
            occurences[x]++;
    }
    auto it_max = std::max_element(occurences.cbegin(), occurences.cend());
    std::vector<long> corner;
    for (int i=0; i < tile.size(); i++) {
        std::array<int, 3> occ_count = { 0, 0, 0 };
        for (const auto x : tile[i].sig) {
            occ_count[occurences[x]]++;
        }
        if (occ_count[1] > 2) {
            corner.push_back(tile[i].id);
        }
    }
    const auto corner_product = std::accumulate(corner.cbegin(), corner.cend(), 1ULL, std::multiplies<unsigned long long>());
    std::cout << "Part 1 answer = " << corner_product << "\n\n";
    // assert(corner_product == 7901522557967);

    // Part 2
    const std::size_t puzzle_size = static_cast<std::size_t>(std::sqrt(tile.size()));
    
    // place top left corner
    std::vector<Tile>::iterator top_left;
    for (int i=0; i < 4; i++) {
        top_left = std::find_if(tile.begin(), tile.end(), [i, &corner](const auto& t){ return t.id == corner[i]; });
        if (occurences[top_left->sig[TOP]] == 1 && occurences[top_left->sig[LEFT]] == 1)
            break;
    }
    std::iter_swap(tile.begin(), top_left);
    
    // place rest of tiles (iterate through adjacent_set)...
    auto solved_set = std::set<std::pair<int, int>>{ std::make_pair(0, 0) };
    auto adjacent_set = std::set<std::pair<int, int>>{ std::make_pair(1, 0), std::make_pair(0, 1) };
    auto search_set = generate_tileset(puzzle_size);
    search_set.erase(search_set.find(std::make_pair(0, 0)));
    while (!adjacent_set.empty()) {
        auto dest = adjacent_set.cbegin();
        while (dest != adjacent_set.cend()) {
            auto it_dest = tile.begin() + dest->first * puzzle_size + dest->second;
            // check what left and top signatures should be
            auto left_sig = -1;
            if (solved_set.contains(std::make_pair(dest->first, dest->second-1)))
                left_sig = tile.at(dest->first * puzzle_size + dest->second - 1).sig[RIGHT];
            auto top_sig = -1;
            if (solved_set.contains(std::make_pair(dest->first-1, dest->second)))
                top_sig = tile.at((dest->first-1) * puzzle_size + dest->second).sig[BOTTOM];
            // try to find a unique match for adjacent tile _dest_
            int match_count = 0;
            std::pair<int, int> match{};
            // check every candidate in search set
            for (auto cand = search_set.begin(); cand != search_set.end(); cand++) {
                // check if _cand_ matches _dest_
                auto it_cand = tile.begin() + cand->first * puzzle_size + cand->second;
                if (!match_left(it_cand, left_sig, true))
                    continue;
                if (!match_top(it_cand, top_sig, left_sig == -1))
                    continue;
                // here _cand_ is a match and is rotated/flipped in place
                match = *cand;
                match_count++;
                if (match_count > 1)
                    break;
            }
            if (match_count == 1) {
                // unique match found!
                solved_set.insert(*dest);
                search_set.erase(search_set.find(*dest));
                const auto adj_right = std::make_pair(dest->first, dest->second+1);
                const auto adj_bottom = std::make_pair(dest->first+1, dest->second);
                if (adj_right.second < puzzle_size)
                    adjacent_set.insert(adj_right);
                if (adj_bottom.first < puzzle_size)
                    adjacent_set.insert(adj_bottom);
                adjacent_set.erase(adjacent_set.find(*dest));
                auto it_match = tile.begin() + match.first * puzzle_size + match.second;
                std::iter_swap(it_dest, it_match);
                dest = adjacent_set.cend();
            }
            else {
                assert(false);  // debug this case!
                dest = std::next(dest);
            }
        }
    }

    // scan each image (with all rotations/flips)
    Image puzzle(tile, false);
    std::ofstream ofs("puzzle.txt");
    ofs << puzzle << '\n';
    ofs.close();
    Image image(tile);
    Image scan_result;
    for (int flipped=0; flipped<2; flipped++) {
        for (int deg=0; deg<=270; deg+=90) {
            auto image_copy{image};
            if (image_copy.scan()) {
                scan_result = image_copy;
            }
            std::ostringstream oss;
            if (flipped==0)
                oss << "image" << deg << ".txt";
            else
                oss << "image" << deg << "_flip.txt";
            ofs.open(oss.str());
            ofs << image_copy << '\n';
            ofs.close();
            image.rotate();
        }
        image.flip();
    }

    // Finally, calculate water "roughness"
    const auto roughness = scan_result.count_char('#');
    std::cout << "Part 2 answer = " << roughness << '\n';

    return 0;
}
