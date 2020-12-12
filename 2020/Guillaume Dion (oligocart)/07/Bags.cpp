#include <utility>

#include "Bags.h"

void Bags::add_bag(const std::string& name)
{
    if (!_bags.contains(name)) {
        _bags.insert({ name, Bag(name) });
    }
}

void Bags::add_contained_bag(const std::string& container, int count, const std::string& contained_bag)
{
    add_bag(container);
    add_bag(contained_bag);
    _bags[container]._childs.insert(std::make_pair(&_bags[contained_bag], count));
    _bags[contained_bag]._parents.insert(&_bags[container]);
}
