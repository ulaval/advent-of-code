// AoC 2020-21

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>

void reduce_map(std::map<std::string, std::set<std::string>>& allergen_map, std::map<std::string, std::string>& matches)
{
    // find allergens with only one ingredient
    int new_matches = 0;
    for (const auto& [a, s] : allergen_map) {
        if (s.size() == 1) {
            auto [it, res] = matches.insert({ *s.begin(), a });
            new_matches += (res) ? 1 : 0;
        }
    }
    if (new_matches > 0) {
        for (const auto& [ingr, allerg] : matches) {
            for (auto& [a, s] : allergen_map) {
                if (s.contains(ingr)) {
                    s.erase(s.find(ingr));
                }
            }
        }
        reduce_map(allergen_map, matches);
    }
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // parse input
    std::string line;
    std::map<std::string, int> ingr_counts{};
    std::vector<std::pair<std::set<std::string>, std::set<std::string>>> foods{};
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        std::string token;
        std::set<std::string> ingredients{};
        std::set<std::string> allergens{};
        bool ingredient_list = true;
        while (iss >> token) {
            if (token == "(contains") {
                ingredient_list = false;
                continue;
            }
            if (ingredient_list) {
                ingredients.insert(token);
                if (!ingr_counts.contains(token))
                    ingr_counts.insert({ token, 0 });
                ingr_counts[token]++;
            }
            else {
                if (token.ends_with(',') || token.ends_with(')'))
                    token = token.substr(0, token.size()-1);
                allergens.insert(token);
            }
        }
        foods.push_back(std::make_pair(ingredients, allergens));
    }

    // Part 1
    std::map<std::string, std::set<std::string>> allergen_map{};
    for (const auto& [ingr, allerg] : foods) {
        for (const auto& a : allerg) {
            if (!allergen_map.contains(a)) {
                allergen_map.insert({ a, ingr });
            }
            const auto& cur_i = allergen_map[a];
            std::set<std::string> isec;
            std::set_intersection(cur_i.cbegin(), cur_i.cend(), ingr.cbegin(), ingr.cend(), std::inserter(isec, isec.begin()));
            allergen_map[a] = isec;
        }
    }
    std::map<std::string, std::string> matches{};
    reduce_map(allergen_map, matches);
    int safe_occurrences = 0;
    std::set<std::string> safe_ingredients{};
    for (const auto& [ingr, cnt] : ingr_counts) {
        if (!matches.contains(ingr)) {
            safe_ingredients.insert(ingr);
            safe_occurrences += cnt;
        }
    }
    std::cout << "Part 1 answer = " << safe_occurrences << '\n';

    // Part 2
    std::vector<std::pair<std::string, std::string>> canonical;
    std::copy(matches.cbegin(), matches.cend(), std::back_inserter(canonical));
    auto map_val_cmp = [](const std::pair<std::string,std::string>& a, const std::pair<std::string,std::string>& b) { return a.second < b.second || (a.second == b.second && a.first < b.first); };
    std::sort(canonical.begin(), canonical.end(), map_val_cmp);
    std::ostringstream oss;
    for (const auto& [i, a] : canonical) {
        oss << i << ',';
    }
    std::cout << "Part 2 answer = " << oss.str() << '\n';

    return 0;
}
