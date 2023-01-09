#include <string>
#include <unordered_map>
#include <vector>
#pragma once
class tesCountryData{
public:
    std::vector<int> aspect_currency_list;
    int getRole(std::string player);

private:
    std::unordered_map<std::string ,std::unordered_map<char, char>> player; //player[name][type] = int
    const int TES_COUNTRY_DATA_ROLE = 1;

};