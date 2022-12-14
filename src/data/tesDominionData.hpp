#pragma once


#include "tesLandData.hpp"
#include <vector>
class tesDominionData{
public:
    int getLandId(int x,int z);    //if land not exists, return -1. 
    tesLandData getLand(int id);

    void addLand(int x1,int z1, int x2 ,int z2,std::string player);
    int getCountryID() const;
    nlohmann::json getAllLand();
    tesDominionData(nlohmann::json data);
    tesDominionData() = default;

private:
    int country_id;
    std::vector<tesLandData> land;
 
};