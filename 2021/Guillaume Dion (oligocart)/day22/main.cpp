// AoC_2021_22

#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <numeric>

using std::size_t, std::cout, std::cerr, std::string, std::vector, std::list;

#include "cuboid.hpp"

struct step {
	bool on;
	cuboid cube;
};

auto read_input(std::istream& in) {
    string state;
	cuboid cube{};
	vector<step> steps;
	while (in >> state >> cube) {
		assert(state == "on" || state == "off");
		steps.emplace_back(state == "on",  cube);
	}
	return steps;
}

void split_cuboids(list<cuboid>& on_cubes, const vector<step>& steps, bool part2) {
	for (const auto& [on, current_cube] : steps) {
		if (!part2 && (std::abs(current_cube.x.min) > 1000 || std::abs(current_cube.z.max) > 1000))
			break;	// skip big numbers for part 1
		// split all existing "on cubes" intersecting with current cube (discarding intersection)
		for (auto it=on_cubes.begin(); it != on_cubes.end(); it++) {
			if (current_cube.intersects(*it)) {
				const auto subparts = it->split(current_cube);
				auto erase_it = it++;
				on_cubes.erase(erase_it);
				for (const auto& s : subparts) {
					on_cubes.insert(it, s);
				}
				it--;
			}
		}
		if (on) on_cubes.insert(on_cubes.cend(), current_cube);
	}
}

int main() {

    const auto steps = read_input(std::cin);

    // Part 1
    {
		list<cuboid> on_cubes;
		split_cuboids(on_cubes, steps, false);
		const auto on_count = std::accumulate(on_cubes.cbegin(), on_cubes.cend(), 0ul, [](const auto& a, const auto& c){ return a + c.size(); });
		cerr << "Part 1 answer = " << on_count << '\n';
    }

    // Part 2
    {
		list<cuboid> on_cubes;
		split_cuboids(on_cubes, steps, true);
		const auto on_count = std::accumulate(on_cubes.cbegin(), on_cubes.cend(), 0ul, [](const auto& a, const auto& c){ return a + c.size(); });
		cerr << "Part 2 answer = " << on_count << '\n';
    }
}
