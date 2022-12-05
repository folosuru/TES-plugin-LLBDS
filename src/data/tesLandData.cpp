#include "tesLandData.hpp"
#include <algorithm>
#include <utility>
#include <array>

tesLandData::tesLandData(int x1,int z1,int x2,int z2,std::string owner_){
    if (x1 > x2){
        max_x = x1;
        min_x = x2;
    } else {
        max_x = x2;
        min_x = x1;
    }
    if (z1 > z2){
        max_z = z1;
        min_z = z2;
    } else {
        max_z = z2;
        min_z = z1;
    }
    owner = std::move(owner_);
}

bool tesLandData::contain(int x, int z) const{
    return (x >= min_x and x <= max_x and z >= min_z and z <= max_z);
}

bool tesLandData::canUse(const std::string& player){
    if (player == owner or std::find(share_player.begin(),share_player.end(),player) != share_player.end() ){
        return true;
    }else {
        return false;
    }
}

std::array<int,4> tesLandData::getAllPos() {
    return std::array<int,4> {min_x,min_z,max_x,max_z};
}

std::vector<std::string> tesLandData::getAllSharePlayer() {
    return share_player;
}

std::string tesLandData::getOwner() {
    return owner;
}
