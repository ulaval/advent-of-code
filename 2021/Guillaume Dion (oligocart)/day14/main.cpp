// AoC_2021_14

#include <cassert>
#include <iostream>
#include <vector>
#include <list>
#include <map>

using std::size_t, std::cout, std::string, std::vector, std::list, std::map, std::pair, std::make_pair;

using poly_t = list<char>;
using pins_t = map<pair<char, char>, char>;
using occ_t = map<pair<char, char>, long>;

auto read_input(std::istream& in) {
	poly_t poly;
	string line;
	std::getline(in, line);
	for (const auto c : line)
		poly.push_back(c);

	pins_t pins;
	char c1, c2, ch, res;
	while (in >> c1 >> c2 >> ch >> ch >> res)
		pins.insert({{c1, c2}, res});

    return make_pair(poly, pins);
}

void step(poly_t& poly, const pins_t& pins) {
	auto it1 = poly.begin();
	auto it2 = std::next(it1);
	while (it2 != poly.end()) {
		const auto p = make_pair(*it1, *it2);
		if (pins.contains(p)) {
			const auto res = pins.at(p);
			poly.insert(it2, res);
		}
		it1 = it2;
		it2++;
	}
}

long score(const poly_t& poly) {
	vector<long> table(26, 0);
	for (const auto c : poly)
		table[c - 'A']++;
	vector<long> copy;
	std::copy_if(table.cbegin(), table.cend(), std::back_inserter(copy), [](const auto x){ return x != 0; });
	const auto [min_it, max_it] = std::minmax_element(copy.cbegin(), copy.cend());
	return *max_it - *min_it;
}

auto occurrences(const poly_t& poly) {
	occ_t occ;
	auto it1 = poly.cbegin();
	auto it2 = std::next(it1);
	while (it2 != poly.cend()) {
		const auto p = make_pair(*it1, *it2);
		if (occ.contains(p)) occ[p]++;
		else occ.insert({p, 1});
		it1 = it2;
		it2++;
	}
	return occ;
}

void step_occ(occ_t& occ, const pins_t& pins) {
	const auto copy{occ};
	occ.clear();
	for (const auto& [p, cnt] : copy) {
		 if (pins.contains(p)) {
			 const auto r = pins.at(p);
			 const auto p1 = make_pair(p.first, r);
			 const auto p2 = make_pair(r, p.second);
			 if (occ.contains(p1)) occ[p1] += cnt;
			 else occ.insert({p1, cnt});
			 if (occ.contains(p2)) occ[p2] += cnt;
			 else occ.insert({p2, cnt});
		 }
		 else occ.insert({p, cnt});
	}
}

int main() {

    const auto [poly_orig, pins] = read_input(std::cin);

	// Part 1
	{
		auto poly{poly_orig};
		for (int i=1; i<=10; i++)
			step(poly, pins);
		cout << "Part 1 answer = " << score(poly) << '\n';
	}

	// Part 2
	{
		auto occ = occurrences(poly_orig);
		for (int i=1; i<=40; i++)
			step_occ(occ, pins);
		map<char, long> elems;
		for (const auto& [p, cnt] : occ) {
			if (elems.contains(p.first)) elems[p.first] += cnt;
			else elems.insert({p.first, cnt});
		}
		const auto [min_it, max_it] = std::minmax_element(elems.cbegin(), elems.cend(), [](const auto& a, const auto& b){ return a.second < b.second; });
		cout << "Part 2 answer = " << max_it->second - min_it->second << " ±1\n";
	}
}
