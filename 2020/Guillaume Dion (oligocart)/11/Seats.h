#pragma once

#include <iostream>
#include <vector>

// Part 1
class Seats
{
public:
    virtual ~Seats() { }

    char state(int row, int col) const { return _seats.at(row * _width + col); }
    int num_occupied() const { return std::count(_seats.cbegin(), _seats.cend(), '#'); }
    virtual int neighbors(int row, int col) const;
    virtual bool update();

    bool operator==(const Seats& rhs) const { return _seats == rhs._seats; }

    friend std::istream& operator>>(std::istream& in, Seats& rhs);
    friend std::ostream& operator<<(std::ostream& out, const Seats& rhs);
    
protected:
    void setstate(int row, int col, char state) { _seats.at(row * _width + col) = state; }

    std::vector<char> _seats{};
    int _width, _height = 0;
};

// Part 2
class Seats_v2 : public Seats
{
public:
    int neighbors(int row, int col) const override;
    bool update() override;
};
