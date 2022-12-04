#include "tesDominionData.hpp"
#include "tesLandData.hpp"
#include <string>
#include <utility>

int tesDominionData::getLandId(int x, int z){
    int i = 0;
    for (auto& land_instance : land){
        if (land_instance.contain(x,z)){
            return i;
        }
        i += 1;
    }
    return -1;
}

tesLandData tesDominionData::getLand(int id){
    return land[id];
}

void tesDominionData::addLand(int x1, int z1, int x2, int z2,std::string player){
    land.emplace_back(x1,z1,x2,z2,std::move(player));
}

int tesDominionData::getCountryID() const {
    return country_id;
}

nlohmann::json tesDominionData::getAllLand() {
    nlohmann::json data;
    int i =0;
    for (auto& land_:land){
        data[std::to_string(i)]["pos"] = land_.getAllPos();
        data[std::to_string(i)]["share"] = land_.getAllSharePlayer();
        data[std::to_string(i)]["owner"] = land_.getOwner();
        i++;
    }
    return data;
}
