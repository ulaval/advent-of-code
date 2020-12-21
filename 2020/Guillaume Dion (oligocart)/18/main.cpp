// AoC 2020-18

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>

#include "Operand.h"

std::size_t find_startpos(const std::string& expr, std::string::const_iterator from)
{
    auto level = 0;
    auto rit = std::next(std::make_reverse_iterator(from));
    bool got_digit = false;
    while (rit != expr.crend() && (level != 0 || !got_digit)) {
        if (*rit == ')')
            level++;
        if (*rit == '(')
            level--;
        if (std::isdigit(*rit))
            got_digit = true;
        rit = std::next(rit);
    }
    return expr.size() - std::distance(expr.rbegin(), rit);
}

std::size_t find_endpos(const std::string& expr, std::string::const_iterator from)
{
    auto level = 0;
    auto it = std::next(from);
    bool got_digit = false;
    while (it != expr.cend() && (level != 0 || !got_digit)) {
        if (*it == '(')
            level++;
        if (*it == ')')
            level--;
        if (std::isdigit(*it))
            got_digit = true;
        it = std::next(it);
    }
    return std::distance(expr.begin(), it);
}

std::string add_paren(const std::string& expr, std::size_t offset = 0)
{
    std::string copy{expr};
    auto it = std::find(copy.begin()+offset, copy.end(), '+');
    if (it == copy.end())
        return copy;

    auto next_offset = std::distance(copy.begin(), it) + 2;
    auto startpos = find_startpos(copy, it);
    auto endpos = find_endpos(copy, it);
    copy.insert(startpos, 1, '(');
    copy.insert(endpos+1, 1, ')');
    return add_paren(copy, next_offset);
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1
    auto total1 = 0ULL;
    std::string line;
    while (getline(input_file, line)) {
        Operand expr{line};
        total1 += expr.solve();
    }
    std::cout << "Part 1 answer = " << total1 << '\n';

    // Part 2
    input_file.clear();
    input_file.seekg(0);
    auto total2 = 0ULL;
    while (getline(input_file, line)) {
        line = add_paren(line);
        Operand expr{line};
        total2 += expr.solve();
    }
    std::cout << "Part 2 answer = " << total2 << '\n';
}
