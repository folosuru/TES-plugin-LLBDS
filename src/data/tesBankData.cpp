#include "tesBankData.hpp"
#include <string>
#include <utility>
#include <climits>

using namespace std;


unsigned long long tesBankData::convertToRealBalance(unsigned long long value) const{
    return value*DECIMAL_DIGIT;
}
unsigned long long tesBankData::convertFromRealBalance(unsigned long long value) const{
    return value/DECIMAL_DIGIT;
}
unsigned long long tesBankData::convertToRealBalance(double value) const {
    return (unsigned long long)(value * DECIMAL_DIGIT);
}

/* 
 * Add interest for all player.
*/
void tesBankData::addInterest() {
    for (const auto& value : money){
        addRealBalance(value.first, (int) ((float) getRealBalance(value.first) * (float) getInterestRate() / 10000));
    }
}

int tesBankData::getInterestRate() const {
    return InterestRate;
}

void tesBankData::setInterestRate(int value){
    InterestRate = value;
}

/** Country Blance **/



bool tesBankData::hasCountryBalance(unsigned long long value) const{
    if (getCountryBalance() >= value){
        return true;
    }else{
        return false;
    }
}

void tesBankData::removeCountryBalance(unsigned long long value){
    if (hasCountryBalance(value)){
        setCountryBalance(getCountryBalance() - value);
    }else {
        setCountryBalance(0);
    }
}

unsigned long long tesBankData::getCountryBalance() const{
    return county_Balance;
}


void tesBankData::addCountryBalance(unsigned long long value){
    setCountryBalance(getCountryBalance() + value);
}

void tesBankData::setCountryBalance(unsigned long long value){
    county_Balance = value;
}

/** player Balance... **/

std::string tesBankData::getDisplayBalance(const std::string& name){
    std::string string = std::to_string(getRealBalance(name));
    unsigned int digit = std::to_string(DECIMAL_DIGIT).length();

    for (int i = 0; string.length() <= digit ; i++) {
        string.insert(0,"0");
    }
    string.insert(string.length()-digit,".");

    return string;
}

unsigned long long tesBankData::getBalance(const std::string& name){
    return convertFromRealBalance(getRealBalance(name));
}

void tesBankData::addBalance(const std::string& name, unsigned long long value){
    addRealBalance(name,convertToRealBalance(value));
}

void tesBankData::removeBalance(const std::string& name, unsigned long long value){
    removeRealBalance(name, convertToRealBalance(value));
}

void tesBankData::setBalance(const std::string& name, unsigned long long value){
    setRealBalance(name , convertToRealBalance(value));
}

bool tesBankData::hasBalance(const std::string& name, unsigned long long value){
    return hasRealBalance(name, convertToRealBalance(value));
}

bool tesBankData::depositPlayerMoney(const std::string& name, int value){
    if (hasBalance(name,value)){
        addCountryBalance(value);
        removeBalance(name, value);
        return true;
    } else {
        return false;
    }
}

bool tesBankData::withdrawPlayerMoney(const std::string& name, int value){
    if (hasCountryBalance(value)){
        removeCountryBalance(value);
        addBalance(name, value);
        return true;
    } else {
        return  false;
    }
}

void tesBankData::addRealBalance(const std::string& name, unsigned long long value) {
    setRealBalance(name, getRealBalance(name) + value);
}

unsigned long long tesBankData::getRealBalance(const std::string& name) {
    if (money.find(name) == money.end()){
        money[name] = 0;
    }
    return money[name];
}

void tesBankData::setRealBalance(const std::string& name, unsigned long long value) {
    money[name] = value;
}

bool tesBankData::hasRealBalance(const std::string& name, unsigned long long value) {
    if (getRealBalance(name) >= value){
        return true;
    }else {
        return false;
    }
}

void tesBankData::removeRealBalance(const std::string& name, unsigned long long value){
    if (hasRealBalance(name, value)){
        setRealBalance(name, getRealBalance(name) - value);
    }else{
        setRealBalance(name, 0);
    }
}

const string &tesBankData::getCurrencyName() const {
    return currencyName;
}

unsigned int tesBankData::getTotal() const{
    unsigned int result = 0;
    for (const auto& player_money:money){
        if (result+ player_money.second > UINT_MAX) {
            break;
        }
        result = result + player_money.second;
    }
    return result;
}

nlohmann::json tesBankData::getAllData() const {
    nlohmann::json data;
    data["interest_rate"] = getInterestRate();
    data["country_balance"] = getCountryBalance();
    data["balance"] = money;
    return data;
}

tesBankData::tesBankData(const nlohmann::json& data) {
    InterestRate = data["interest_rate"].get<int>();
    county_Balance = data["country_balance"].get<unsigned long long >();
    money = data["balance"].get<std::unordered_map<std::string ,unsigned long long>>();
}


