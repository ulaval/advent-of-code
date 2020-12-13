#pragma once

struct Coordinates
{
    constexpr Coordinates(int x = 0, int y = 0) : _x{x}, _y{y} { }
    Coordinates& operator+=(const Coordinates& rhs) { 
        _x += rhs._x;
        _y += rhs._y;
        return *this;
    }
    void rotate(const int degrees) {
        static const int sin[] = { 0, 1, 0, -1 };
        static const int cos[] = { 1, 0, -1, 0 };
        Coordinates copy{ *this };
        _x = copy._x * cos[degrees/90] - copy._y * sin[degrees/90];
        _y = copy._x * sin[degrees/90] + copy._y * cos[degrees/90];
    }
    int manathan_distance() const { return std::abs(_x) + std::abs(_y); }
    int _x, _y;
};

Coordinates operator*(int value, const Coordinates& rhs) { return Coordinates(value * rhs._x, value * rhs._y); }
