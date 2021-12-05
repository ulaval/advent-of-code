// AoC_2021_04

#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <numeric>

using std::size_t, std::cout, std::string, std::vector, std::map, std::array;

constexpr int N = 5;

struct cell {
	int row, col;
};

template<typename K, typename V>
std::vector<K> map_keys_to_vec(const map<K, V>& map)
{
	std::vector<K> vec;
	for (const auto& p : map)
		vec.push_back(p.first);
	return vec;
}

class board {
public:
	friend std::istream& operator>>(std::istream& in, board& obj);
	bool mark(int num) {
		if (data.contains(num)) {
			marked.push_back(num);
			const auto [r, c] = data[num];
			row[r]--;
			col[c]--;
			if (row[r] == 0 || col[c] == 0) {
				won = true;
				return won;
			}
		}
		return won;
	}
	int sum_unmarked() const {
		vector<int> unmarked;
		vector<int> sorted{marked};
		std::sort(sorted.begin(), sorted.end());
		const auto all = map_keys_to_vec(data);
		std::set_difference(all.cbegin(), all.cend(), sorted.cbegin(), sorted.cend(), std::back_inserter(unmarked));
		return std::accumulate(unmarked.cbegin(), unmarked.cend(), 0);
	}
	bool has_won() const { return won; }
private:
	bool won{false};
	map<int, cell> data{};
	vector<int> marked{};
	array<int, N> row{ N, N, N, N, N };
	array<int, N> col{ N, N, N, N, N };
};

std::istream& operator>>(std::istream& in, board& obj)
{
	obj.data.clear();
	int n;
	for (int r=0; r < N; r++) {
		for (int c=0; c < N; c++) {
			in >> n;
			if (!in.good())
				return in;
			obj.data.insert({n,{r,c}});
		}
	}
	return in;
}

auto read_input(std::istream& in) {
	string line;
	std::getline(in, line);
	std::istringstream iss{line};
	int n;
	char ch;
	vector<int> nums;
	while (iss >> n) {
		nums.push_back(n);
		iss >> ch;
	}
	vector<board> boards;
	board b;
	while (in >> b)
		boards.push_back(b);
	return std::make_pair(nums, boards);
}

int main() {

    const auto [numbers, boards] = read_input(std::cin);

    // Part 1
    {
		bool won = false;
		auto boards_copy{boards};
		for (const auto n : numbers) {
			for (auto& b : boards_copy) {
				if (b.mark(n)) {
					cout << "Part 1 answer = " << n * b.sum_unmarked() << '\n';
					won = true;
					break;
				}
			}
			if (won) break;
		}
    }

    // Part 2
    {
		auto board_remains = [](const auto& v){ return std::any_of(v.cbegin(), v.cend(), [](const auto& b){ return !b.has_won(); }); };
		bool all_won = false;
		auto boards_copy{boards};
		for (const auto n : numbers) {
			for (auto& b : boards_copy) {
				if (!b.has_won() && b.mark(n)) {
					if (!board_remains(boards_copy)) {
						cout << "Part 2 answer = " << n * b.sum_unmarked() << '\n';
						all_won = true;
						break;
					}
				}
			}
			if (all_won) break;
		}
    }
}
