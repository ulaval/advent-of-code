//
// Created by gui_d on 2021-10-21.
//

#pragma once

#include <cassert>
#include <array>
#include <iostream>

template <typename T>
struct coord
{
	static_assert(std::is_arithmetic_v<T>);

	using value_type = T;

	T x, y;

	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr bool operator==(const coord& rhs) const { return x == rhs.x && y == rhs.y; }
	constexpr bool operator!=(const coord& rhs) const { return x != rhs.x || y != rhs.y; }
	constexpr coord& operator+=(const coord& rhs) { x += rhs.x; y += rhs.y; return *this; }
	constexpr coord& operator-=(const coord& rhs) { x -= rhs.x; y -= rhs.y; return *this; }
	constexpr coord operator+(const coord& rhs) const { coord x{*this}; x += rhs; return x; }
	constexpr coord operator-(const coord& rhs) const { coord x{*this}; x -= rhs; return x; }
	constexpr bool operator<(const coord& rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
	constexpr bool operator>(const coord& rhs) const { return y > rhs.y || (y == rhs.y && x > rhs.x); }
	constexpr bool operator<=(const coord& rhs) const { return *this < rhs || *this == rhs; }
	constexpr bool operator>=(const coord& rhs) const { return *this > rhs || *this == rhs; }
	constexpr bool in_rect(T _x, T _y, size_t _w, size_t _h) const {
		assert(_x <= static_cast<value_type>(_x+_w) && _y <= static_cast<value_type>(_y+_h));	// check overflow
		return x >= _x && x < static_cast<value_type>(_x+_w) && y >= _y && y < static_cast<value_type>(_y+_h);
	}
	constexpr size_t distance(const coord& rhs) const { return std::abs(x-rhs.x) + std::abs(y-rhs.y); }
	std::array<coord, 4> adjacent4() const { return { coord{x, y-1}, coord{x-1, y}, coord{x+1, y}, coord{x, y+1} }; }
	std::array<coord, 8> adjacent8() const { return { coord{x-1, y-1}, coord{x, y-1}, coord{x+1, y-1}, coord{x-1, y},
													  coord{x+1, y}, coord{x-1, y+1}, coord{x, y+1}, coord{x+1, y+1}}; }
};

template <typename T>
std::ostream& operator<<(std::ostream& out, const coord<T>& obj)
{
	out << '(' << obj.x << ',' << obj.y << ')';
	return out;
}
