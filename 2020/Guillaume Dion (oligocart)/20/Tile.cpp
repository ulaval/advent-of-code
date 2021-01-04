#include <cassert>
#include <bitset>
#include <vector>
#include <sstream>
#include <regex>

#include "Tile.h"

unsigned short Tile::hashside(const std::string& side)
{
    std::bitset<10> bs;
    auto pos = side.size()-1;
    for (const auto ch : side) {
        bs.set(pos--, ch == '#');
    }
    return static_cast<unsigned short>(bs.to_ulong());
}

void Tile::rotate_left()
{
    const auto image_copy{image};
    int line = 0;
    for (int i=Tile::tile_size-1; i >= 0; i--) {
        std::ostringstream oss;
        for (int j=0; j < Tile::tile_size; j++) {
            oss << image_copy[j][i];
        }
        image[line++] = oss.str();
    }
    const auto sig_copy{sig};
    sig[0] = sig_copy[1];
    sig[1] = sig_copy[6];
    sig[2] = sig_copy[3];
    sig[3] = sig_copy[4];
    sig[4] = sig_copy[5];
    sig[5] = sig_copy[2];
    sig[6] = sig_copy[7];
    sig[7] = sig_copy[0];
}

void Tile::rotate_180()
{
    rotate_left();
    rotate_left();
}

void Tile::rotate_right()
{
    rotate_left();
    rotate_left();
    rotate_left();
}

void Tile::flip_h()
{
    for (int i=0; i < Tile::tile_size/2; i++) {
        std::swap(image[i], image[Tile::tile_size-i-1]);
    }
    std::swap(sig[0], sig[2]);
    std::swap(sig[1], sig[5]);
    std::swap(sig[3], sig[7]);
    std::swap(sig[4], sig[6]);
}

void Tile::flip_v()
{
    for (int row=0; row < Tile::tile_size; row++) {
        std::ostringstream oss;
        for (int col=0; col < Tile::tile_size; col++)
            oss << image[row][Tile::tile_size-col-1];
        image[row] = oss.str();
    }
    std::swap(sig[0], sig[4]);
    std::swap(sig[1], sig[3]);
    std::swap(sig[2], sig[6]);
    std::swap(sig[5], sig[7]);
}

std::istream& operator>>(std::istream& in, Tile& rhs)
{
    std::string line;
    in >> line;
    if (line != "Tile") {
        in.setstate(std::ios_base::eofbit);
        return in;
    }
    in >> rhs.id;
    getline(in, line);
    std::vector<std::string> edge(4, std::string{});
    std::ostringstream left, right;
    for (int i=0; i < Tile::tile_size; i++) {
        getline(in, line);
        rhs.image[i] = line;
        if (i == 0)
            edge[0] = line;
        if (i == Tile::tile_size-1)
            edge[2] = line;
        left << line[0];
        right << line[Tile::tile_size-1];
    }
    edge[3] = left.str();
    edge[1] = right.str();
    for (int i=0; i < 4; i++) {
        assert(edge[i].size() == Tile::tile_size);
        rhs.sig[i] = Tile::hashside(edge[i]);
        std::reverse(edge[i].begin(), edge[i].end());
        rhs.sig[i+4] = Tile::hashside(edge[i]);
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Tile& rhs)
{
    out << "Tile #" << rhs.id << " : ";
    out << "top=" << rhs.sig[0] << '/' << rhs.sig[4] << ", ";
    out << "right=" << rhs.sig[1] << '/' << rhs.sig[5] << ", ";
    out << "bottom=" << rhs.sig[2] << '/' << rhs.sig[6] << ", ";
    out << "left=" << rhs.sig[3] << '/' << rhs.sig[7];
    return out;
}

void swap(Tile& lhs, Tile& rhs)
{
    std::swap(lhs.id, rhs.id);
    std::swap(lhs.sig, rhs.sig);
    std::swap(lhs.image, rhs.image);
}

std::set<std::pair<int, int>> generate_tileset(std::size_t sz)
{
    std::set<std::pair<int, int>> tileset{};
    for (int i=0; i < sz; i++) {
        for (int j=0; j < sz; j++)
            tileset.insert(std::make_pair(i, j));
    }
    return tileset;
}

Image::Image(const std::vector<Tile>& tileset, bool borderless)
{
    const std::size_t puzzle_size = static_cast<std::size_t>(std::sqrt(tileset.size()));
    
    for (int row=0; row < puzzle_size; row++) {
        for (int line=0; line < Tile::tile_size; line++) {
            std::ostringstream oss;
            for (int col=0; col < puzzle_size; col++) {
                if (borderless) {
                    if (line > 0 && line < Tile::tile_size-1)
                        oss << tileset[row * puzzle_size + col].image[line].substr(1, Tile::tile_size-2);
                }
                else {
                    oss << tileset[row * puzzle_size + col].image[line] << ' ';
                }
            }
            if (!oss.str().empty())
                _line.push_back(oss.str());
        }
        if (!borderless)
            _line.push_back("\n");
    }
}

void Image::rotate()
{
    static const auto line_size = static_cast<int>(_line.size());
    const auto line_copy{_line};
    int line = 0;
    for (int i=line_size-1; i >= 0; i--) {
        std::ostringstream oss;
        for (int j=0; j < line_size; j++) {
            oss << line_copy[j][i];
        }
        _line[line++] = oss.str();
    }
}

void Image::flip()
{
    static const auto line_size = static_cast<int>(_line.size());
    for (int i=0; i < line_size/2; i++) {
        std::swap(_line[i], _line[line_size-i-1]);
    }
}

bool Image::scan()
{
    static const auto pattern1 = std::regex{"..................#."};
    static const auto pattern2 = std::regex{"#....##....##....###"};
    static const auto pattern3 = std::regex{".#..#..#..#..#..#..."};
    static const auto line_size = static_cast<int>(_line.size());

    // find sea monsters
    std::vector<std::pair<std::size_t, std::size_t>> location;  // (row, col) loc of sea monsters
    for (int i=2; i < line_size; i++) {
        auto matches3 = std::smatch{}, matches2 = std::smatch{};
        auto begin3 = _line[i].cbegin();
        while (std::regex_search(begin3, _line[i].cend(), matches3, pattern3)) {
            auto pos = std::distance(_line[i].cbegin(), matches3[0].first);
            auto len = std::distance(matches3[0].first, matches3[0].second);
            auto begin2 = _line[i-1].cbegin() + pos;
            if (regex_search(begin2, begin2 + len, matches2, pattern2)) {
                if (_line[i-2][pos+18] == '#') {
                    // full sea monster match!
                    location.push_back(std::make_pair(i-2, pos));
                }
            }
            begin3 = matches3[0].first+1;
        }
    }

    // mark sea monsters
    static const int pos1[] = { 18 };
    static const int pos2[] = { 0, 5, 6, 11, 12, 17, 18, 19 };
    static const int pos3[] = { 1, 4, 7, 10, 13, 16 };
    for (const auto [line, offset] : location) {
        for (const auto x : pos1)
            _line[line][offset+x] = 'O';
        for (const auto x : pos2)
            _line[line+1][offset+x] = 'O';
        for (const auto x : pos3)
            _line[line+2][offset+x] = 'O';
    }

    return location.size() > 0;
}

std::size_t Image::count_char(char ch) const
{
    std::size_t count = 0;
    for (const auto& str : _line) {
        count += std::count(str.cbegin(), str.cend(), ch);
    }
    return count;
}

std::ostream& operator<<(std::ostream& out, const Image& rhs)
{
    for (const auto& line : rhs._line) {
        out << line << '\n';
    }
    return out;
}