//
// Created by folosuru on 2022/11/01.
//

#include "tesMainClass.hpp"
#include "data/tesDominionData.hpp"
#include <fstream>

tesMainClass::tesMainClass() {

//    player_data[id] = tesPlayerData(hoge);
}

tesMainClass& tesMainClass::getInstance() { //おネットのシングルトンからコピペしてきたから合ってるかは知らない
    static tesMainClass instance;
    return instance;
}


std::optional<tesPlayerData> tesMainClass::getPlayerData(const std::string& name) {
    if (player_data.find(name) == player_data.end()) {
        return std::nullopt;
    }else {
        return player_data[name];
    }
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
    if (country_data.size() > id) {
        return country_data[id];
    }
    return std::nullopt;
}

std::optional<std::string> tesMainClass::getCurrency(int id) {
    if (currency_id_to_name.find(id) == currency_id_to_name.end()){
        return std::nullopt;
    }
    return currency_id_to_name[id];
}

std::optional<int> tesMainClass::getCurrencyID(const std::string& name) {
    if (currency_name_to_id.find(name) == currency_name_to_id.end()){
        return std::nullopt;
    }
    return currency_name_to_id[name];
}

std::optional<tesBankData> tesMainClass::getBank(int id){
    if (bank_data.size() > id) {
        return bank_data[id];
    }
    return std::nullopt;
}

void tesMainClass::saveAllPlayerData() {
    for (auto& player: player_data){
        std::ofstream file("plugins/TES-main/player/"+player.first+".json");
        file << std::setw(4)  << player.second.getAllData() << std::endl;
    }
}
