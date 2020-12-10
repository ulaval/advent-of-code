#pragma once

#include <set>
#include <string>
#include <map>

struct Bag
{
    Bag(std::string name = "root bag") : _name{name}, _parents{}, _childs{} { }

    std::string _name;
    std::set<Bag*> _parents;
    std::set<std::pair<Bag*, int>> _childs;
};

class Bags
{
public:
    Bags() : _bags{} { }

    void add_bag(const std::string& name);
    void add_contained_bag(const std::string& container, int count, const std::string& contained_bag);

    const auto& get_bag(const std::string& name) const { return _bags.at(name); }

private:
    std::map<std::string, Bag> _bags;
};
