#include <string>
#include <unordered_map>
#include <vector>
#pragma once
class tesCountryData{
public:
    std::vector<int> aspect_currency_list;


private:
    std::unordered_map<int ,std::unordered_map<char, char>> player; //player[XUID][type] = int
    const int TES_COUNTRY_DATA_ROLE = 1;

};