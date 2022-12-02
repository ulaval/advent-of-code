// cuboid

#pragma once

#include <cassert>
#include <iostream>
#include <vector>

using std::vector;

struct range {
	int min;
	int max;
	size_t size() const { return max - min + 1; }
};

struct cuboid {
	bool is_void() const { return x.max < x.min || y.max < y.min || z.max < z.min; }
	bool intersects(const cuboid& other) const { return !intersection(other).is_void(); }
	cuboid intersection(const cuboid& other) const;
	vector<cuboid> split(const cuboid& other) const;
	size_t size() const { return x.size() * y.size() * z.size(); }
	range x;
	range y;
	range z;
};

cuboid cuboid::intersection(const cuboid& other) const
{
	const range isect_rx = { std::max(x.min, other.x.min), std::min(x.max, other.x.max) };
	const range isect_ry = { std::max(y.min, other.y.min), std::min(y.max, other.y.max) };
	const range isect_rz = { std::max(z.min, other.z.min), std::min(z.max, other.z.max) };
	return { isect_rx, isect_ry, isect_rz };
}

vector<cuboid> cuboid::split(const cuboid& other) const
{
	vector<cuboid> subparts;	// worst case is 6 sub parts...
	const auto isect = intersection(other);
	if (isect.is_void())
		return { *this };		// should not happen

	// large left part
	const cuboid left = { { x.min, isect.x.min - 1 }, { y.min, y.max }, { z.min, z.max } };
	if (!left.is_void()) subparts.push_back(left);
	// large right part
	const cuboid right = { { isect.x.max + 1, x.max }, { y.min, y.max }, { z.min, z.max } };
	if (!right.is_void()) subparts.push_back(right);
	// medium bottom part (does not include larger left and right parts)
	const cuboid bottom = { { left.x.max + 1, right.x.min - 1 }, { y.min, isect.y.min - 1 }, { z.min, z.max } };
	if (!bottom.is_void()) subparts.push_back(bottom);
	// medium top part (does not include larger left and right parts)
	const cuboid top = { { left.x.max + 1, right.x.min - 1 }, { isect.y.max + 1, y.max }, { z.min, z.max } };
	if (!top.is_void()) subparts.push_back(top);
	// small front part (includes neither left, right, top nor bottom)
	const cuboid front = { { left.x.max + 1, right.x.min - 1 }, { bottom.y.max + 1, top.y.min - 1 }, { z.min, isect.z.min - 1 } };
	if (!front.is_void()) subparts.push_back(front);
	// small back part (includes neither left, right, top nor bottom)
	const cuboid back = { { left.x.max + 1, right.x.min - 1 }, { bottom.y.max + 1, top.y.min - 1 }, { isect.z.max + 1, z.max } };
	if (!back.is_void()) subparts.push_back(back);

	return subparts;
}

// IO operations

std::ostream& operator<<(std::ostream& out, const range& r) {
	out << r.min << ".." << r.max;
	return out;
}

std::istream& operator>>(std::istream& in, range& r) {
	char ch;
	in >> r.min;
	if (in.good()) {
		in >> ch >> ch;
		if (in.good()) {
			in >> r.max;
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const cuboid& c) {
	out << "x=" << c.x << ",y=" << c.y << ",z=" << c.z;
	return out;
}

std::istream& operator>>(std::istream& in, cuboid& c) {
	char ch;
	in >> ch >> ch;
	if (in.good()) {
		in >> c.x;
		if (in.good()) {
			in >> ch >> ch >> ch;
			if (in.good()) {
				in >> c.y;
				if (in.good()) {
					in >> ch >> ch >> ch;
					if (in.good()) {
						in >> c.z;
					}
				}
			}
		}
	}
	return in;
}
