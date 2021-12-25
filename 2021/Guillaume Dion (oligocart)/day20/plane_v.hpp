// Auto-expandable (expand-on-write) matrix representing an infinite plane based on <vector>

#pragma once

#include <array>
#include <cassert>
#include <iostream>
#include <sstream>
#include <vector>

template <typename T>
struct coord
{
	T x, y;
	constexpr coord(T _x = T{}, T _y = T{}) : x{_x}, y{_y} { }
	std::array<coord, 9> adjacent9() const { return { coord{x-1, y-1}, coord{x, y-1}, coord{x+1, y-1}, coord{x-1, y}, coord{x ,y},
													  coord{x+1, y}, coord{x-1, y+1}, coord{x, y+1}, coord{x+1, y+1}}; }
};

struct rect {
	int x0, x1;
	int y0, y1;
};

template <typename T>
class plane_v
{
public:
	using index_type = int;
	using size_type = std::size_t;

	constexpr explicit plane_v(size_type x_margin = 0, size_type y_margin = 0, const T& defval = T{});
	constexpr const auto& data() const noexcept { return v_; }
	constexpr auto window() const noexcept { return rect{x0_, y0_, static_cast<int>(x0_ + w_), static_cast<int>(y0_ + h_)}; }
	const T& operator()(const coord<index_type>& c) const { return (*this)(c.x, c.y); }
	const T& operator()(index_type x, index_type y) const;	// accessor
	T& set(index_type x, index_type y);		// mutator

	void print(std::ostream& out) const { print(out, x0_, y0_, w_, h_); }
	void print(std::ostream& out, index_type x0, index_type y0, size_type w, size_type h) const;

private:
	constexpr bool is_in_window(index_type x, index_type y) const noexcept {
		return x >= x0_ && x < static_cast<index_type>(x0_+w_) && y >= y0_ && y < static_cast<index_type>(y0_+h_);
	}
	void rewindow(index_type x, index_type y);

	size_type xm_, ym_;		// x & y margins (to prevent "re-windowing")
	size_type w_, h_;		// window width & height
	index_type x0_, y0_;	// coordinates of window[0]
	T defval_;				// default value
	std::vector<T> v_;		// window data
	bool empty_ = true;		// plane is initially empty (all default values)
};

template <typename T>
constexpr plane_v<T>::plane_v(plane_v::size_type x_margin, plane_v::size_type y_margin, const T& defval)
	: xm_{x_margin}, ym_{y_margin}, w_{2*xm_+1}, h_{2*ym_+1}, x0_{0}, y0_{0}, defval_{defval}, v_(w_*h_, defval_)
{
}

// accessor
template <typename T>
const T& plane_v<T>::operator()(plane_v::index_type x, plane_v::index_type y) const
{
	if (!empty_ && is_in_window(x, y)) [[likely]] {
		const auto index = (y-y0_) * w_ + x - x0_;
		return v_[index];
	}
	return defval_;
}

// mutator
template<typename T>
T& plane_v<T>::set(plane_v::index_type x, plane_v::index_type y)
{
	if (empty_) [[unlikely]] {
		x0_ = x - xm_;
		y0_ = y - ym_;
		empty_ = false;
	}
	if (!is_in_window(x, y)) [[unlikely]] {
		rewindow(x, y);
	}
	const auto index = (y-y0_) * w_ + x - x0_;
	return v_[index];
}

template <typename T>
void plane_v<T>::rewindow(plane_v::index_type x, plane_v::index_type y)
{
	assert(static_cast<index_type>(x-xm_) <= x && static_cast<index_type>(y-ym_) <= y);		// underflow check
	assert(static_cast<index_type>(x+xm_) >= x && static_cast<index_type>(y+ym_) >= y);		// overflow check

	if (x >= x0_ && y >= y0_ && x < static_cast<index_type>(x0_+w_)) {
		assert(y >= static_cast<index_type>(y0_+h_));
		const size_type new_h = y - y0_ + ym_ + 1;
		v_.resize(w_*new_h, defval_);
		h_ = new_h;
	}
	else {
		const index_type new_x0 = std::min(x0_, static_cast<index_type>(x-xm_));
		const index_type new_y0 = std::min(y0_, static_cast<index_type>(y-ym_));
		const index_type new_x1 = std::max(static_cast<index_type>(x0_+w_)-1, static_cast<index_type>(x+xm_));
		const index_type new_y1 = std::max(static_cast<index_type>(y0_+h_)-1, static_cast<index_type>(y+ym_));
		assert(new_x1 > new_x0 && new_y1 > new_y0);
		const size_type new_w = static_cast<size_type>(new_x1-new_x0)+1;
		const size_type new_h = static_cast<size_type>(new_y1-new_y0)+1;
		assert(new_w > w_ || new_h > h_);

		std::vector<T> new_v(new_w*new_h, defval_);
		const auto dx = x0_ - new_x0;
		const auto dy = y0_ - new_y0;
		size_type index = 0;
		for (index_type y=0; y<static_cast<index_type>(h_); y++) {
			size_type new_index = (y+dy) * new_w + dx;
			for (index_type x=0; x<static_cast<index_type>(w_); x++) {
				assert(new_index < new_v.size());
				assert(index < v_.size());
				new_v[new_index++] = v_[index++];
			}
		}
		x0_ = new_x0;
		y0_ = new_y0;
		w_ = new_w;
		h_ = new_h;
		v_ = std::move(new_v);
	}
	assert(is_in_window(x, y));
}

template <typename T>
void plane_v<T>::print(std::ostream& out, plane_v::index_type x0, plane_v::index_type y0,
		plane_v::size_type w, plane_v::size_type h) const
{
	std::ostringstream oss;
	for (auto y=y0; y<static_cast<index_type>(y0+h); y++) {
		for (int x=x0; x<static_cast<index_type>(x0+w); x++)
			oss << operator()(x,y);
		oss << '\n';
	}
	out << oss.str();
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const plane_v<T>& obj) {
	obj.print(out);
	return out;
}
