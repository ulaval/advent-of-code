// AoC 2020-16

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <set>
#include <numeric>

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    std::vector<std::set<int>> field_values;
    std::string line;
    while (getline(input_file, line)) {
        if (line.empty())
            break;

        line = line.substr(line.find(':')+2);
        std::istringstream iss(line);
        int n1, n2;
        std::set<int> poss_values;
        while (iss >> n1) {
            char ch;
            iss >> ch;
            assert(ch == '-');
            iss >> n2;
            std::string dummy;
            iss >> dummy;
            for (int x=n1; x <= n2; x++)
                poss_values.insert(x);
            
        }
        field_values.push_back(poss_values);
    }

    std::string dummy;
    std::vector<int> my_ticket;
    getline(input_file, dummy);
    getline(input_file, line);
    std::istringstream iss(line);
    while (getline(iss, dummy, ',')) {
        my_ticket.push_back(std::stoi(dummy));
    }
    getline(input_file, dummy);
    getline(input_file, dummy);

    long sum = 0;
    std::vector<std::vector<int>> valid_tickets;
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        std::string num;
        std::vector<int> ticket;
        std::vector<int> valid_for;
        int i = 0;
        while (getline(iss, num, ',')) {
            int value = std::stoi(num);
            ticket.push_back(value);
            valid_for.push_back(0);
            for (const auto& s : field_values) {
                if (s.contains(ticket.back()))
                    valid_for.back()++;
            }
            i++;
        }
        auto it = std::find(valid_for.cbegin(), valid_for.cend(), 0);
        if (it != valid_for.cend()) {
            auto index = std::distance(valid_for.cbegin(), it);
            sum += ticket[index];
        }
        else {
            valid_tickets.push_back(ticket);
        }
    }
    std::cout << "Part 1 answer : " << sum << '\n';

    // Part 2
    std::vector<int> field_numbers(field_values.size(), 0);
    std::generate(field_numbers.begin(), field_numbers.end(), [n = 1]() mutable { return n++; });
    std::vector<std::vector<int>> pos_v(field_values.size(), field_numbers);
    for (int p=1; p <= field_values.size(); p++) {
        for (const auto& t : valid_tickets) {
            int value = t[p-1];
            for (int f=1; f <= field_values.size(); f++) {
                if (!field_values[f-1].contains(value)) {
                    pos_v[p-1].erase(std::remove(pos_v[p-1].begin(), pos_v[p-1].end(), f), pos_v[p-1].end());
                }
            }
        }
    }

    std::vector<int> mapping(field_values.size(), 0);
    while (std::count(mapping.cbegin(), mapping.cend(), 0) != 0) {
        for (int p=1; p <= field_values.size(); p++) {
            if (pos_v[p-1].size() == 1) {
                auto field = pos_v[p-1][0];
                mapping[p-1] = field;
                std::for_each(pos_v.begin(), pos_v.end(), [field](auto& v) { v.erase(std::remove(v.begin(), v.end(), field), v.end()); });
            }
        }
    }

    return 0;
}
