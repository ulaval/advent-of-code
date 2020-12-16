// AoC 2020-14

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <map>
#include <numeric>
#include <bitset>
#include <set>

void expand_addr(std::set<unsigned long>& addresses, const std::bitset<36>& data, const std::vector<int>& x_bits)
{
    if (x_bits.empty())
        return;

    std::bitset<36> value{data};
    auto x_bits_copy{x_bits};
    auto bit = x_bits_copy.back();
    x_bits_copy.pop_back();
    value.set(bit, true);
    addresses.insert(value.to_ulong());
    expand_addr(addresses, value, x_bits_copy);
    value.set(bit, false);
    addresses.insert(value.to_ulong());
    expand_addr(addresses, value, x_bits_copy);
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    // Part 1 & 2
    std::string line;
    std::vector<int> x_bits;
    std::bitset<36> and_mask, or_mask, addr_mask;
    std::map<unsigned long, unsigned long> memory1, memory2;
    while (getline(input_file, line)) {
        std::istringstream iss(line);
        std::string op, value, dummy;
        iss >> op >> dummy >> value;
        assert(dummy[0] == '=');
        if (op == "mask") {         // mask = ...
            // Part 1
            std::string or_str{value}, and_str{value};
            std::transform(value.cbegin(), value.cend(), or_str.begin(), [](auto c) { return (c == '1') ? '1' : '0'; });
            std::transform(value.cbegin(), value.cend(), and_str.begin(), [](auto c) { return (c == '0') ? '0' : '1'; });
            or_mask = std::bitset<36>(or_str);
            and_mask = std::bitset<36>(and_str);

            // Part 2
            x_bits.clear();
            int bit = 36;
            std::for_each(value.cbegin(), value.cend(), [bit, &x_bits](auto c) mutable { bit--; if (c == 'X') { x_bits.push_back(bit); } });
            std::transform(value.cbegin(), value.cend(), value.begin(), [](auto c) { return (c == 'X') ? '0' : c; });
            addr_mask = std::bitset<36>(value);
        }
        else {                      // mem[addr] = ...
            // Part 1
            std::istringstream iss2(op.substr(4));
            unsigned long addr;
            iss2 >> addr;
            std::bitset<36> data1(std::stoi(value));
            data1 &= and_mask;
            data1 |= or_mask;
            memory1.insert_or_assign(addr, data1.to_ulong());

            // Part 2
            std::bitset<36> addr_bits(addr);
            addr_bits |= addr_mask;
            std::set<unsigned long> addresses;
            expand_addr(addresses, addr_bits, x_bits);
            for (auto a : addresses) {
                memory2.insert_or_assign(a, std::stoul(value));
            }
        }
    }
    auto sum1 = std::accumulate(memory1.cbegin(), memory1.cend(), 0UL, [](auto a, const auto& p) { return a + p.second; });
    auto sum2 = std::accumulate(memory2.cbegin(), memory2.cend(), 0UL, [](auto a, const auto& p) { return a + p.second; });
    std::cout << "Part 1 answer = " << sum1 << '\n';
    std::cout << "Part 2 answer = " << sum2 << '\n';
}
