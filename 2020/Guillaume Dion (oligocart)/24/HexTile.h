#pragma once

#include <iostream>
#include <set>

enum class Cardinal : int { E = 'e', SE = 's'+'e', SW = 's'+'w', W = 'w', NW = 'n'+'w', NE = 'n'+'e' };

std::istream& operator>>(std::istream& in, Cardinal& rhs);

struct Direction
{
    Direction(Cardinal);
    double _x;
    double _y;
};

struct HexTile
{
    HexTile() : _x{0.0}, _y{0.0}, _black{true} { }
    double _x;
    double _y;
    bool _black;

    void flip() { _black = !_black; }
    bool is_black() const { return _black; }
    std::set<HexTile> adjacent() const;

    bool operator<(const HexTile& rhs) const { return _x < rhs._x || (_x == rhs._x && _y < rhs._y); }
    HexTile& operator+=(const Direction& rhs);
};
