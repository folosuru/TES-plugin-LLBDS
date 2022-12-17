//
// Created by folosuru on 2022/10/19.
//

#include "tesPlayerData.hpp"
#include <string>
#include <utility>
using namespace std;

/*tesPlayerData::tesPlayerData(std::string json) {

}*/
int tesPlayerData::getCountry() const {
    return country;
}

void tesPlayerData::setCountry(int country_id) {
    country = country_id;
}
int tesPlayerData::getMoney(int currency) {
    if (money.size() > currency){
        return money[currency];
    } else {
        money[currency] = 0;
        return 0;
    }
}

bool tesPlayerData::hasMoney(int currency, int value) {
    if (getMoney(currency) >= value){
        return true;
    }else{
        return false;
    }
}


void tesPlayerData::addMoney(int currency, const int value) {
    setMoney(currency,getMoney(currency)+value);
}
/**
 * remove money. money not be under 0.
 * @param currency
 * @param value
 */
void tesPlayerData::removeMoney(int currency, int value) {
    if (hasMoney(currency,value)){
        setMoney(currency,getMoney(currency) - value);
    } else {
        setMoney(currency,0);
    }
}

void tesPlayerData::setMoney(int currency, int value) {
    money[currency] = value;
}

void tesPlayerData::setLastPosition(Vec3 pos,int dim){
    last_position[0] = ((int)pos.x);
    last_position[1] = ((int)pos.y);
    last_position[2] = ((int)pos.z);
    last_position[3] = dim;
}

nlohmann::json tesPlayerData::getAllData() {
    nlohmann::json data;
    data["country"] = getCountry();
    data["money"] = money;

    return data;
}

int tesPlayerData::getLastDimension() {
    return last_position[3];
}

Vec3 tesPlayerData::getLastPosition() {
    return Vec3(last_position[0],last_position[1],last_position[2]);
}

