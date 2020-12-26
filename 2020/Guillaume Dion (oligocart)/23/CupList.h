#pragma once

#include <iostream>
#include <string>
#include <vector>

class CupList;

struct Cup
{
    Cup(CupList* p = nullptr) : plist{p}, label{0}, next_index{0}, prev_index{0} { }
    Cup(CupList* p, int value, int next_i, int prev_i)
        : plist{p}, label{value}, next_index{next_i}, prev_index{prev_i} { }
    
    int label;
    int next_index;
    int prev_index;
    CupList* plist;
};

class CupList
{
public:
    explicit CupList(const std::string& list, bool to_one_million = false);

    const int max_cups;
    constexpr int wrap(int index);

    int next(int from, int n = 1) const;
    int prev(int from, int n = 1) const;
    int find(int label) const;
    void pick_up();
    void put_back();
    void select_dest();
    void move();

    void print_list(std::ostream& out, int from, int count = 0) const;

private:
    void print_helper(std::ostream& out, int index) const;

    std::vector<Cup> _list;
    int picked_up;
    int destination;
    int current;
    int min_label, max_label;
};

std::ostream& operator<<(std::ostream& out, const CupList& rhs);
