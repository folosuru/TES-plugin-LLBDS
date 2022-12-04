#pragma once

#include <string>
#include <vector>
#include <nlohmann/json.hpp>
class tesLandData{
public:
    bool canUse(const std::string& player);
    void addSharePlayer(const std::string& player);
    bool contain(int x,int z) const;
    tesLandData(int x1,int z1,int x2,int z2,std::string owner_);
    std::array<int,4> getAllPos();
    std::vector<std::string> getAllSharePlayer();

    std::string getOwner();

private:
    int min_x;
    int max_x;
    int min_z;
    int max_z;

    std::string owner;
    std::vector<std::string> share_player;
};