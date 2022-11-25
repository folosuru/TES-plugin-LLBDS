#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <optional>
#include "data/tesDominionData.h"
#include "data/tesPlayerData.h"
#include "data/tesCountryData.h"
#include "data/tesBankData.h"
#include "data/tesCurrencyData.h"
#include "shop/tesShopManager.h"

class tesShopManager;

class tesMainClass {
public:
    static tesMainClass getInstance();
    bool existsPlayerData(const std::string& name);
    tesPlayerData getPlayerData(const std::string& name);
    std::optional<tesCountryData> getCountry(int id);
    tesCurrencyData getCurrency(int id);
    int getCurrencyID(std::string name);
    std::optional<tesDominionData> getDominion(int x,int z);

private:
    std::unordered_map<std::string ,tesPlayerData> player_data;
    std::unordered_map<int,tesCountryData> country_data; //note: country_id = 0 means country not exists
    std::unordered_map<int,tesCurrencyData> currency_data;
    std::unordered_map<std::string ,int> currency_name_to_id;
    tesMainClass();
    std::unordered_map<int,tesBankData> bank_data;
    std::unordered_map<int,std::unordered_map<int,tesDominionData>> dominion;
};