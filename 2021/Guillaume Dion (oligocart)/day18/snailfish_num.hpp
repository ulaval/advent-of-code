// Snailfish number type

#pragma once

#include <iostream>
#include <set>
#include <queue>
#include <stack>
#include <sstream>

using val_t = uint16_t;

template <typename T>
struct pair {
	pair* parent_p;
	T x_val;
	T y_val;
	pair* x_sub_p;
	pair* y_sub_p;
	void print(std::ostream& out) const;
	long magnitude() const;
};

template<typename T>
void pair<T>::print(std::ostream& out) const
{
	if (x_sub_p == nullptr && y_sub_p == nullptr) {
		out << '[' << x_val << ',' << y_val << ']';
	}
	else {
		out << '[';
		if (x_sub_p != nullptr)
			out << *x_sub_p;
		else
			out << x_val;
		out << ',';
		if (y_sub_p != nullptr)
			out << *y_sub_p;
		else
			out << y_val;
		out << ']';
	}
}

template<typename T>
long pair<T>::magnitude() const
{
	long res = 0ul;
	res += (x_sub_p == nullptr) ? 3 * x_val : 3 * x_sub_p->magnitude();
	res += (y_sub_p == nullptr) ? 2 * y_val : 2 * y_sub_p->magnitude();
	return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const pair<T>& obj) {
	obj.print(out);
	return out;
}

using pair_t = pair<val_t>;

template <size_t N>
struct snailfish_num {
	snailfish_num() : pairs{}, root_p{&pairs[0]}, free_p{&pairs[0]} { }
	array<pair_t, N> pairs;
	pair_t* root_p;
	pair_t* free_p;

	snailfish_num& operator+=(const snailfish_num& rhs);

	void reduce();
	void explode(pair_t* p);
	void split(pair_t* p);
	int depth(const pair_t* p) const;
	pair_t* find_depth4() const;
	pair_t* find_gt9(pair_t* start) const;
	std::string to_string() const;
	pair_t* copy_pair(const pair_t* src);
};

template <size_t N>
std::ostream& operator<<(std::ostream& out, const snailfish_num<N>& obj) {
	const string s = obj.to_string();
	out << s;
	return out;
}

template <size_t N>
pair_t* snailfish_num<N>::copy_pair(const pair_t* src) {
	assert(free_p != nullptr && src != nullptr);
	pair_t* dest = free_p++;
	assert(free_p < &pairs[0] + N*sizeof(pair_t));
	*dest = *src;
	if (src->x_sub_p != nullptr) {
		dest->x_sub_p = copy_pair(src->x_sub_p);
		dest->x_sub_p->parent_p = dest;
	}
	if (src->y_sub_p != nullptr) {
		dest->y_sub_p = copy_pair(src->y_sub_p);
		dest->y_sub_p->parent_p = dest;
	}
	return dest;
}

template <size_t N>
snailfish_num<N>& snailfish_num<N>::operator+=(const snailfish_num& rhs) {
	pair_t* const new_root = free_p++;
	assert(free_p < &pairs[0] + N*sizeof(pair_t));
	new_root->parent_p = nullptr;
	new_root->x_sub_p = root_p;
	new_root->x_sub_p->parent_p = new_root;
	// append rhs
	new_root->y_sub_p = copy_pair(rhs.root_p);
	new_root->y_sub_p->parent_p = new_root;
	root_p = new_root;
	reduce();
	return *this;
}

template <size_t N>
void snailfish_num<N>::explode(pair_t* const p) {
	assert(p != nullptr);
	assert(p->x_sub_p == nullptr && p->y_sub_p == nullptr);

	// easy one...
	{
		pair_t* cp = p;
		pair_t* pp = p->parent_p;
		while (pp != nullptr && pp->x_sub_p == cp) {
			cp = pp;
			pp = pp->parent_p;
		}
		if (pp != nullptr) {
			if (pp->x_sub_p != nullptr) {
				pp = pp->x_sub_p;
				while (pp->y_sub_p != nullptr)
					pp = pp->y_sub_p;
				pp->y_val += p->x_val;
			}
			else pp->x_val += p->x_val;
		}
	}

	{
		pair_t* cp = p;
		pair_t* pp = p->parent_p;
		while (pp != nullptr && pp->y_sub_p == cp) {
			cp = pp;
			pp = pp->parent_p;
		}
		if (pp != nullptr) {
			if (pp->y_sub_p != nullptr) {
				pp = pp->y_sub_p;
				while (pp->x_sub_p != nullptr)
					pp = pp->x_sub_p;
				pp->x_val += p->y_val;
			}
			else pp->y_val += p->y_val;
		}
	}

	// explode p
	assert(p->parent_p != nullptr);
	assert(p->parent_p->x_sub_p == p || p->parent_p->y_sub_p == p);
	if (p->parent_p->x_sub_p == p) {
		p->parent_p->x_sub_p = nullptr;
		p->parent_p->x_val = 0;
	}
	else {
		p->parent_p->y_sub_p = nullptr;
		p->parent_p->y_val = 0;
	}
	// p->parent_p = nullptr;		// mark deleted : p->parent_p == nullptr && root_p != p
}

template<size_t N>
void snailfish_num<N>::split(pair_t* const p) {
	assert(p != nullptr);
	assert(p->x_val > 9 || p->y_val > 9);

	pair_t* const new_p = free_p++;
	assert(free_p < &pairs[0] + N*sizeof(pair_t));
	if (p->x_val > 9) {
		new_p->x_val = p->x_val/2;
		new_p->y_val = (p->x_val % 2 == 0) ? p->x_val/2 : p->x_val/2 + 1;
		assert(p->x_sub_p == nullptr);
		p->x_sub_p = new_p;
		p->x_val = 0;
	}
	else {
		new_p->x_val = p->y_val/2;
		new_p->y_val = (p->y_val % 2 == 0) ? p->y_val/2 : p->y_val/2 + 1;
		assert(p->y_sub_p == nullptr);
		p->y_sub_p = new_p;
		p->y_val = 0;
	}
	new_p->parent_p = p;
}

template<size_t N>
int snailfish_num<N>::depth(const pair_t* const p) const
{
	assert(p != nullptr);
	int depth = 1;
	const pair_t* pp = p->parent_p;
	while (pp != nullptr) {
		pp = pp->parent_p;
		depth++;
	}
	return depth;
}

template<size_t N>
pair_t* snailfish_num<N>::find_depth4() const
{
	// DFS
	std::stack<pair_t*> s;
	std::set<pair_t*> discovered;
	s.push(root_p);
	pair_t* found_p = nullptr;
	while (!s.empty()) {
		pair_t* p = s.top(); s.pop();
		if (depth(p) > 4) {
			found_p = p;
			break;
		}
		if (!discovered.contains(p)) {
			discovered.insert(p);
			if (p->y_sub_p != nullptr)
				s.push(p->y_sub_p);
			if (p->x_sub_p != nullptr)
				s.push(p->x_sub_p);
		}
	}
	return found_p;
}

template<size_t N>
pair_t* snailfish_num<N>::find_gt9(pair_t* start) const
{
	if (start->x_val > 9 || (start->x_sub_p == nullptr && start->y_val > 9))
		return start;

	pair_t* res = nullptr;
	if (start->x_sub_p != nullptr)
		res = find_gt9(start->x_sub_p);
	if (res != nullptr) return res;

	if (start->y_sub_p != nullptr)
		res = find_gt9(start->y_sub_p);
	if (res != nullptr) return res;

	return nullptr;
}

template<size_t N>
void snailfish_num<N>::reduce()
{
	pair_t* p = nullptr;
	while (true) {
		// find leftmost depth=4 (if any)
		p = find_depth4();
		if (p != nullptr) {
			explode(p);
		}
		else {
			// find leftmost regular number > 9 (if any)
			p = find_gt9(root_p);
			if (p == nullptr)
				break;
			split(p);
		}
	}
}

template<size_t N>
std::string snailfish_num<N>::to_string() const
{
	std::ostringstream oss;
	oss << *this->root_p;
	return oss.str();
}

