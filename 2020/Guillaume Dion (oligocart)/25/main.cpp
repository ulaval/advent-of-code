// AoC 2020-25

#include <cassert>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <numeric>

long long find_loopsize(long long pubkey)
{
    static const long long subject_number = 7;
    static const long long denominator = 20201227;

    long long value = 1;
    long long loops = 1;
    while (true) {
        value *= subject_number;
        value %= denominator;
        if (value == pubkey)
            return loops;
        loops++;
    }
    throw "that is weird!";
}

long long transform(long long subject_number, long long loopsize)
{
    static const long long denominator = 20201227;

    long long value = 1;
    while (loopsize--) {
        value *= subject_number;
        value %= denominator;
    }
    return value;
}

int main(int argc, char* argv[])
{
    const long long card_pubkey = 9033205;
    const long long door_pubkey = 9281649;

    // Part 1
    const auto card_loops = find_loopsize(card_pubkey);
    const auto door_loops = find_loopsize(door_pubkey);
    const auto key1 = transform(door_pubkey, card_loops);
    const auto key2 = transform(card_pubkey, door_loops);
    assert(key1 == key2);
    std::cout << "Part 1 answer = " << key1 << '\n';
}
