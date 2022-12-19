#pragma once
#include <string>
#include <unordered_map>
#include <Nlohmann/json.hpp>


/*
 * BankData
 * Country's Bank Class.
*/
class tesBankData{
public:
    /**
     * add interest for all player.
     */
    void addInterest();

    int getInterestRate() const;
    void setInterestRate(int value);




    std::string getDisplayBalance(const std::string& name);
 
    /** if return false, country/player balance is not enough. **/
    bool depositPlayerMoney(const std::string& name, int value);
    bool withdrawPlayerMoney(const std::string& name, int value);

 

    unsigned long long getBalance(const std::string& name);
    void setBalance(const std::string& name, unsigned long long value);
    void addBalance(const std::string& name, unsigned long long value);

    /**
     * remove money from player.
     * If value is more than balance, balance will be 0.
     * @param player_xuid
     * @param value
    */
    void removeBalance(const std::string& name, unsigned long long value);

    /**
     * Check the player's balance is more than value.
     * @param player_xuid
     * @param value
     * @return
     */
    bool hasBalance(const std::string& name, unsigned long long value);



    unsigned long long convertToRealBalance(unsigned long long value) const;
    unsigned long long convertToRealBalance(double value) const;
    unsigned long long convertFromRealBalance(unsigned long long value) const;


    /**
     * function of RealBalance() are using law value of money.
     * If you need to use decimal value, use this.
     */
    unsigned long long getRealBalance(const std::string& name);
    void addRealBalance(const std::string& name, unsigned long long value);
    void removeRealBalance(const std::string& name, unsigned long long value);
    void setRealBalance(const std::string& name, unsigned long long value);
    bool hasRealBalance(const std::string& name, unsigned long long value);


    unsigned long long getCountryBalance() const;
    bool hasCountryBalance(unsigned long long value) const;
    void addCountryBalance(unsigned long long value);
    void removeCountryBalance(unsigned long long value);
    void setCountryBalance(unsigned long long value);
    const std::string &getCurrencyName() const;

    unsigned int getTotal() const;

   nlohmann::json getAllData() const;


private:
    int InterestRate; //  *(1/10000) した物を利子として
    int Interest_tick;
    unsigned long long county_Balance; // 引き出しのときに減る、要は印刷した紙幣の枠
    std::string country;
    std::unordered_map<std::string ,unsigned long long> money; // *(1/DECIMAL_DIGIT) to Balance

    std::string currencyName; //name of currency


    const int DECIMAL_DIGIT = 1000;
};