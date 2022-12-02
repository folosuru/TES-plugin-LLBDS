#pragma once
#include <unordered_map>
#include <string>
#include <fstream>
#include <optional>
#include "data/tesDominionData.hpp"
#include "data/tesPlayerData.hpp"
#include "data/tesCountryData.hpp"
#include "data/tesBankData.hpp"
#include "data/tesCurrencyData.hpp"
#include "shop/tesShopManager.hpp"

class tesShopManager;

class tesMainClass {
public:
    static tesMainClass& getInstance();
    std::optional<tesPlayerData> getPlayerData(const std::string& name);
    std::optional<tesCountryData> getCountry(int id);
    std::optional<std::string> getCurrency(int id);
    std::optional<int> getCurrencyID(const std::string& name);
    std::optional<tesDominionData> getDominion(int x,int z);
    std::optional<tesBankData> getBank(int id);


private:
    std::unordered_map<std::string ,tesPlayerData> player_data;
    std::vector<tesCountryData> country_data;
    std::unordered_map<int,std::string> currency_id_to_name;
    std::unordered_map<std::string ,int> currency_name_to_id;
    tesMainClass();
    std::vector<tesBankData> bank_data;
    std::unordered_map<int,std::unordered_map<int,tesDominionData>> dominion;
};