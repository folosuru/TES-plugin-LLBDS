//
// Created by folosuru on 2022/11/29.
//

#include "tesExchangeManager.hpp"

void tesExchangeManager::newCurrency(double supply_){
    supply.push_back(supply_);
}

bool tesExchangeManager::exchange(std::string player, int from, int to,unsigned int value) {
    tesMainClass main = tesMainClass::getInstance();
    std::optional<tesBankData> bank_from = main.getBank(from);
    std::optional<tesBankData> bank_to = main.getBank(to);
    if (!bank_from or !bank_to){
        return false;
    }
    if (!bank_from.value().hasBalance(player,value)){
        return false;
    }
    bank_to.value().addBalance(
            player,
            bank_to.value().convertToRealBalance(getRate(from,to) * value)
    );
    bank_from.value().removeBalance(player,value);

    supplyUp(from,value);
    supplyDown(to,getRate(from,to) * value);
    return true;
}

double tesExchangeManager::getExchangeValue(int from,int to,unsigned int value){
    return (value * getRate(from,to));
}

double tesExchangeManager::getRate(int from, int to) {
    double supply_from = supply[from];
    double supply_to = supply[to];
    double x = (std::log(rate_base)/std::log(rate_base * rate_base) * supply_from) - ((std::log(rate_base)/std::log(rate_base * rate_base))*supply_to);
    return std::pow(rate_base,x+supply_from);
}

void tesExchangeManager::supplyUp(int currency,double value){
    supply[currency] += value * supply_convert_rate;
}

void tesExchangeManager::supplyDown(int currency,double value){
    supply[currency] -= value * supply_convert_rate;
}

double tesExchangeManager::getBase(int currency){
    return rate_base + (std::pow(0.98 , tesMainClass::getInstance().getBank(currency)->getTotal()) * 0.001);
}