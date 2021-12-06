// AoC_2021_02

#include <iostream>
#include <vector>

using std::size_t, std::cout, std::string, std::vector;

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr coord& operator+=(const coord& rhs) { x += rhs.x; y += rhs.y; return *this; }
};
using coord_t = coord<int>;

vector<coord_t> read_input(std::istream& in) {
	vector<coord_t> vec;
	string s;
	int n;
    while (in >> s >> n) {
		if (s == "forward")
			vec.emplace_back(n, 0);
		else if (s == "down")
			vec.emplace_back(0, n);
		else if (s == "up")
			vec.emplace_back(0, -n);
    }
	return vec;
}

int main() {

    const auto vec = read_input(std::cin);

    // Part 1
    {
		auto pos = coord_t{0,0};
		for (const auto& c : vec)
			pos += c;
		cout << "Part 1 answer = " << pos.x * pos.y << '\n';
    }

    // Part 2
    {
		int aim = 0;
		auto pos = coord_t{0,0};
		for (const auto& c : vec) {
			aim += c.y;
			pos.x += c.x;
			pos.y += aim * c.x;
		}
		cout << "Part 2 answer = " << pos.x * pos.y << '\n';
    }
}
