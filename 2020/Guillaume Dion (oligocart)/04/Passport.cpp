#include "Passport.h"

bool Passport::is_number(const std::string_view s) const
{
    return !s.empty() && std::all_of(s.cbegin(), s.cend(), [](auto ch){ return std::isdigit(ch); });
}

bool Passport::is_hex(const std::string_view s) const
{
    return s.size() == 7 && s[0] == '#' && std::all_of(s.cbegin()+1, s.cend(), [](auto ch){ return std::isxdigit(ch); });
}

bool Passport::is_height(const std::string& s) const
{
    return (s.ends_with("cm") && in_range(s.substr(0,3),150,193)) || (s.ends_with("in") && in_range(s.substr(0,2),59,76));
}

bool Passport::is_valid_p2() const
{
    return is_valid_p1()
        && is_year(attr_m.at("byr"),1920,2002)
        && is_year(attr_m.at("iyr"),2010,2020)
        && is_year(attr_m.at("eyr"),2020,2030)
        && is_height(attr_m.at("hgt"))
        && is_hex(attr_m.at("hcl"))
        && is_color(attr_m.at("ecl"))
        && is_number(attr_m.at("pid"))
        && attr_m.at("pid").size() == 9;
}
