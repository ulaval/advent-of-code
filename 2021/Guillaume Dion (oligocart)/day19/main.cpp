// AoC_2021_19

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iomanip>

using std::size_t, std::cout, std::cerr, std::string, std::vector, std::array;

using coord3d = std::array<int, 3>;
using scanner_report = std::vector<std::vector<coord3d>>;

std::ostream& operator<<(std::ostream& out, const coord3d& c) {
	out << '(' << std::setw(2) << c[0] << ',' << std::setw(2) << c[1] << ',' << std::setw(2) << c[2] << ')';
	return out;
}

std::istream& operator>>(std::istream& in, coord3d& c) {
	char ch;
	in >> c[0];
	if (in.good()) {
		in >> ch >> c[1];
		if (in.good())
			in >> ch >> c[2];
	}
	return in;
}

// #include "matrices.hpp"

auto read_input(std::istream& in) {
	string s;
	int n;
	scanner_report vec;
	while (in >> s >> s >> n >> s) {
		vec.emplace_back();
		coord3d p;
		while (in >> p)
			vec.back().push_back(p);
		in.clear();
	}
	return vec;
}

auto variations_of(const coord3d& p) {
	const auto a = p[0], b = p[1], c = p[2];
	array<coord3d, 24> var = {
			coord3d{ a, b, c}, 	coord3d{ a, c,-b}, 	coord3d{ a,-b,-c}, 	coord3d{ a,-c, b},
			coord3d{-a, b,-c}, 	coord3d{-a, c, b}, 	coord3d{-a,-b, c}, 	coord3d{-a,-c,-b},
			coord3d{ b,-a, c}, 	coord3d{ b, c, a}, 	coord3d{ b, a,-c}, 	coord3d{ b,-c,-a},
			coord3d{-b,-a,-c}, 	coord3d{-b, c,-a}, 	coord3d{-b, a, c}, 	coord3d{-b,-c, a},
			coord3d{ c, b,-a}, 	coord3d{ c,-a,-b}, 	coord3d{ c,-b, a}, 	coord3d{ c, a, b},
			coord3d{-c, b, a}, 	coord3d{-c,-a, b}, 	coord3d{-c,-b,-a}, 	coord3d{-c, a,-b}
	};
	return var;
}

auto convert_relative(const vector<coord3d>& scan, const coord3d& ref) {
	vector<coord3d> relative;
	for (auto p /* byval intended */ : scan) {
		p[0] -= ref[0];
		p[1] -= ref[1];
		p[2] -= ref[2];
		relative.push_back(p);
	}
	return relative;
}

auto compare_scans(coord3d& position, const vector<coord3d>& scan1, const vector<coord3d>& scan2) {
	// compare 2 scans and return position of scanner 2 relative to scanner 1 (if cube overlaps)
	position = coord3d{0, 0, 0};
	vector<coord3d> beacons;
	for (size_t i=0; i<scan1.size(); i++) {
		const auto relative1 = convert_relative(scan1, scan1[i]);
		for (size_t j=0; j<scan2.size(); j++) {
			const auto relative2 = convert_relative(scan2, scan2[j]);
			int var_index = -1, matches = 1;		// matches=1 : car relative1[0] match toujours relative2[0]
			for (const auto& p1 : relative1) {
				const auto p1var = variations_of(p1);
				for (const auto& p2 : relative2) {
					if (p1 == coord3d{0, 0, 0} && p2 == coord3d{0, 0, 0})
						continue;
					// find index of matching variation
					const auto it = std::find(p1var.cbegin(), p1var.cend(), p2);
					if (it != p1var.cend()) {
						if (var_index == -1) var_index = std::distance(p1var.cbegin(), it);
						assert(var_index == std::distance(p1var.cbegin(), it));	// ne devrait jamais varier
						if (++matches >= 12)
							break;
					}
				}
				if (matches >= 12)
					break;
			}
			if (matches >= 12) {
				if (position == coord3d{0, 0, 0}) {
					const auto orientation = variations_of(coord3d{1, 2, 3})[var_index];
					const auto p2var = variations_of(scan2[j])[var_index];
					position = coord3d{ scan1[i][0]-p2var[0], scan1[i][1]-p2var[1], scan1[i][2]-p2var[2] };
					cerr  << "comparable scans! position = " << position << ", orientation # " << var_index << ' ' << orientation << '\n';
				}
				beacons.push_back(scan1[i]);
				cerr << "   " << scan1[i] << " == " << scan2[j] << '\n';
				break;
			}
		}
	}
	if (beacons.empty())
		cerr << "no overlap in scans\n";
	return beacons;
}

int main() {

	const auto input_coords = read_input(std::cin);

    // Part 1
    {
		coord3d pos;
		compare_scans(pos, input_coords[0], input_coords[1]);
		compare_scans(pos, input_coords[1], input_coords[4]);
		// incomplet... :-(
    }

    // Part 2
    {

    }
}
