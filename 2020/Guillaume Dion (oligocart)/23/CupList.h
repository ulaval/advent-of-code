#pragma once

#include <iostream>
#include <vector>

struct Cup
{
    Cup() : prev{0}, next{0} { }
    int prev;
    int next;
};

class CupList
{
public:
    explicit CupList(const std::string& list, int max_label = 0);

    int wrap(int label) const;
    int prev(int label, int n = 1) const;
    int next(int label, int n = 1) const;
    bool is_picked_up(int label) const;
    void move();

    void print_list(std::ostream& out, int start = 0, int count = 0) const;
    
private:
    void print_helper(std::ostream& out, int label) const;

    std::vector<Cup> _cup;
    int _min;
    int _max;
    int _current;
    int _initial;
    int _picked;
};

std::ostream& operator<<(std::ostream& out, const CupList& rhs);
