#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <map>
#include <vector>

class Passport {
    inline static const char* req_v[] = { "byr","iyr","eyr","hgt","hcl","ecl","pid" };
    inline static const char* colors[] = { "amb","blu","brn","gry","grn","hzl","oth" };
    std::map<std::string, std::string> attr_m;

    bool is_number(const std::string_view s) const;
    bool is_hex(const std::string_view s) const;
    bool is_color(const std::string_view s) const { return std::any_of(colors, colors+7, [&](const auto& c) { return s == c; }); }
    bool in_range(const std::string& s, int min, int max) const { return is_number(s) && min <= std::stoi(s) && std::stoi(s) <= max; }
    bool is_year(const std::string& s, int min, int max) const { return s.size() == 4 && in_range(s,min,max); }
    bool is_height(const std::string& s) const;

public:
    void add_attribute(std::string attr) { attr_m.insert ({attr.substr(0,3), attr.substr(4)}); }
    bool is_valid_p1() const { return std::all_of(req_v, req_v+7, [this](const auto& a) { return attr_m.contains(a); }); }
    bool is_valid_p2() const;
};
