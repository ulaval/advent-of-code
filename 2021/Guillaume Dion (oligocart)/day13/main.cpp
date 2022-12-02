// AoC_2021_13

#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::string, std::vector;

#include "matrix_v.hpp"

using matrix_t = matrix_v<char>;

auto read_input(std::istream& in) {
	int x, y;
	char ch;
	vector<int> vx;
	vector<int> vy;
    while (in >> x >> ch >> y) {
		assert(ch == ',');
		vx.push_back(x);
		vy.push_back(y);
    }
	const size_t w = 1 + *std::max_element(vx.cbegin(), vx.cend());
	const size_t h = 1 + *std::max_element(vy.cbegin(), vy.cend());

	matrix_t m{w, h, '.'};
	for (size_t i=0; i<vx.size(); i++)
		m.at({vx[i], vy[i]}) = '#';

	return m;
}

matrix_t fold_x(const matrix_t& page, int fold) {
	matrix_t m{fold, page.height(), '.'};
	// copy (0..fold-1, 0..h-1)
	for (int y=0; y<page.height(); y++) {
		for (int x=0; x<fold; x++)
			m.at({x,y}) = page.at({x,y});
	}
	// copy '#' (w-1..fold+1, 0..h-1) to (0..fold-1, 0..h-1)
	for (int y=0; y<page.height(); y++) {
		for (int x0=0, x1=page.width()-1; x0<fold; x0++, x1--) {
			if (page.at({x1,y}) == '#')
				m.at({x0,y}) = page.at({x1,y});
		}
	}
	return m;
}

matrix_t fold_y(const matrix_t& page, int fold) {
	matrix_t m{page.width(), fold, '.'};
	// copy (0..w-1, 0..fold-1)
	for (int y=0; y<fold; y++) {
		for (int x=0; x<page.width(); x++)
			m.at({x,y}) = page.at({x,y});
	}
	// copy '#' (0..w-1, h-1..fold+1) to (0..w-1, 0..fold-1)
	for (int y0=0, y1=page.height()-1; y0<fold; y0++, y1--) {
		for (int x=0; x<page.width(); x++) {
			if (page.at({x,y1}) == '#')
				m.at({x,y0}) = page.at({x,y1});
		}
	}
	return m;
}

int main() {
    auto page = read_input(std::cin);

    // Part 1
    {
		// fold along x=655
		page = fold_x(page, 655);
		const auto cnt = std::count_if(page.data().cbegin(), page.data().cend(), [](const auto c){ return c == '#'; });
		cout << "Part 1 answer = " << cnt << '\n';
    }

    // Part 2
    {
		page = fold_y(page, 447);
		page = fold_x(page, 327);
		page = fold_y(page, 223);
		page = fold_x(page, 163);
		page = fold_y(page, 111);
		page = fold_x(page, 81);
		page = fold_y(page, 55);
		page = fold_x(page, 40);
		page = fold_y(page, 27);
		page = fold_y(page, 13);
		page = fold_y(page, 6);
		cout << "Part 2 answer :\n";
		cout << page << '\n';
    }
}
