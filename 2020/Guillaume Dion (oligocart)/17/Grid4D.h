#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>

struct Coord4D
{
    Coord4D(int _x, int _y, int _z, int _w) : x{_x}, y{_y}, z{_z}, w{_w} { }
    bool operator<(const Coord4D& rhs) const { return w < rhs.w || (w == rhs.w && z < rhs.z) || (w == rhs.w && z == rhs.z && y < rhs.y) || (w == rhs.w && z == rhs.z && y == rhs.y && x < rhs.x); }

    std::vector<Coord4D> neighbors() const;

    int x;
    int y;
    int z;
    int w;
};

class Grid4D
{
public:
    Grid4D(const std::vector<std::string>& w0z0_plane);
    void update();
    std::pair<Coord4D, Coord4D> get_frame() const;
    int active_cubes() const { return _grid.size(); }

    friend std::ostream& operator<<(std::ostream& out, const Grid4D& rhs);

private:
    std::set<Coord4D> _grid{};
};
