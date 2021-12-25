// AoC_2021_17

#include <iostream>
#include <vector>
#include <set>
#include <limits>

using std::size_t, std::cout, std::string, std::vector, std::set;

#include "coord.hpp"

using coord_t = coord<int>;

bool probe_in_target(coord_t v, int x_min, int y_min, int x_max, int y_max) {
	coord_t p{0,0};
	while (p.x <= x_max && p.y >= y_min) {
		p += v;
		if (p.in_rect(x_min, y_min, x_max-x_min+1, y_max-y_min+1))
			return true;
		v = {std::max(v.x-1, 0), v.y-1};
	}
	return false;
}

int max_height(coord_t v) {
	int h_max = std::numeric_limits<int>::min();
	coord_t p{0,0};
	while (p.y > h_max) {
		h_max = p.y;
		p += v;
		v = {std::max(v.x-1, 0), v.y-1};
	}
	return h_max;
}

int main() {
	constexpr int x_min = 206, x_max = 250;
	constexpr int y_min = -105, y_max = -57;

	// Part 1 : trouver Py_max (hauteur maximale d'un point)
	// dépend de Vx_min : la vélocité X minimale pour atteindre la cible
	int n = 1;
	while (((n+1) * n/2) < x_min) n++;	// Somme(i) pour i = 1..n := n/2 * (n+1)
	const auto vx_min = n;
	const auto vy_max = -y_min-1;		// Vy_max est simplement -y_min-1
	cout << "Part 1 answer = " << max_height({vx_min, vy_max})	<< '\n';

	// Part 2 : trouver toutes les vélocités produisant des points dans la cible
	const auto vx_max = x_max;
	const auto vy_min = y_min;
	// les vélocité candidates sont { (vx_min..vx_max, vy_min..vy_max) }
	set<coord_t> vs;
	for (int vx=vx_min; vx<=vx_max; vx++) {
		for (int vy=vy_min; vy<=vy_max; vy++) {
			if (probe_in_target({vx, vy}, x_min, y_min, x_max, y_max))
				vs.emplace(vx, vy);
		}
	}
	cout << "Part 2 answer = " << vs.size() << '\n';
}
