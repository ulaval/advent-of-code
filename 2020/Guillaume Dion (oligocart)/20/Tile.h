#pragma once

#include <iostream>
#include <array>
#include <set>

enum Side { TOP = 0, RIGHT = 1, BOTTOM = 2, LEFT = 3 };

struct Tile
{
    inline static const std::size_t tile_size = 10;
    static unsigned short hashside(const std::string& side);

    int id;
    std::array<unsigned short, 8> sig;
    std::array<std::string, tile_size> image;

    void rotate_left();
    void rotate_180();
    void rotate_right();
    void flip_h();
    void flip_v();

    friend std::istream& operator>>(std::istream& in, Tile& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Tile& rhs);

    friend void swap(Tile& lhs, Tile& rhs);
};

std::set<std::pair<int, int>> generate_tileset(std::size_t sz);

class Image
{
public:
    Image() : _line{} { }
    explicit Image(const std::vector<Tile>& tileset, bool borderless = true);

    friend std::ostream& operator<<(std::ostream& out, const Image& rhs);

    void rotate();
    void flip();
    bool scan();
    std::size_t count_char(char ch) const;

private:
    std::vector<std::string> _line;
};