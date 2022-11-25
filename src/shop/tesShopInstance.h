//
// Created by folosuru on 2022/11/12.
//
#pragma once
#include <string>
#include <llapi/mc/BlockPos.hpp>

class tesShopInstance {
public:
    tesShopInstance();

    int getPrice() const;
    tesShopInstance setPrice(int value);

    int getCurrency() const;
    tesShopInstance setCurrency(int currency);

    int getAmount() const;
    tesShopInstance setAmount(int amount_);

    bool getActivate() const;
    tesShopInstance setActivate(bool value);

    std::string getChestPos();
    BlockPos getChestBlockPos();


    std::string getSignPos();
    BlockPos getSignBlockPos();

    tesShopInstance setSignPos(std::string SignPos_);


    std::string getOwner();

    tesShopInstance(BlockPos chest_pos_, BlockPos sign_pos_ ,std::string name);

private:
    std::string owner;
    int currency = 0;
    int price = 0;
    int amount = 0;
    bool activate = false;
    std::string chest_pos;
    std::string sign_pos;
    BlockPos chest_block;
    BlockPos sign_block;

};

