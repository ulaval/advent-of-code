// AoC 2020-12

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <map>

#include "Coordinates.h"

int main(int argc, char* argv[])
{
    std::ifstream input_file((argc > 1) ? argv[1] : "input.txt");
    assert(input_file.is_open());

    Coordinates position1, position2;         // default = (0,0)
    std::array<char, 4> compass = { 'E', 'N', 'W', 'S' };       // compass[0] = current direction
    static const std::map<char, Coordinates> way = {
        { 'N', Coordinates(0, 1) }, 
        { 'S', Coordinates(0, -1) }, 
        { 'E', Coordinates(1, 0) }, 
        { 'W', Coordinates(-1, 0) }
    };
    auto waypoint = Coordinates(10, 1);
    static const int sin[] = { 0, 1, 0, -1 };
    static const int cos[] = { 1, 0, -1, 0 };

    int new_x, new_y;
    std::string instruction;
    while (std::getline(input_file, instruction)) {
        char op = instruction[0];
        int value = std::stoi(instruction.substr(1));
        switch (op) {
        case 'F':
            position1 += value * way.at(compass[0]);
            position2 += value * waypoint;
            break;
        case 'N':
        case 'S':
        case 'E':
        case 'W':
            position1 += value * way.at(op);
            waypoint += value * way.at(op);
            break;
        case 'L':
            std::rotate(compass.begin(), compass.begin() + value / 90, compass.end());
            waypoint.rotate(value);
            break;
        case 'R':
            std::rotate(compass.rbegin(), compass.rbegin() + value / 90, compass.rend());
            waypoint.rotate(360 - value);
            break;
        }
    }
    std::cout << "Part 1 answer = " << position1.manathan_distance() << '\n';
    std::cout << "Part 2 answer = " << position2.manathan_distance() << '\n';
}
