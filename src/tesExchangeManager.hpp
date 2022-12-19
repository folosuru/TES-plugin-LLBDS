//
// Created by folosuru on 2022/11/29.
//
#pragma once
#include "tesMainClass.hpp"
#include <vector>

class tesExchangeManager {
public:
    // In this file,param of 'from' and 'to' means currency id.

    void newCurrency(double supply_ = 1.0);

    /**
     * @param player player's name.
     * exchange("folosuru",jpy,usd,100) means...
     * player lost 100JPY and player will get (100*rate)USD.
     */
    bool exchange(std::string player,int from,int to,unsigned int value);


    /**
     * @param player player's name.
     * exchange_reverse("folosuru",jpy,usd,100) means...
     * player lost (100*rate)JPY and player will get 100USD .
     */
    bool exchange_reverse(std::string player,int from,int to,int value);

    double getExchangeValue(int from,int to,unsigned int value);

    void supplyUp(int currency,double value);
    void supplyDown(int currency,double value);

    /**
     * get rate.
     * if return value of getRate(jpy,usd) is 0.5, you can exchange 100JPY to 50USD.
     */
    double getRate(int from,int to);
    
    /**
     * get base. use sum of bank.
    */
    double getBase(int currency);
private:
    std::vector<double> supply;
    const double rate_base = 1.00001; //rate_base^x+supply
    double supply_convert_rate = 0.001; //need change
};
