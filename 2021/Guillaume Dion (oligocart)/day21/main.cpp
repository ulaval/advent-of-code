// AoC_2021_21

#include <cassert>
#include <iostream>
#include <vector>

using std::size_t, std::cout, std::string, std::vector, std::pair;

struct player {
	player(uint16_t start_cell) : cell{start_cell}, score{0} { }
	void move(uint16_t num_cells) {
		cell += num_cells % 10;
		if (cell > 10) cell -= 10;
		score += cell;
	}
	uint16_t cell;
	uint16_t score;
};

struct d100_dice {
	d100_dice() : rolled_value{0}, roll_count{0} { }
	auto roll() {
		roll_count++;
		rolled_value++;
		if (rolled_value > 100)
			rolled_value = 1;
		return rolled_value;
	}
	uint16_t rolled_value;
	uint16_t roll_count;
};

struct wins_t {
	wins_t() : p1_wins{0l}, p2_wins{0l} { }
	wins_t(long p1, long p2) : p1_wins{p1}, p2_wins{p2} { }
	long p1_wins;
	long p2_wins;
	wins_t& operator+=(const wins_t& rhs) { p1_wins += rhs.p1_wins; p2_wins += rhs.p2_wins; return *this; }
};

wins_t universe_wins(long count, uint16_t rolled_sum, player p1, player p2, bool p1_turn) {
	if (rolled_sum > 0) {
		if (p1_turn)
			p1.move(rolled_sum);
		else
			p2.move(rolled_sum);
	}

	if (p1.score >= 21)
		return {count, 0l};
	if (p2.score >= 21)
		return {0l, count};

	wins_t wins;
	wins += universe_wins(1 * count, 3, p1, p2, !p1_turn);
	wins += universe_wins(3 * count, 4, p1, p2, !p1_turn);
	wins += universe_wins(6 * count, 5, p1, p2, !p1_turn);
	wins += universe_wins(7 * count, 6, p1, p2, !p1_turn);
	wins += universe_wins(6 * count, 7, p1, p2, !p1_turn);
	wins += universe_wins(3 * count, 8, p1, p2, !p1_turn);
	wins += universe_wins(1 * count, 9, p1, p2, !p1_turn);
	return wins;
}

int main() {

    // Part 1
    {
		player p1{4};
		player p2{5};
		d100_dice dice;
		while (true) {
			p1.move(dice.roll() + dice.roll() + dice.roll());
			if (p1.score >= 1000) break;
			p2.move(dice.roll() + dice.roll() + dice.roll());
			if (p2.score >= 1000) break;
		}
		const auto min_score = std::min(p1.score, p2.score);
		cout << "Part 1 answer = " << min_score * dice.roll_count << '\n';
    }

    // Part 2
    {
		player p1{4};
		player p2{5};
		const auto [p1_wins, p2_wins] = universe_wins(1, 0, p1, p2, false);
		cout << "Part 2 answer = " << std::max(p1_wins, p2_wins) << '\n';
    }
}
