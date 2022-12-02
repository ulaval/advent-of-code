// A matrix implementation based on <vector>

#pragma once

#include <cassert>
#include <limits>
#include <sstream>
#include <vector>
#include <iomanip>

#include "coord.hpp"

template <typename T>
class matrix_v
{
public:
	using value_type = T;
	using index_type = int;
	using coord_type = coord<index_type>;

	matrix_v(size_t width, size_t height, T default_value) : origin_{0, 0}, w_{width}, h_{height}, vec_(w_*h_, default_value), defval_{default_value} { }

	T& at(const coord_type& c);
	[[nodiscard]] const T& at(const coord_type& c) const;
	const std::vector<T>& data() const { return vec_; }
	auto width() const { return w_; }
	auto height() const { return h_; }
	auto size() const { return w_ * h_; }
	void print(std::ostream& out, const coord_type& origin, size_t _w, size_t _h) const;
	void print(std::ostream& out) const { print(out, origin_, w_, h_); }

private:
	coord_type origin_;
	size_t w_, h_;
	std::vector<T> vec_;
	T defval_;
};


template <typename T>
T& matrix_v<T>::at(const coord_type& c)
{
	assert(c.x >= origin_.x && c.x < origin_.x + static_cast<index_type>(w_));
	// we also check that Y is within bounds in debug builds
	assert(c.y >= origin_.y && c.y < origin_.y + static_cast<index_type>(h_));
	const auto index = (c.y-origin_.y) * w_ + c.x - origin_.x;
	return vec_.at(index);
}

template<typename T>
const T& matrix_v<T>::at(const matrix_v::coord_type& c) const
{
	// c must always be between X bounds as width cannot be changed
	assert(c.x >= origin_.x && c.x < origin_.x + static_cast<index_type>(w_));
	// we also check that Y is within bounds in debug builds
	assert(c.y >= origin_.y && c.y < origin_.y + static_cast<index_type>(h_));
	const auto index = (c.y-origin_.y) * w_ + c.x - origin_.x;
	return vec_.at(index);
}

template<typename T>
void matrix_v<T>::print(std::ostream& out, const coord_type& origin, size_t _w, size_t _h) const
{
	if (origin.x < origin_.x || origin.y < origin_.y || origin.x+_w > origin_.x+w_ || origin.y+_h > origin_.y+h_)
		throw std::invalid_argument("matrix_v<T>::print() : invalid region");
	std::ostringstream oss;
	for (auto y=origin.y; y<static_cast<index_type>(origin.y+_h); y++) {
		for (int x=origin.x; x<static_cast<index_type>(origin.x+_w); x++)
			oss << at({x,y});
		oss << '\n';
	}
	out << oss.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const matrix_v<T>& m) {
	m.print(out);
	return out;
}
