// AoC 2020-22

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <deque>
#include <vector>
#include <stack>

#ifdef NDEBUG
constexpr bool debug_build = false;
#else
constexpr bool debug_build = true;
#endif

int play_game(std::deque<int>& pl1, std::deque<int>& pl2);
int play_round(std::deque<int>& pl1, std::deque<int>& pl2);

void print_plays(int c1, int c2)
{
    std::cout << "Player 1 plays: " << c1 << '\n';
    std::cout << "Player 2 plays: " << c2 << '\n';
}

void print_deck(const std::deque<int>& deck)
{
    if (!deck.empty()) {
        std::cout << *(deck.cbegin());
        for (auto it = std::next(deck.cbegin()); it != deck.cend(); it++)
            std::cout << ", " << *it;
    }
    std::cout << '\n';
}

void print_decks(const std::deque<int>& pl1, const std::deque<int>& pl2)
{
    std::cout << "Player 1's deck: ";
    print_deck(pl1);
    std::cout << "Player 2's deck: ";
    print_deck(pl2);
}

std::deque<int> copy_top_n(const std::deque<int>& q, int n)
{
    std::deque<int> copy{q};
    std::deque<int> top_n;
    while (n--) {
        top_n.push_back(copy.front());
        copy.pop_front();
    }
    return top_n;
}

// returns winning's player number
int play_round(std::deque<int>& pl1, std::deque<int>& pl2)
{
    if constexpr (debug_build) { print_decks(pl1, pl2); }

    const auto c1 = pl1.front();
    const auto c2 = pl2.front();
    pl1.pop_front();
    pl2.pop_front();

    if constexpr (debug_build) { print_plays(c1, c2); }

    if (c1 <= pl1.size() && c2 <= pl2.size()) {
        if constexpr (debug_build) {
            std::cout << "Playing a sub-game to determine the winner...\n" << std::endl;
        }
        auto new_pl1 = copy_top_n(pl1, c1);
        auto new_pl2 = copy_top_n(pl2, c2);
        auto winner = play_game(new_pl1, new_pl2);
        if (winner == 1) {
            pl1.push_back(c1);
            pl1.push_back(c2);
        }
        else {
            pl2.push_back(c2);
            pl2.push_back(c1);
        }
        return winner;
    }
    else {
        if (c1 > c2) {
            pl1.push_back(c1);
            pl1.push_back(c2);
            return 1;
        }
        else {
            pl2.push_back(c2);
            pl2.push_back(c1);
            return 2;
        }
    }
}

bool check_history(std::vector<std::deque<int>>& pl1_hist, std::vector<std::deque<int>>& pl2_hist, const std::deque<int>& pl1, const std::deque<int>& pl2)
{
    bool pl1_check = true, pl2_check = true;
    for (const auto& h : pl1_hist) {
        if (h == pl1)
            pl1_check = false;
    }
    for (const auto& h : pl2_hist) {
        if (h == pl2)
            pl2_check = false;
    }
    if (!pl1_check && !pl2_check)
        return false;
    pl1_hist.push_back(pl1);
    pl2_hist.push_back(pl2);
    return true;
}

// returns winning's player number
int play_game(std::deque<int>& pl1, std::deque<int>& pl2)
{
    static int game_id = 0;
    static std::stack<int> games{};
    games.push(++game_id);
    if constexpr (debug_build) {
        std::cout << "=== Game " << games.top() << " ===\n\n";
    }

    std::vector<std::deque<int>> pl1_history, pl2_history;

    int winner = 0;
    int round_number = 1;
    bool quit_game = false;
    while (!quit_game && !pl1.empty() && !pl2.empty()) {
        if constexpr (debug_build) { 
            std::cout << "-- Round " << round_number << " (Game " << games.top() << ") --\n";
        }
        if (!check_history(pl1_history, pl2_history, pl1, pl2)) {
            if constexpr (debug_build) {
                std::cout << "Infinite game prevention : player 1 wins!\n\n";
            }
            winner = 1;
            quit_game = true;
        }
        else {
            winner = play_round(pl1, pl2);
            if constexpr (debug_build) {
                std::cout << "Player " << winner << " wins round " << round_number << " of game " << games.top() << "!\n" << std::endl;
            }
            round_number++;
        }
    }
    if constexpr (debug_build) {
        std::cout << "The winner of game " << games.top() << " is player " << winner << "!\n\n";
    }
    games.pop();
    if constexpr (debug_build) {
        if (!games.empty()) {
            std::cout << "...anyway, back to game " << games.top() << ".\n";
        }
    }
    return winner;
}

unsigned long long deck_score(std::deque<int>& winning_deck)
{
    auto mul = winning_deck.size();
    auto score = 0ULL;
    while (!winning_deck.empty()) {
        const auto x = winning_deck.front();
        winning_deck.pop_front();
        score += mul-- * x;
    }
    return score;
}

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    std::string line;
    getline(input_file, line);
    assert(line.starts_with("Player 1"));
    std::deque<int> pl1, pl2, pl1_orig, pl2_orig;
    bool player2 = false;
    while (getline(input_file, line)) {
        if (line.starts_with("Player 2")) {
            player2 = true;
            continue;
        }
        if (!line.empty() && std::isdigit(line[0])) {
            (player2) ? pl2.push_back(std::stoi(line)) : pl1.push_back(std::stoi(line));
        }
    }
    pl1_orig = pl1;
    pl2_orig = pl2;

    // Part 1
    while (!pl1.empty() && !pl2.empty()) {
        auto c1 = pl1.front();
        auto c2 = pl2.front();
        pl1.pop_front();
        pl2.pop_front();
        if (c1 > c2) {
            pl1.push_back(c1);
            pl1.push_back(c2);
        }
        else {
            pl2.push_back(c2);
            pl2.push_back(c1);
        }
    }
    const auto score1 = deck_score((pl1.empty()) ? pl2 : pl1);
    std::cout << "Part 1 answer = " << score1 << '\n';

    // Part 2
    pl1 = pl1_orig;
    pl2 = pl2_orig;
    auto winner = play_game(pl1, pl2);
    if constexpr (debug_build) {
        std::cout << "== Post-game results ==\n";
        print_decks(pl1, pl2);
    }
    const auto score2 = deck_score((winner == 1) ? pl1 : pl2);
    std::cout << "Part 2 answer = " << score2 << '\n';
}
