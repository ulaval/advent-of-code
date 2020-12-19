#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>

struct Coord
{
    Coord(int _x = 0, int _y = 0, int _z = 0) : x{_x}, y{_y}, z{_z} { }
    bool operator<(const Coord& rhs) const { return z < rhs.z || (z == rhs.z && y < rhs.y) || (z == rhs.z && y == rhs.y && x < rhs.x); }

    std::vector<Coord> neighbors() const;

    int x;
    int y;
    int z;
};

class Grid
{
public:
    Grid(const std::vector<std::string>& z0_plane);
    void update();
    std::pair<Coord, Coord> get_frame() const;
    int active_cubes() const { return _grid.size(); }

    friend std::ostream& operator<<(std::ostream& out, const Grid& rhs);

private:
    std::set<Coord> _grid{};
};
