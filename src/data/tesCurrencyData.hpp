#include <string>
#pragma once

class tesCurrencyData {
public:

tesBankData getBank();
std::string getCurrencyName();

private:
    std::string currency_name;
    int country_id;
    tesBankData Bank;

};
