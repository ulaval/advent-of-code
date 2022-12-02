// AoC_2021_15

#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

using std::size_t, std::cout, std::string, std::vector;

#include "matrix_v.hpp"

using matrix_t = matrix_v<int>;
using coord_t = matrix_t::coord_type;

auto read_input(std::istream& in) {
	matrix_t m{0};
    string line;
	int y = 0;
    while (std::getline(in, line)) {
        const auto w = static_cast<int>(line.size());
		m.set_width(w);
		std::istringstream iss{line};
		char ch;
		for (int x=0; x<w; x++) {
			iss >> ch;
			m.at({x, y}) = ch-'0';
		}
		y++;
    }
	return m;
}

// retourne le cout minimal d'une cellule basé sur le coût des cellules adjacentes
int min_cost(const coord_t& c, const matrix_t& cost, const matrix_t& cave) {
	int min_adj_cost = 99999999;
	for (const auto& a : cost.adjacent(c)) {
		if (cost.at(a) != 0 && cost.at(a) < min_adj_cost)
			min_adj_cost = cost.at(a);
	}
	return min_adj_cost + cave.at(c);
}

int compute_cost_matrix(matrix_t& cost, const matrix_t& cave) {
	const auto side = static_cast<int>(cave.width());
	const coord_t start{0, 0};
	const coord_t exit{side-1, side-1};

	// déterminer le carré final
	cost.at(exit) = cave.at(exit);
	cost.at(exit.up()) = cave.at(exit.up()) + cave.at(exit);
	cost.at(exit.left()) = cave.at(exit.left()) + cave.at(exit);
	cost.at(exit.up().left()) = min_cost(exit.up().left(), cost, cave);

	// déterminer les côtés des carrés imbriqués (i,i) jusqu'à atteindre start (0,0)
	for (int i=side-3, l=3; i>=0; i--, l++) {
		// déterminer les côtés du carré débutant à (i,i)
		// l := la longueur du côté du carré
		const coord_t square{i, i};
		// déterminer le côté supérieur
		const coord_t top_right{i+l-1, i};
		cost.at(top_right) = min_cost(top_right, cost, cave);
		for (auto c = top_right.left(); c != square; c = c.left()) {
			cost.at(c) = min_cost(c, cost, cave);
			// rebalancer récursivement les coûts vers la droite
			auto c_right = c.right();
			while (c_right.x < side && min_cost(c_right, cost, cave) < cost.at(c_right)) {
				cost.at(c_right) = min_cost(c_right, cost, cave);
				c_right = c_right.right();
			}
		}
		// déterminer le côté gauche
		const coord_t bottom_left{i, i+l-1};
		cost.at(bottom_left) = min_cost(bottom_left, cost, cave);
		for (auto c = bottom_left.up(); c != square; c = c.up()) {
			cost.at(c) = min_cost(c, cost, cave);
			// rebalancer récursivement les coûts vers le bas
			auto c_down = c.down();
			while (c_down.y < side && min_cost(c_down, cost, cave) < cost.at(c_down)) {
				cost.at(c_down) = min_cost(c_down, cost, cave);
				c_down = c_down.down();
			}
		}
		// déterminer le pignon (square)
		if (i != 0) {
			cost.at(square) = min_cost(square, cost, cave);
			// rebalancer récursivement les coûts vers la droite
			auto c_right = square.right();
			while (c_right.x < side && min_cost(c_right, cost, cave) < cost.at(c_right)) {
				cost.at(c_right) = min_cost(c_right, cost, cave);
				c_right = c_right.right();
			}
			// rebalancer récursivement les coûts vers le bas
			auto c_down = square.down();
			while (c_down.y < side && min_cost(c_down, cost, cave) < cost.at(c_down)) {
				cost.at(c_down) = min_cost(c_down, cost, cave);
				c_down = c_down.down();
			}
		}
	}
	return std::min(cost.at(start.right()), cost.at(start.down()));
}

void copy_cave(matrix_t& full, const matrix_t& cave, const coord_t& origin, int diff) {
	const auto size = static_cast<int>(cave.width());
	for (int y=0; y<size; y++) {
		for (int x=0; x<size; x++)
			full.at(origin+coord_t{x,y}) = ((cave.at({x,y})+diff-1) % 9) + 1;
	}
}

void tile_cave(matrix_t& full, const matrix_t& cave) {
	const auto size = static_cast<int>(cave.width());
	for (int y=0; y<5; y++) {
		for (int x=0; x<5; x++) {
			copy_cave(full, cave, {x*size, y*size}, x+y);
		}
	}
}

int main() {

    const auto cave = read_input(std::cin);
	assert(cave.width() == cave.height());

    // Part 1
    {
		matrix_t cost{cave.width(), cave.height(), 0};
		const auto risk = compute_cost_matrix(cost, cave);
		cout << "Part 1 answer = " << risk << '\n';
    }

    // Part 2
    {
		matrix_t full_cave{5*cave.width(), 5*cave.height(), 0};
		tile_cave(full_cave, cave);
		matrix_t cost{full_cave.width(), full_cave.height(), 0};
		const auto risk = compute_cost_matrix(cost, full_cave);
		cout << "Part 2 answer = " << risk << '\n';
    }
}
