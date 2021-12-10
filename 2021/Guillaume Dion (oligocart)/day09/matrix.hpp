// A simple matrix based on <vector>

#pragma once

#include <cassert>
#include <array>
#include <vector>

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr bool operator<(const coord& rhs) const { return y < rhs.y || (y == rhs.y && x < rhs.x); }
	[[nodiscard]] std::array<coord, 4> adjacent() const { return { coord{x, y-1}, coord{x-1, y}, coord{x+1, y}, coord{x, y+1} }; }
};

template <typename T>
class matrix
{
public:
	using index_type = int;
	using coord_type = coord<index_type>;
	explicit matrix(T default_value) : origin{0,0}, w{0}, h{0}, vec{}, defval{default_value} { }
	void set_width(size_t width);
	T& at(const coord_type& c);
	[[nodiscard]] const T& at(const coord_type& c) const;
	auto dimensions() const { return std::make_pair(w, h); }
	auto adjacent(const coord_type& c) const;

private:
	coord_type origin;
	size_t w, h;
	std::vector<T> vec;
	T defval;

	void extend(size_t index);
};

template <typename T>
void matrix<T>::extend(size_t index)
{
	assert(w > 0);
	vec.resize(index / w * w + w, defval);
	h = index / w + 1;
}

template <typename T>
void matrix<T>::set_width(size_t width)
{
	if (w == width)
		return;
	assert(w == 0 && width > 0);
	w = width;
	extend(0);
}

template <typename T>
T& matrix<T>::at(const coord_type& c)
{
	const auto index = (c.y-origin.y) * w + c.x - origin.x;
	if (index >= vec.size())
		extend(index);
	return vec.at(index);
}

template<typename T>
const T& matrix<T>::at(const matrix::coord_type& c) const
{
	const auto index = (c.y-origin.y) * w + c.x - origin.x;
	return vec.at(index);
}

template<typename T>
auto matrix<T>::adjacent(const matrix::coord_type& c) const
{
	vector<coord_type> vec;
	for (const auto& a : c.adjacent()) {
		if (a.x >= 0 && a.x < static_cast<int>(w) && a.y >= 0 && a.y < static_cast<int>(h))
			vec.push_back(a);
	}
	return vec;
}
