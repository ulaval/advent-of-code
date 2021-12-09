// AoC_2021_05

#include <iostream>
#include <utility>
#include <vector>

using std::size_t, std::string, std::vector, std::pair;

#include "matrix.hpp"

using coord_t = coord<int>;
constexpr size_t dim = 1000;

auto read_input(std::istream& in) {
	vector<pair<coord_t, coord_t>> vec;
	int x1, y1, x2, y2;
	char ch;
    while (in >> x1 >> ch >> y1 >> ch >> ch >> x2 >> ch >> y2)
		vec.push_back({{x1,y1},{x2,y2}});
	return vec;
}

int main() {
    const auto lines = read_input(std::cin);

	matrix m1{dim, dim, 0};
	matrix m2{dim, dim, 0};
	for (const auto& [c1, c2] : lines) {
		coord_t delta{0,0};
		if (c1.x != c2.x) delta.x = (c1.x < c2.x) ? 1 : -1;
		if (c1.y != c2.y) delta.y = (c1.y < c2.y) ? 1 : -1;
		for (coord_t c = c1; c != (c2 + delta); c += delta) {
			if (delta.x == 0 || delta.y == 0)
				m1.at(c)++;
			m2.at(c)++;
		}
	}
	const auto ans1 = std::count_if(m1.data().cbegin(), m1.data().cend(), [](auto x){ return x > 1; });
	const auto ans2 = std::count_if(m2.data().cbegin(), m2.data().cend(), [](auto x){ return x > 1; });
	std::cout << "Part 1 answer = " << ans1 << '\n';
	std::cout << "Part 2 answer = " << ans2 << '\n';
}
