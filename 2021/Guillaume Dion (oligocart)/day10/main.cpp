// AoC_2021_10

#include <cassert>
#include <iostream>
#include <vector>
#include <iterator>

using std::size_t, std::cout, std::string, std::vector;

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

char closing_of(char opening) {
	switch (opening) {
	case '(': return ')';
	case '[': return ']';
	case '{': return '}';
	case '<': return '>';
	}
	throw std::logic_error("duh?");
}

int char_score(char illegal) {
	switch (illegal) {
	case ')': return 3;
	case ']': return 57;
	case '}': return 1197;
	case '>': return 25137;
	}
	throw std::logic_error("duh?");
}

int char_value(char expected) {
	switch (expected) {
	case ')': return 1;
	case ']': return 2;
	case '}': return 3;
	case '>': return 4;
	}
	throw std::logic_error("duh?");
}

int main() {

    const auto lines = read_input(std::cin);

    // Part 1 & 2
	int score = 0;
	vector<long> p2values;
	for (const auto& s : lines) {
		bool valid = true;
		vector<char> stack;
		for (const auto ch : s) {
			if (is_any_of(ch, ')', ']', '}', '>')) {
				const auto expected = closing_of(stack.back());
				stack.pop_back();
				if (ch != expected) {
					valid = false;
					score += char_score(ch);
					// cout << s << " - expected " << expected << ", but found " << ch << " instead.\n";
					break;
				}
			}
			else stack.push_back(ch);
		}
		if (valid) {
			long value = 0;
			string complete;
			while (!stack.empty()) {
				complete.push_back(closing_of(stack.back()));
				value *= 5;
				value += char_value(closing_of(stack.back()));
				stack.pop_back();
			}
			p2values.push_back(value);
			// cout << s << " - complete by adding " << complete << " - " << value << " total points.\n";
		}
	}
	cout << "Part 1 answer = " << score << '\n';
	std::sort(p2values.begin(), p2values.end());
	const auto middle_score = p2values[p2values.size()/2];
	cout << "Part 2 answer = " << middle_score << '\n';
}
