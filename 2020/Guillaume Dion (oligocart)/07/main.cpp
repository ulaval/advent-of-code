// AoC 2020-07

#include <cassert>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

#include "Bags.h"

std::istream& read_bag_name(std::istream& in, std::string& bag_name)
{
    std::string adjective, color, dummy;
    in >> adjective >> color >> dummy;
    assert(dummy.substr(0,3) == "bag");
    bag_name = adjective + ' ' + color;
    return in;
}

std::istream& read_bag_count(std::istream& in, int& bag_count)
{
    std::string token;
    in >> token;
    assert(token.size() == 1 || token == "no");
    bag_count = 0;
    if (std::isdigit(token[0])) {
        bag_count = std::stoi(token);
    }
    return in;
}

void enum_parents(std::set<std::string>& set, const Bag* node)
{
    for (auto p : node->_parents) {
        set.insert(p->_name);
        enum_parents(set, p);
    }
}

int count_bags(const Bag* node)
{
    int count = 0;
    for (auto [c, n] : node->_childs) {
        count += n + n * count_bags(c);
    }
    return count;
}

int main(int argc, char* argv[])
{
    std::chrono::time_point<std::chrono::high_resolution_clock> t1{ std::chrono::high_resolution_clock::now() };

    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    if (!input_file.is_open()) {
        std::cerr << "cannot open input file\n";
        return -1;
    }
    
    Bags bags;
    std::string line;
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        std::string container, dummy;
        read_bag_name(iss, container);
        bags.add_bag(container);
        iss >> dummy;
        assert(dummy == "contain");
        std::string contents;
        while (getline(iss, contents, ',')) {
            std::istringstream iss2(contents);
            std::string bag_name;
            int n;
            read_bag_count(iss2, n);
            if (n > 0) {
                read_bag_name(iss2, bag_name);
                bags.add_contained_bag(container, n, bag_name);
            }
        }
    }

    // Part 1
    std::set<std::string> distinct_bags;
    enum_parents(distinct_bags, &bags.get_bag("shiny gold"));
    std::cout << "Part1 answer = " << distinct_bags.size() << '\n';

    // Part 2
    int count = count_bags(&bags.get_bag("shiny gold"));
    std::cout << "Part2 answer = " << count << '\n';

    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t1).count();
    std::cout << "Took " << elapsed << " us\n";
}
