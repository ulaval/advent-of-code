// A simple matrix type based on vector

#pragma once

#include <cassert>
#include <vector>

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr bool operator!=(const coord& rhs) const { return x != rhs.x || y != rhs.y; }
	constexpr coord& operator+=(const coord& rhs) { x += rhs.x; y += rhs.y; return *this; }
	constexpr coord operator+(const coord& rhs) const { coord x{*this}; x += rhs; return x; }
};

template <typename T>
class matrix
{
public:
	using index_type = int;
	using coord_type = coord<index_type>;
	matrix(size_t width, size_t height, T default_value) : origin{0,0}, w{width}, h{height}, vec(w*h, default_value), defval{default_value} { }
	T& at(const coord_type& c);
	const std::vector<T>& data() const { return vec; }

private:
	coord_type origin;
	size_t w, h;
	std::vector<T> vec;
	T defval;
};


template <typename T>
T& matrix<T>::at(const coord_type& c)
{
	assert(c.x >= origin.x && c.x < origin.x + static_cast<index_type>(w));
	assert(c.y >= origin.y && c.y < origin.x + static_cast<index_type>(w));
	const auto index = (c.y-origin.y) * w + c.x - origin.x;
	return vec.at(index);
}
