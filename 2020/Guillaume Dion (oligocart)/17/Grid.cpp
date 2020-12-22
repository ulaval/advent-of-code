#include <sstream>

#include "Grid.h"

std::vector<Coord> Coord::neighbors() const
{
    std::vector<Coord> coords;
    for (int _x=x-1; _x<=x+1; _x++) {
        for (int _y=y-1; _y<=y+1; _y++) {
            for (int _z=z-1; _z<=z+1; _z++) {
                if (_x != x || _y != y || _z != z)
                    coords.push_back(Coord{_x,_y,_z});
            }
        }
    }
    return coords;
}

Grid::Grid(const std::vector<std::string>& z0_plane)
{
    for (int y=0; y < z0_plane.size(); y++) {
        const auto& row = z0_plane[y];
        for (int x=0; x < row.size(); x++) {
            if (row[x] == '#') {
                _grid.insert(Coord{x, y, 0});
            }
        }
    }
}

void Grid::update()
{
    Grid copy{*this};

    auto [min, max] = copy.get_frame();

    // consider one less and one more in every direction...
    for (int z=min.z-1; z <= max.z+1; z++) {
        for (int y=min.y-1; y <= max.y+1; y++) {
            for (int x=min.x-1; x <= max.x+1; x++) {
                Coord coord{x,y,z};
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

std::pair<Coord, Coord> Grid::get_frame() const
{
    // Calcule les x,y,z minimums et maximums de la Grid
    auto it = _grid.cbegin();
    Coord min{ it->x, it->y, it->z };
    Coord max{ min };
    while (++it != _grid.cend()) {
        min.x = std::min(min.x, it->x);
        min.y = std::min(min.y, it->y);
        min.z = std::min(min.z, it->z);
        max.x = std::max(max.x, it->x);
        max.y = std::max(max.y, it->y);
        max.z = std::max(max.z, it->z);
    }
    return std::make_pair(min, max);
}

std::ostream& operator<<(std::ostream& out, const Grid& rhs)
{
    auto [min, max] = rhs.get_frame();
    std::ostringstream oss;
    for (int z=min.z; z <= max.z; z++) {
        oss << "z=" << z << '\n';
        for (int y=min.y; y <= max.y; y++) {
            for (int x=min.x; x <= max.x; x++) {
                if (rhs._grid.contains(Coord{x,y,z}))
                    oss << '#';
                else
                    oss << '.';
            }
            oss << '\n';
        }
        oss << '\n';
    }
    out << oss.str();
    return out;
}