//
// Created by folosuru on 2022/10/19.
//
#pragma once
#include <string>
#include <unordered_map>
#include <Nlohmann/json.hpp>
class tesPlayerData {
public:

    tesPlayerData() = default;

    int getCountry() const;

    void setCountry(int country_id);

    int getMoney(int currency);

    /**
     * add money to player.
     * @param currency
     * @param value
     */
    void addMoney(int currency,int value);

    /**
     * remove money from player.
     * If value is more than money, money will be 0.
     * @param currency
     * @param value
     */
    void removeMoney(int currency,int value);

    void setMoney(int currency, int value);

    /**
     * Check the player's money is more than value.
     * @param currency
     * @param value
     * @return bool
     */
    bool hasMoney(int currency, int value);

    nlohmann::json getAllData();


private:
    int country;
    std::vector<unsigned int> money;
};


