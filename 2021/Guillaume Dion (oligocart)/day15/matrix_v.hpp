// A simple matrix type based on <vector>

#pragma once

#include <array>
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
	constexpr coord up(int n = 1) const { return coord{x, y-n}; }
	constexpr coord down(int n = 1) const { return coord{x, y+n}; }
	constexpr coord left(int n = 1) const { return coord{x-n, y}; }
	constexpr coord right(int n = 1) const { return coord{x+n, y}; }
	constexpr bool in_rect(T _x, T _y, size_t _w, size_t _h) const {
		assert(_x <= static_cast<T>(_x+_w) && _y <= static_cast<T>(_y+_h));	// check overflow
		return x >= _x && x < static_cast<T>(_x+_w) && y >= _y && y < static_cast<T>(_y+_h);
	}
	std::array<coord, 4> adjacent() const { return { coord{x, y-1}, coord{x-1, y}, coord{x+1, y}, coord{x, y+1} }; }
};

template <typename T>
class matrix_v
{
public:
	using value_type = T;
	using index_type = int;
	using coord_type = coord<index_type>;

	matrix_v(size_t width, size_t height, T default_value) : origin_{0, 0}, w_{width}, h_{height}, vec_(w_*h_, default_value), defval_{default_value} { }
	explicit matrix_v(T default_value) : origin_{0,0}, w_{0}, h_{0}, vec_{}, defval_{default_value} { }
	void set_width(size_t width);

	T& at(const coord_type& c);
	[[nodiscard]] const T& at(const coord_type& c) const;
	auto width() const { return w_; }
	auto height() const { return h_; }
	bool has_coord(const coord_type& c) const { return c.in_rect(origin_.x, origin_.y, w_, h_); }
	decltype(auto) adjacent(const coord_type& c) const;

private:
	coord_type origin_;
	size_t w_, h_;
	std::vector<T> vec_;
	T defval_;

	void extend(size_t index);
};

template <typename T>
void matrix_v<T>::extend(size_t index)
{
	vec_.resize(index / w_ * w_ + w_, defval_);
	h_ = index / w_ + 1;
}

template <typename T>
void matrix_v<T>::set_width(size_t width)
{
	if (w_ == width)
		return;
	w_ = width;
	extend(0);
}

template <typename T>
T& matrix_v<T>::at(const coord_type& c)
{
	const auto index = (c.y-origin_.y) * w_ + c.x - origin_.x;
	if (index >= vec_.size())
		extend(index);
	return vec_.at(index);
}

template<typename T>
const T& matrix_v<T>::at(const matrix_v::coord_type& c) const
{
	const auto index = (c.y-origin_.y) * w_ + c.x - origin_.x;
	return vec_.at(index);
}

template<typename T>
decltype(auto) matrix_v<T>::adjacent(const matrix_v::coord_type& c) const
{
	std::vector<coord_type> adj;
	const auto c_adj = c.adjacent();
	std::copy_if(c_adj.cbegin(), c_adj.cend(), std::back_inserter(adj), [this](const auto& c){ return this->has_coord(c); });
	return adj;
}
