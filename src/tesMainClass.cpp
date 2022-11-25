//
// Created by folosuru on 2022/11/01.
//

#include "tesMainClass.h"
#include "data/tesDominionData.h"

tesMainClass::tesMainClass() {

//    player_data[id] = tesPlayerData(hoge);
}

tesMainClass tesMainClass::getInstance() { //おネットのシングルトンからコピペしてきたから合ってるかは知らない
    static tesMainClass instance;
    return instance;
}

bool tesMainClass::existsPlayerData(const std::string& name) {
    if (player_data.find(name) == player_data.end()) {
        return false;
    }
    return true;
}


tesPlayerData tesMainClass::getPlayerData(const std::string& name) {
    if (player_data.find(name) == player_data.end()) {
        player_data[name] = tesPlayerData();
    }
    return player_data[name];
}

std::optional<tesDominionData> tesMainClass::getDominion(int x, int z) {
    if (dominion.find(x) == dominion.end()) {
        return std::nullopt;
    }
    if (dominion[x].find(z) == dominion[x].end()){
        return std::nullopt;
    }
    return dominion[x][z];
}

std::optional<tesCountryData> tesMainClass::getCountry(int id) {
    if (country_data.find(id) == country_data.end()){
        return std::nullopt;
    }
    return country_data[id];
}
