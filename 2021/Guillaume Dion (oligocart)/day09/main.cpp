// AoC_2021_09

#include <iostream>
#include <utility>
#include <set>
#include <vector>

using std::size_t, std::cout, std::string, std::vector, std::set, std::pair;

#include "matrix.hpp"

using coord_t = coord<int>;

auto read_input(std::istream& in) {
	string line;
	matrix m{0};
	int y = 0;
	while (std::getline(in, line)) {
		m.set_width(line.size());
		for (int x=0; x<static_cast<int>(line.size()); x++)
			m.at({x, y}) = line[x]-'0';
		y++;
	}
	return m;
}

int basin_area(const matrix<int>& cave, const coord_t& low_p) {
	set<coord_t> explore_set;
	set<coord_t> done_set;
	int area = 0;
	explore_set.insert(low_p);
	while (!explore_set.empty()) {
		const auto p = *explore_set.begin();
		explore_set.erase(explore_set.begin());
		area++;
		done_set.insert(p);
		for (const auto& a : cave.adjacent(p)) {
			if (!done_set.contains(a) && cave.at(a) != 9) {
				explore_set.insert(a);
				done_set.insert(a);
			}
		}
	}
	return area;
}

int main() {

    const auto cave = read_input(std::cin);
	vector<coord_t> low_points;

    // Part 1
    {
		for (int y=0; y<static_cast<int>(cave.dimensions().second); y++) {
			for (int x=0; x<static_cast<int>(cave.dimensions().first); x++) {
				const coord_t c{x, y};
				const auto adj = cave.adjacent(c);
				if (std::all_of(adj.cbegin(), adj.cend(), [&cave, &c](const auto& a){ return cave.at(a) > cave.at(c); }))
					low_points.push_back(c);
			}
		}
		int sum = 0;
		for (const auto& p : low_points)
			sum += 1 + cave.at(p);
		cout << "Part 1 answer = " << sum << '\n';
    }

    // Part 2
    {
		vector<int> area;
		for (const auto& p : low_points)
			area.push_back(basin_area(cave, p));
		std::sort(area.begin(), area.end(), std::greater<>());
		cout << "Part 2 answer = " << area[0] * area[1] * area[2] << '\n';
    }
}
