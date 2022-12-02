// graph_v - Graph dirigé implémenté par liste d'adjacence.

#pragma once

#include <map>
#include <set>

template <typename V>
class graph_v
{
public:
	using vertex_type = V;

	graph_v() = default;
	bool has_vertex(const V& vertex) const { return adj_.contains(vertex); }
	void add_vertex(const V& vertex) { adj_.insert({vertex, {}}); }
	void add_edge(const V& from, const V& to) { adj_[from].insert(to); }
	const V& vertex(const V& v) const { return adj_.find(v)->first; }
	const std::set<V>& adjacent(const V& from) const { return adj_.at(from); }
	const auto& adj_list() const { return adj_; }

private:
	std::map<V, std::set<V>> adj_;
};
