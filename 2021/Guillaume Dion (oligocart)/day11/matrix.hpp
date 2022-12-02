// A simple matrix based on <vector>

#pragma once

#include <array>
#include <vector>

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr bool in_rect(T _x, T _y, size_t _w, size_t _h) const { return x >= _x && x < static_cast<T>(_x+_w) && y >= _y && y < static_cast<T>(_y+_h); }
	std::array<coord, 8> adjacent() const { return { coord{x-1, y-1}, coord{x, y-1}, coord{x+1, y-1}, coord{x-1, y},
													 coord{x+1, y}, coord{x-1, y+1}, coord{x, y+1}, coord{x+1, y+1}}; }
};

template <typename T>
class matrix
{
public:
	using coord_type = coord<int>;

	matrix(size_t width, size_t height, T default_value) : origin{0,0}, w{width}, h{height}, vec(w*h, default_value), defval{default_value} { }
	T& at(const coord_type& c) { return vec.at((c.y-origin.y) * w + c.x - origin.x); }
	[[nodiscard]] const T& at(const coord_type& c) const { return vec.at((c.y-origin.y) * w + c.x - origin.x); }
	const std::vector<T>& data() const { return vec; }
	std::vector<T>& data() { return vec; }
	decltype(auto) adjacent(const coord_type& from) const;

private:
	coord_type origin;
	size_t w, h;
	std::vector<T> vec;
	T defval;
};

template<typename T>
decltype(auto) matrix<T>::adjacent(const matrix::coord_type& from) const
{
	std::vector<coord_type> adj;
	for (const auto& a : from.adjacent()) {
		if (a.in_rect(origin.x, origin.y, w, h))
			adj.push_back(a);
	}
	return adj;
}
