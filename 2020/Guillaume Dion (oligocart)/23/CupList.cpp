#include <cassert>

#include "CupList.h"

CupList::CupList(const std::string& list, int max_label)
    : _cup{}, _min{1}, _max{1}, _current{0}, _initial{0}, _picked{0}
{
    auto list_size = static_cast<int>(list.size());
    if (max_label == 0)
        max_label = list_size;
    _max = max_label;
    _cup.resize(max_label+1);

    auto label = list[0]-'0';
    auto prev = label;
    _initial = label;
    _current = label;
    for (int i=1; i<list.size(); i++) {
        label = list[i]-'0';
        _cup[label].prev = prev;
        _cup[prev].next = label;
        prev = label;
    }
    _cup[label].next = _current;
    _cup[_current].prev = label;

    if (max_label > list.size()) {
        for (int i=list_size+1; i <= max_label; i++) {
            _cup[i].prev = prev;
            _cup[prev].next = i;
            prev = i;
        }
        _cup[max_label].next = _current;
        _cup[_current].prev = max_label;
    }
}

int CupList::wrap(int label) const
{
    if (label < _min)
        label = _max;
    if (label > _max)
        label = _min;
    return label;
}

int CupList::prev(int label, int n) const
{
    while (n--)
        label = _cup[label].prev;
    return label;
}

int CupList::next(int label, int n) const
{
    while (n--)
        label = _cup[label].next;
    return label;
}

bool CupList::is_picked_up(int label) const
{
    assert(_picked != 0);
    if (label == _picked || label == next(_picked) || label == next(_picked, 2))
        return true;
    return false;
}

void CupList::move()
{
    // pick up three
    _picked = next(_current);
    auto after = next(_picked, 3);
    _cup[_current].next = after;
    _cup[after].prev = _current;

    // select destination
    int destination = wrap(_current-1);
    while (is_picked_up(destination)) {
        destination = wrap(destination-1);
    }

    // put back
    auto last_picked_up = next(_picked, 2);
    after = _cup[destination].next;
    _cup[destination].next = _picked;
    _cup[_picked].prev = destination;
    _cup[last_picked_up].next = after;
    _cup[after].prev = last_picked_up;

    // new current cup
    _current = next(_current);
}

void CupList::print_helper(std::ostream& out, int label) const
{
    if (label == _current)
        out << '(';
    out << label;
    if (label == _current)
        out << ')';
    out << ' ';
}

// prints count (or all if count=0) cups starting at start (or initial if start=0)
void CupList::print_list(std::ostream& out, int start, int count) const
{
    start = (start == 0) ? _initial : start;
    print_helper(out, start);
    for (int label = _cup[start].next; label != start && --count != 0; label = _cup[label].next) {
        print_helper(out, label);
    }
}

std::ostream& operator<<(std::ostream& out, const CupList& rhs)
{
    rhs.print_list(out, 0);
    return out;
}