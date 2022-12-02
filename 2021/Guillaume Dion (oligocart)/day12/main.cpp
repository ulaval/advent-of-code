// AoC_2021_12

#include <cassert>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>

using std::size_t, std::cout, std::string, std::string_view, std::vector, std::set;

#include "graph_v.hpp"

struct cave {
	cave() = default;
	explicit cave(string_view cave_name) : name{cave_name}, is_small{cave_name[0] >= 'a' && cave_name[0] <= 'z'}, is_start{cave_name == "start"}, is_end{cave_name == "end"} { }
	bool operator==(const cave& rhs) const { return name == rhs.name; }
	bool operator<(const cave& rhs) const { return name[0] < rhs.name[0] || (name[0] == rhs.name[0] && name[1] < rhs.name[1]); }
	string name;
	bool is_small, is_start, is_end;
};

std::ostream& operator<<(std::ostream& out, const cave& obj) {
	out << obj.name;
	return out;
}

using graph_t = graph_v<cave>;

auto read_input(std::istream& in) {
	graph_t graph;
    string line;
    while (std::getline(in, line)) {
        const auto it = std::find(line.cbegin(), line.cend(), '-');
		cave c1{string_view{line.cbegin(), it}};
		cave c2{string_view{it+1, line.cend()}};
		if (!graph.has_vertex(c1)) graph.add_vertex(c1);
		if (!graph.has_vertex(c2)) graph.add_vertex(c2);
		graph.add_edge(c1, c2);
		graph.add_edge(c2, c1);
    }
	return graph;
}

void recurse(set<string>& all_paths, const graph_t& graph, vector<string> path, set<graph_t::vertex_type> visited, const graph_t::vertex_type& start, const cave& free_pass = cave{}, bool pass_used = false) {
	// Note: path et visited sont intentionnellement passés par valeur.
	const auto v = start;
	path.push_back(v.name);
	if (v.is_small) {
		if (v == free_pass && !pass_used)
			pass_used = true;
		else
			visited.insert(v);
	}
	if (v.is_end) {
		std::ostringstream oss;
		for (const auto& p : path)
			oss << p << ',';
		oss << v << '\n';
		all_paths.insert(oss.str());
		return;
	}
	for (const auto& w : graph.adjacent(v)) {
		if (!visited.contains(w))
			recurse(all_paths, graph, path, visited, w, free_pass, pass_used);
	}
}

int main() {

    const auto graph = read_input(std::cin);
	const auto& start = graph.vertex(cave{"start"});

    // Part 1
    {
		set<string> all_paths;
		recurse(all_paths, graph, {}, {}, start);
		cout << "Part 1 answer = " << all_paths.size() << '\n';
    }

    // Part 2
    {
		set<graph_t::vertex_type> smalls;
		for (const auto& [k, v] : graph.adj_list()) {
			if (k.is_small && !k.is_start && !k.is_end)
				smalls.insert(k);
		}
		set<string> all_paths;
		for (const auto& free_pass : smalls) {
			recurse(all_paths, graph, {}, {}, start, free_pass);
		}
		cout << "Part 2 answer = " << all_paths.size() << '\n';
    }
}
