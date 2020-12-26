#include <cassert>

#include "HexTile.h"

std::istream& operator>>(std::istream& in, Cardinal& rhs)
{
    char ch;
    if (in >> ch) {
        assert(ch == 'n' || ch == 's' || ch == 'e' || ch == 'w');
        int value = ch;
        if (ch == 'n' || ch == 's') {
            char ch2;
            in >> ch2;
            assert(ch2 == 'e' || ch2 == 'w');
            value += ch2;
        }
        rhs = static_cast<Cardinal>(value);
    }
    else {
        in.setstate(std::ios_base::eofbit);
    }
    return in;
}

Direction::Direction(Cardinal cardinal)
 : _x{0.0}, _y{0.0}
{
    switch (cardinal) {
    case Cardinal::E:
        _x = 1.0;
        break;
    case Cardinal::NE:
        _x = 0.5;
        _y = 1.0;
        break;
    case Cardinal::NW:
        _x = -0.5;
        _y = 1.0;
        break;
    case Cardinal::SE:
        _x = 0.5;
        _y = -1.0;
        break;
    case Cardinal::SW:
        _x = -0.5;
        _y = -1.0;
        break;
    case Cardinal::W:
        _x = -1.0;
        break;
    }
}

HexTile& HexTile::operator+=(const Direction& rhs)
{
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

std::set<HexTile> HexTile::adjacent() const
{
    std::set<HexTile> adj;
    HexTile t{*this};
    Cardinal card[] = { Cardinal::E, Cardinal::SW, Cardinal::W, Cardinal::NW, Cardinal::NE, Cardinal::E };
    for (auto c : card) {
        t += c;
        adj.insert(t);
    }
    return adj;
}