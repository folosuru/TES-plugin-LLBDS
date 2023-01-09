//
// Created by folosuru on 2022/10/19.
//
#pragma once
#include <string>
#include <unordered_map>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/mc/Level.hpp>
#include <llapi/mc/Player.hpp>
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
    
    // function of teleport and hub command
    void setLastPosition(Vec3 pos,int dim);
    Vec3 getLastPosition();
    int getLastDimension();
    void teleportToLastPosition(const std::string& player_name);

    nlohmann::json getAllData();
    tesPlayerData(nlohmann::json data);


private:
    int country;
    std::unordered_map<int,int> money;
    std::array<int,4> last_position{};
};


