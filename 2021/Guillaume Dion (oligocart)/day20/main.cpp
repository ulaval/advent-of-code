// AoC_2021_20

#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::string, std::vector;

#include "plane_v.hpp"

using plane_t = plane_v<char>;

auto read_input(std::istream& in) {
    string line, algo;
	std::getline(in, algo);
	std::getline(in, line);
	assert(line.size() == 0);
	vector<string> image;
	while (std::getline(in, line))
		image.push_back(line);
	plane_t pl(200, 200, '.');
	for (int x=0; x<static_cast<int>(image[0].size()); x++) {
		for (int y=0; y<static_cast<int>(image.size()); y++) {
			if (image[y][x] == '#')
				pl.set(x, y) = '#';
		}
	}
	return std::make_pair(pl, algo);
}

void enhance(plane_t& pl, const string& algo) {
	plane_t copy{pl};
	const auto [x0, y0, x1, y1] = copy.window();
	for (int x=x0; x<x1; x++) {
		for (int y=y0; y<y1; y++) {
			int weight = 256, algo_index = 0;
			for (const auto& a : coord{x,y}.adjacent9()) {
				algo_index += (copy(a) == '#') ? weight : 0;
				weight /= 2;
			}
			pl.set(x, y) = algo[algo_index];
		}
	}
}

int main() {

    const auto [plane_orig, algo] = read_input(std::cin);

    // Part 1
    {
		auto plane{plane_orig};
		enhance(plane, algo);
		enhance(plane, algo);
		const auto [x0, y0, x1, y1] = plane.window();
		const auto cnt = std::count_if(plane.data().cbegin(), plane.data().cend()-(x1-x0), [](const auto ch){ return ch == '#'; });
		cout << "Part 1 answer = " << cnt << '\n';
    }

    // Part 2
    {
		auto plane{plane_orig};
		for (int i=0; i<50; i++)
			enhance(plane, algo);
		cout << plane << '\n';
    }
}
