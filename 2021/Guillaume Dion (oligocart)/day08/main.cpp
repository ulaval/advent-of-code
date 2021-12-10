// AoC_2021_08

#include <cassert>
#include <iostream>
#include <map>
#include <vector>

using std::size_t, std::cout, std::string, std::vector, std::map;

struct display {
	vector<string> pattern;
	vector<string> output;
};

auto read_input(std::istream& in) {
	char ch;
	vector<display> vec;
    vector<string> p(10);
	vector<string> o(4);
	while (in >> p[0] >> p[1] >> p[2] >> p[3] >> p[4] >> p[5] >> p[6] >> p[7] >> p[8] >> p[9] >> ch >> o[0] >> o[1] >> o[2] >> o[3]) {
		assert(ch == '|');
		std::for_each(p.begin(), p.end(), [](auto& s){ std::sort(s.begin(), s.end()); });
		std::for_each(o.begin(), o.end(), [](auto& s){ std::sort(s.begin(), s.end()); });
		vec.emplace_back(p, o);
	}
	return vec;
}

auto deduce(const vector<string>& pattern) {
	map<string, int> sigmap;
	vector<string> vs(10);
	auto setsig = [&](const string& s, int n){ sigmap.insert({s, n}); vs[n] = s; };
	char f = '\0';
	while (sigmap.size() < 10) {
		for (const string& s : pattern) {
			if (sigmap.contains(s))
				continue;
			switch (s.size()) {
				case 2ul: setsig(s, 1); break;
				case 3ul: setsig(s, 7); break;
				case 4ul: setsig(s, 4); break;
				case 5ul:
					if (!vs[1].empty() && std::all_of(vs[1].cbegin(), vs[1].cend(), [&s](const char c){ return s.find(c) != string::npos; }))
						setsig(s, 3);
					else if (f != '\0')
						setsig(s, s.find(f) == string::npos ? 2 : 5);
					break;
				case 6ul:
					if (!vs[1].empty() && !vs[4].empty()) {
						if (!std::all_of(vs[1].cbegin(), vs[1].cend(), [&s](const char c){ return s.find(c) != string::npos; })) {
							f = (s.find(vs[1][0]) == string::npos) ? vs[1][1] : vs[1][0];
							setsig(s, 6);
						} else if (std::all_of(vs[4].cbegin(), vs[4].cend(), [&s](const char c){ return s.find(c) != string::npos; }))
							setsig(s, 9);
						else
							setsig(s, 0);
					}
					break;
				case 7ul: setsig(s, 8); break;
			}
		}
	}
	return sigmap;
}

template <typename T, typename... Ts>
bool is_any_of(T&& t, Ts&&... ts)
{
	return ((t == ts) || ...);
}

int main() {

    const auto disp = read_input(std::cin);

    // Part 1
    {
		int n = 0;
		for (const auto& [pattern, output] : disp) {
			for (const auto& s : output) {
				if (is_any_of(s.size(), 2ul, 3ul, 4ul, 7ul))
					n++;
			}
		}
		cout << "Part 1 answer = " << n << '\n';
    }

    // Part 2
    {
		int sum = 0;
		for (const auto& [pattern, output] : disp) {
			const auto sigmap = deduce(pattern);
			for (int v = 1000, i = 0; v >= 1; v /= 10, i++)
				sum += v * sigmap.at(output[i]);
		}
		cout << "Part 2 answer = " << sum << '\n';
    }
}
