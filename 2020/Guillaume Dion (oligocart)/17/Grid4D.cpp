#include <sstream>

#include "Grid4D.h"

std::vector<Coord4D> Coord4D::neighbors() const
{
    std::vector<Coord4D> coords;
    for (int _w=w-1; _w<=w+1; _w++) {
        for (int _x=x-1; _x<=x+1; _x++) {
            for (int _y=y-1; _y<=y+1; _y++) {
                for (int _z=z-1; _z<=z+1; _z++) {
                    if (_x != x || _y != y || _z != z || _w != w)
                        coords.push_back(Coord4D{_x,_y,_z,_w});
                }
            }
        }
    }
    return coords;
}

Grid4D::Grid4D(const std::vector<std::string>& w0z0_plane)
{
    for (int y=0; y < w0z0_plane.size(); y++) {
        const auto& row = w0z0_plane[y];
        for (int x=0; x < row.size(); x++) {
            if (row[x] == '#') {
                _grid.insert(Coord4D{x, y, 0, 0});
            }
        }
    }
}

void Grid4D::update()
{
    Grid4D copy{*this};

    auto [min, max] = copy.get_frame();

    // consider one less and one more in every direction...
    for (int w=min.w-1; w <= max.w+1; w++) {
        for (int z=min.z-1; z <= max.z+1; z++) {
            for (int y=min.y-1; y <= max.y+1; y++) {
                for (int x=min.x-1; x <= max.x+1; x++) {
                    Coord4D coord{x,y,z,w};
                    auto neighbors = coord.neighbors();
                    auto active_neighbors = 0;
                    for (const auto& c : neighbors) {
                        if (copy._grid.contains(c))
                            active_neighbors++;
                    }
                    if (copy._grid.contains(coord)) {
                        // cube is active
                        if (active_neighbors < 2 || active_neighbors > 3)
                            _grid.erase(coord);
                    }
                    else if (active_neighbors == 3) {
                        _grid.insert(coord);
                    }
                }
            }
        }
    }
}

std::pair<Coord4D, Coord4D> Grid4D::get_frame() const
{
    // Calcule les x,y,z,w minimums et maximums de la Grid4D
    auto it = _grid.cbegin();
    Coord4D min{ it->x, it->y, it->z, it->w };
    Coord4D max{ min };
    while (++it != _grid.cend()) {
        min.x = std::min(min.x, it->x);
        min.y = std::min(min.y, it->y);
        min.z = std::min(min.z, it->z);
        min.w = std::min(min.w, it->w);
        max.x = std::max(max.x, it->x);
        max.y = std::max(max.y, it->y);
        max.z = std::max(max.z, it->z);
        max.w = std::max(max.w, it->w);
    }
    return std::make_pair(min, max);
}

std::ostream& operator<<(std::ostream& out, const Grid4D& rhs)
{
    auto [min, max] = rhs.get_frame();
    std::ostringstream oss;
    for (int w=min.w; w <= max.w; w++) {
        for (int z=min.z; z <= max.z; z++) {
            oss << "z=" << z << ", w=" << w << '\n';
            for (int y=min.y; y <= max.y; y++) {
                for (int x=min.x; x <= max.x; x++) {
                    if (rhs._grid.contains(Coord4D{x,y,z,w}))
                        oss << '#';
                    else
                        oss << '.';
                }
                oss << '\n';
            }
            oss << '\n';
        }
    }
    out << oss.str();
    return out;
}
