// AoC_2021_11

#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::string, std::vector;

#include "matrix.hpp"

using coord_t = coord<int>;

constexpr int dim = 10;
int g_flashes = 0;

auto read_input(std::istream& in) {
    string line;
	int y = 0;
	matrix m{dim, dim, 0};
    while (std::getline(in, line)) {
		for (int x = 0; x < dim; x++) {
			m.at({x, y}) = line[x]-'0';
		}
		y++;
	}
	return m;
}

void power_up(matrix<int>& grid, vector<coord_t>& flash_list, const coord_t& c) {
	if (grid.at(c) < 10) {
		grid.at(c)++;
		if (grid.at(c) == 10)
			flash_list.emplace_back(c);
	}
}

void flash(matrix<int>& grid, vector<coord_t>& flash_list) {
	while (!flash_list.empty()) {
		const auto c = flash_list.back();
		flash_list.pop_back();
		g_flashes++;
		for (const auto& a : grid.adjacent(c))
			power_up(grid, flash_list, a);
	}
}

int main() {

    auto grid = read_input(std::cin);

    // Part 1 & 2
	int step = 0;
	while (++step) {
		vector<coord_t> flash_list;
		for (int y=0; y<dim; y++) {
			for (int x=0; x<dim; x++)
				power_up(grid, flash_list, {x,y});
		}
		flash(grid, flash_list);
		std::for_each(grid.data().begin(), grid.data().end(), [](auto& x){ x = (x == 10) ? 0 : x; });
		if (step == 100)
			cout << "Part 1 answer = " << g_flashes << '\n';
		if (std::all_of(grid.data().cbegin(), grid.data().cend(), [](const auto& x){ return x == 0; })) {
			cout << "Part 2 answer = " << step << '\n';
			break;
		}
	}
}
