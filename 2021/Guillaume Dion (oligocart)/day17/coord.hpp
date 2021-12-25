// Coordinates type

#pragma once

#include <cassert>

template <typename T>
struct coord
{
	static_assert(std::is_arithmetic_v<T>);
	using value_type = T;
	T x, y;

	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr coord& operator+=(const coord& rhs) { x += rhs.x; y += rhs.y; return *this; }
	constexpr coord operator+(const coord& rhs) const { coord x{*this}; x += rhs; return x; }
	constexpr bool operator<(const coord& rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
	constexpr bool in_rect(T _x, T _y, size_t _w, size_t _h) const {
		assert(_x <= static_cast<value_type>(_x+_w) && _y <= static_cast<value_type>(_y+_h));	// check overflow
		return x >= _x && x < static_cast<value_type>(_x+_w) && y >= _y && y < static_cast<value_type>(_y+_h);
	}
};
