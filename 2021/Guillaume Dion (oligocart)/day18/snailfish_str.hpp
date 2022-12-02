#pragma once

#include <string>

namespace sfs {

using std::size_t, std::string;

size_t inc_number(string& s, size_t from_index, int inc_value, bool left = true) {
	size_t begin_index = from_index, end_index = 0;
	if (left) {
		while (begin_index-- > 0) {
			if (std::isdigit(s[begin_index])) {
				end_index = begin_index+1;
				while (begin_index > 0 && std::isdigit(s[begin_index-1]))
					begin_index--;
				break;
			}
		}
	}
	else {
		while (begin_index++ < s.size()) {
			if (std::isdigit(s[begin_index])) {
				end_index = begin_index+1;
				while (end_index < s.size() && std::isdigit(s[end_index]))
					end_index++;
				break;
			}
		}
	}
	if (end_index > 0) {
		int number = std::stoi(s.substr(begin_index, end_index-begin_index));
		number += inc_value;
		const string new_value{std::to_string(number)};
		s.replace(begin_index, end_index-begin_index, new_value);
		return new_value.size()-(end_index-begin_index);
	}
	return 0ul;
}

bool explode(string& s) {
	// find pair with depth=5
	size_t index = 0, depth = 0;
	while (index < s.size()) {
		if (s[index] == '[') depth++;
		else if (s[index] == ']') depth--;
		if (depth == 5)
			break;
		index++;
	}
	if (index < s.size()) {        // pair found!
		// increment prev number
		const auto left = std::stoi(s.substr(index+1));
		index += inc_number(s, index, left, true);
		assert(s[index] == '[');
		const auto begin_index = index;

		// increment next number
		while (s[index] != ',')
			index++;
		size_t len;
		const auto right = std::stoi(s.substr(index+1), &len);
		inc_number(s, index+len, right, false);

		// find end and explode pair
		while (s[index] != ']')
			index++;
		assert(s[index] == ']');
		const auto end_index = index+1;
		s.replace(begin_index, end_index-begin_index, "0");
		return true;
	}
	return false;
}

bool split(string& s) {
	// find number > 9
	size_t index = 0;
	while (index < s.size()) {
		if (std::isdigit(s[index])) {
			if (std::isdigit(s[index+1])) {
				size_t len;
				int number = std::stoi(s.substr(index), &len);
				int x_val = number/2;
				int y_val = (number % 2 == 0) ? number/2 : number/2 + 1;
				string r{"[" + std::to_string(x_val) + "," + std::to_string(y_val) + "]"};
				s.replace(index, len, r);
				return true;
			}
		}
		index++;
	}
	return false;
}

void reduce(string& s) {
	while (true) {
		if (!explode(s)) {
			if (!split(s))
				break;
		}
	}
}

string add(const string& s1, const string& s2)
{
	string add{"["+s1+","+s2+"]"};
	reduce(add);
	return add;
}

}	// namespace sfs