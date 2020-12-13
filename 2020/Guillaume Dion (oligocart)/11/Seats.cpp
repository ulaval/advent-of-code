#include <algorithm>
#include <cassert>
#include <string>
#include <sstream>

#include "Seats.h"

int Seats::neighbors(int row, int col) const
{
    assert(state(row, col) != '.');

    int occupied = 0;
    for (int x = std::max(row-1,0); x <= std::min(row+1,_height-1); x++) {
        for (int y = std::max(col-1,0); y <= std::min(col+1,_width-1); y++) {
            if (state(x, y) == '#')
                occupied++;
        }
    }
    occupied -= (state(row,col) == '#') ? 1 : 0;
    return occupied;
}

bool Seats::update()
{
    Seats copy = *this;
    for (int x = 0; x < _height; x++) {
        for (int y = 0; y < _width; y++) {
            if (copy.state(x, y) == 'L' && copy.neighbors(x, y) == 0)
                setstate(x, y, '#');
            else if (copy.state(x, y) == '#' && copy.neighbors(x, y) >= 4)
                setstate(x, y, 'L');
        }
    }
    return (*this == copy);
}

int Seats_v2::neighbors(int row, int col) const
{
    assert(state(row, col) != '.');

    int x, y;
    int occupied = 0;
    
    // up
    x = row - 1, y = col;
    while (x >= 0 && state(x,y) == '.') x--;
    occupied += (x >= 0 && state(x,y) == '#') ? 1 : 0;
    // down
    x = row + 1, y = col;
    while (x < _height && state(x,y) == '.') x++;
    occupied += (x < _height && state(x,y) == '#') ? 1 : 0;
    // left
    x = row, y = col - 1;
    while (y >= 0 && state(x,y) == '.') y--;
    occupied += (y >= 0 && state(x,y) == '#') ? 1 : 0;
    // right
    x = row, y = col + 1;
    while (y < _width && state(x,y) == '.') y++;
    occupied += (y < _width && state(x,y) == '#') ? 1 : 0;
    // up-left
    x = row - 1, y = col -1;
    while (x >= 0 && y >= 0 && state(x,y) == '.') x--, y--;
    occupied += (x >= 0 && y >= 0 && state(x,y) == '#') ? 1 : 0;
    // up-right
    x = row - 1, y = col + 1;
    while (x >= 0 && y < _width && state(x,y) == '.') x--, y++;
    occupied += (x >= 0 && y < _width && state(x,y) == '#') ? 1 : 0;
    // down-left
    x = row + 1, y = col - 1;
    while (x < _height && y >= 0 && state(x,y) == '.') x++, y--;
    occupied += (x < _height && y >= 0 && state(x,y) == '#') ? 1 : 0;
    // down-right
    x = row + 1, y = col + 1;
    while (x < _height && y < _width && state(x,y) == '.') x++, y++;
    occupied += (x < _height && y < _width && state(x,y) == '#') ? 1 : 0;
    
    return occupied;
}

bool Seats_v2::update()
{
    Seats_v2 copy = *this;
    for (int x = 0; x < _height; x++) {
        for (int y = 0; y < _width; y++) {
            if (copy.state(x, y) == 'L' && copy.neighbors(x, y) == 0)
                setstate(x, y, '#');
            else if (copy.state(x, y) == '#' && copy.neighbors(x, y) >= 5)
                setstate(x, y, 'L');
        }
    }
    return (*this == copy);
}

std::istream& operator>>(std::istream& in, Seats& rhs)
{
    int linecount = 0;
    std::string line;
    while (getline(in, line)) {
        linecount++;
        rhs._width = line.size();
        std::copy(line.cbegin(), line.cend(), std::back_inserter(rhs._seats));
    }
    rhs._height = linecount;
    return in;
}

std::ostream& operator<<(std::ostream& out, const Seats& rhs)
{
    std::ostringstream oss;
    for (int l=0; l<rhs._height; l++) {
        auto it1 = rhs._seats.cbegin()+(l*rhs._width);
        auto it2 = it1 + rhs._width;
        while (it1 != it2) {
            oss << *it1;
            it1++;
        }
        oss << '\n';
    }
    out << oss.str();
    return out;
}