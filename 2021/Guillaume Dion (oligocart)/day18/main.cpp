// AoC_2021_18

#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <iterator>
#include <stack>

using std::size_t, std::cout, std::string, std::vector, std::array, std::string_view, std::stack;

#include "snailfish_num.hpp"
#include "snailfish_str.hpp"

constexpr size_t max_pairs = 5000;

using snailfish_num_t = snailfish_num<max_pairs>;

auto read_input(std::istream& in) {
	std::vector<string> vec;
	std::copy(std::istream_iterator<string>{in}, std::istream_iterator<string>{}, std::back_inserter(vec));
	return vec;
}

template <typename T, typename... Ts>
bool is_any_of(T&& t, Ts&&... ts)
{
	return ((t == ts) || ...);
}

template <size_t N>
void parse_number(snailfish_num<N>& num, const string_view sv) {
	stack<pair_t*> pair_stack;
	stack<char> char_stack;
	assert(num.pairs[0].parent_p == nullptr);
	assert(*sv.cbegin() == '[' && *std::prev(sv.cend()) == ']');
	pair_t* cur_p = &num.pairs[0];
	num.free_p = &num.pairs[1];
	pair_stack.push(cur_p);
	char_stack.push('[');
	auto it = std::next(sv.cbegin());
	while (it != sv.cend()) {
		if (*it == '[') {
			cur_p = num.free_p++;
			cur_p->parent_p = pair_stack.top();
			assert(is_any_of(char_stack.top(), '[', ','));
			if (char_stack.top() == '[')
				cur_p->parent_p->x_sub_p = cur_p;
			else
				cur_p->parent_p->y_sub_p = cur_p;
			pair_stack.push(cur_p);
		}
		else if (std::isdigit(*it)) {
			assert(is_any_of(char_stack.top(), '[', ','));
			if (char_stack.top() == '[')
				cur_p->x_val = *it-'0';
			else
				cur_p->y_val = *it-'0';
		}
		else if (*it == ']') {
			cur_p = cur_p->parent_p;
			pair_stack.pop();
		}
		char_stack.push(*it++);
	}
	assert(cur_p == nullptr && pair_stack.empty());
}

int main() {
	using namespace std::literals;
    const auto numbers = read_input(std::cin);

	// Part 1
	{
		string str{numbers[0]};
		for (size_t i=1; i<numbers.size(); i++) {
			string op{numbers[i]};
			str = sfs::add(str, op);
		}
		snailfish_num_t num;
		parse_number(num, str);
		cout << "Part 1 answer = " << num.root_p->magnitude() << '\n';
	}

    // Part 2
    {
		auto max_mag = 0l;
		for (size_t i=0; i<numbers.size(); i++) {
			for (size_t j=0; j<numbers.size(); j++) {
				if (i != j) {
					snailfish_num_t num;
					parse_number(num, sfs::add(numbers[i], numbers[j]));
					max_mag = std::max(max_mag, num.root_p->magnitude());
				}
			}
		}
		cout << "Part 2 answer : " << max_mag << '\n';
    }
}
