//
// Created by folosuru on 2022/10/19.
//
#pragma once
#include <string>
#include <unordered_map>
#include <Nlohmann/json.hpp>
#include "llapi/mc/Vec3.hpp"

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

    void setLastPosition(Vec3 pos,int dim);
    Vec3 getLastPosition();
    int getLastDimension();

    nlohmann::json getAllData();


private:
    int country;
    std::vector<int> money;
    std::array<int,4> last_position;
};


