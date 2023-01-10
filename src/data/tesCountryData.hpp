#include <string>
#include <unordered_map>
#include <vector>
#pragma once
class tesCountryData{
public:
    std::vector<int> aspect_currency_list;
    role_list getRole(std::string player);

private:
    std::unordered_map<std::string ,std::unordered_map<char, role_list>> player; //player[name][type] = int
    const int TES_COUNTRY_ROLE_CATEGORY = 0;
    enum class role_list {
        all,
        normal,
        none,
    }
};