// AoC_2021_25

#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::cerr, std::string, std::vector;

#include "matrix_v.hpp"

auto read_input(std::istream& in) {
    string line;
	int y = 0;
	matrix_v<char> m{'.'};
	while (std::getline(in, line)) {
		m.set_width(line.size());
		for (int x=0; x<static_cast<int>(line.size()); x++)
			m.at({x, y}) = line[x];
		y++;
	}
	return m;
}

coord<int> target_pos(const coord<int>& current_pos, const matrix_v<char>& map) {
	assert(map.at(current_pos) == '>' || map.at(current_pos) == 'v');
	auto target{current_pos};
	if (map.at(current_pos) == '>') {
		target += coord<int>{1, 0};
		if (target.x == static_cast<int>(map.width()))
			target.x = 0;
	}
	else {	// 'v'
		target += coord<int>{0, 1};
		if (target.y == static_cast<int>(map.height()))
			target.y = 0;
	}
	return target;
}

void move(matrix_v<char>& seafloor, bool east) {
	char type = east ? '>' : 'v';
	matrix_v<char> copy{seafloor};
	for (int x=0; x<static_cast<int>(copy.width()); x++) {
		for (int y=0; y<static_cast<int>(copy.height()); y++) {
			if (copy.at({x,y}) == type) {
				auto target = target_pos({x,y}, seafloor);
				if (copy.at(target) == '.') {
					seafloor.at({x,y}) = '.';
					seafloor.at(target) = type;
				}
			}
		}
	}
}

int main() {

    auto seafloor = read_input(std::cin);

    // Part 1
    {
		int s = 0;
		while(++s) {
			auto copy{seafloor};
			move(seafloor, true);
			move(seafloor, false);
			if (seafloor == copy)
				break;
		}
		cout << "Part 1 answer = " << s << '\n';
    }

    // Part 2
    {

    }
}
