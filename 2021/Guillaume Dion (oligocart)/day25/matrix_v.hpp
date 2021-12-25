// A simple matrix type based on <vector>

#pragma once

#include <vector>

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	constexpr coord& operator+=(const coord& rhs) { x += rhs.x; y += rhs.y; return *this; }
};

template <typename T>
class matrix_v
{
public:
	using value_type = T;
	using index_type = int;
	using coord_type = coord<index_type>;

	explicit matrix_v(T default_value) : origin_{0,0}, w_{0}, h_{0}, vec_{}, defval_{default_value} { }
	void set_width(size_t width);
	bool operator==(const matrix_v& rhs) const { return data() == rhs.data(); }
	T& at(const coord_type& c);
	[[nodiscard]] const T& at(const coord_type& c) const;
	const std::vector<T>& data() const { return vec_; }
	auto width() const { return w_; }
	auto height() const { return h_; }

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
