#include <cassert>

#include "CupList.h"

CupList::CupList(const std::string& list, bool to_one_million)
    : _list{}, current{0}, picked_up{-1}, destination{-1}, min_label{max_cups}, max_label{0}, max_cups{(to_one_million) ? 1'000'000 : 9}
{
    int i = 0;
    for (const auto ch : list) {
        const auto label = ch-'0';
        min_label = std::min(min_label, label);
        max_label = std::max(max_label, label);
        Cup c{ this, label, wrap(i+1), wrap(i-1) };
        _list.push_back(c);
        i++;
    }
    if (to_one_million) {
        _list.reserve(1'000'000);
        for (int x = max_label; x < 1'000'000; x++) {
            Cup c{ this, x+1, wrap(x+1), wrap(x-1) };
            _list.push_back(c);
        }
        max_label = 1'000'000;
    }
}

int CupList::next(int from, int n) const
{
    assert(from >= 0 && from < max_cups);
    int index = from;
    while (n--)
        index = _list[index].next_index;
    return index;
}

int CupList::prev(int from, int n) const
{
    assert(from >= 0 && from < max_cups);
    int index = from;
    while (n--)
        index = _list[index].prev_index;
    return index;
}

void CupList::pick_up()
{
    assert(picked_up == -1);
    picked_up = _list[current].next_index;
    auto after = next(current, 4);
    _list[current].next_index = after;
    _list[after].prev_index = current;
#ifndef NDEBUG
    std::cout << "pick up: ";
    print_list(std::cout, picked_up, 3);
    std::cout << '\n';
#endif
}

void CupList::put_back()
{
    assert(picked_up != -1);
    assert(destination != -1);
    auto after = _list[destination].next_index;
    _list[destination].next_index = picked_up;
    _list[picked_up].prev_index = destination;
    _list[next(picked_up, 2)].next_index = after;
    _list[after].prev_index = next(picked_up, 2);
    destination = -1;
    picked_up = -1;
}

// try to find label beginning at current and skipping picked up cups and return index (or -1 if not found)
int CupList::find(int label) const
{
    if (_list[current].label == label)
        return current;

    for (int i = next(current); i != current; i = next(i)) {
        if (_list[i].label == label)
            return i;
    }
    return -1;
}

void CupList::select_dest()
{
    assert(destination == -1);
    auto target = _list[current].label - 1;
    destination = find(target);
    while (destination == -1) {
        target--;
        if (target < min_label)
            target = max_label;
        destination = find(target);
    }
#ifndef NDEBUG
    std::cout << "destination: " << _list[destination].label << '\n';
#endif
}

void CupList::move()
{
    pick_up();
    select_dest();
    put_back();
    current = next(current);
}

constexpr int CupList::wrap(int index)
{
    if (index < 0) {
        return max_cups + index;
    }
    if (index >= max_cups) {
        return index - max_cups;
    }
    return index;
}

void CupList::print_helper(std::ostream& out, int index) const
{
    if (index == current)
        out << '(';
    out << _list[index].label;
    if (index == current)
        out << ')';
    out << ' ';
}

// print count cups begining at from (or all of them if count == 0)
void CupList::print_list(std::ostream& out, int from, int count) const
{
    print_helper(out, from);
    for (int i = _list[from].next_index; i != from && --count != 0; i = _list[i].next_index) {
        print_helper(out, i);
    }
}

std::ostream& operator<<(std::ostream& out, const CupList& rhs)
{
    out << "cups: ";
    rhs.print_list(out, 0);
    return out;
}
