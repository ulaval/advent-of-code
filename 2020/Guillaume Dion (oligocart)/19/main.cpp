// AoC 2020-19

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <regex>

using rules_t = std::array<std::string, 200>;

std::string substitute(const rules_t& rule, int id = 0)
{
    if (rule.at(id).size() == 1 && rule.at(id)[0] >= 'a' && rule.at(id)[0] <= 'z')
        return rule[id];

    char ch;
    std::istringstream iss(rule[id]);
    std::ostringstream oss;
    std::string token;
    while (iss >> token) {
        if (std::isdigit(token[0])) {
            oss << substitute(rule, std::stoi(token));
        }
        else {
            oss << token;
        }
    }
    return oss.str();
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    rules_t rule;
    std::string line;
    int rule_count = 0;
    while (getline(input_file, line)) {
        if (line.empty())
            break;
        std::istringstream iss(line);
        int id;
        iss >> id;
        char ch;
        iss >> ch;
        assert(ch == ':');
        iss >> std::ws;
        ch = iss.peek();
        if (ch == '"') {
            iss >> ch;
            iss >> ch;
            rule[id] = ch;
            iss >> ch;
        }
        else {
            getline(iss, line);
            if (line.find('|') != std::string::npos)
                line = "( " + line + " )";
            rule[id] = line;
        }
        rule_count++;
    }

    std::vector<std::string> strings;
    while (getline(input_file, line)) {
        strings.push_back(line);
    }

    const auto text0 = '^' + substitute(rule) + '$';
    const auto regex0 = std::regex(text0);
    auto count = 0;
    for (const auto& s : strings) {
        if (std::regex_search(s, regex0))
            count++;
    }
    std::cout << "Part 1 answer = " << count << '\n';

    // Part 2
    const auto text42 = substitute(rule, 42);
    const auto text31 = substitute(rule, 31);
    const auto regex42 = std::regex(text42);
    const auto regex31 = std::regex(text31);
    auto ncount = 0;
    for (const auto& s : strings) {
        auto matched42 = 0, matched31 = 0;
        for (auto pos=0; pos < s.size(); pos += 8) {
            const auto sub_s = s.substr(pos, 8);
            if (pos == 0 && !regex_search(sub_s, regex42))
                break;
            if (pos == 0) {
                matched42++;
            }
            else if (regex_search(sub_s, regex42)) {
                if (matched31 != 0) {
                    matched31 = 0;
                    break;
                }
                matched42++;
            }
            else if (regex_search(sub_s, regex31)) {
                matched31++;
            }
        }
        if (matched42 < 2 || matched31 < 1 || matched31 >= matched42)
            ncount++;
    }
    std::cout << "Part 2 answer = " << strings.size() - ncount << '\n';
}
