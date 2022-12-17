//
// Created by folosuru on 2022/11/12.
//

#include "tesShopInstance.hpp"

#include <utility>

tesShopInstance::tesShopInstance(BlockPos chest_pos_, BlockPos sign_pos_ ,std::string name) {
    chest_pos = chest_pos_.toString();
    sign_pos = sign_pos_.toString();
    owner = std::move(name);
    chest_block = chest_pos_;
    sign_block = sign_pos_;
}

int tesShopInstance::getPrice() const {
    return price;
}

tesShopInstance* tesShopInstance::setPrice(int value) {
    price = value;
    return this;
}

std::string tesShopInstance::getOwner() {
    return owner;
}

int tesShopInstance::getCurrency() const {
    return currency;
}
tesShopInstance* tesShopInstance::setCurrency(int currency_) {
    currency = currency_;
    return this;
}

int tesShopInstance::getAmount() const {
    return amount;
}

tesShopInstance* tesShopInstance::setAmount(int amount_) {
    amount = amount_;
    return this;
}

bool tesShopInstance::getActivate() const {
    return activate;
}

tesShopInstance* tesShopInstance::setActivate(bool value) {
    activate = value;
    return this;
}

std::string tesShopInstance::getChestPos() {
    return chest_pos;
}

std::string tesShopInstance::getSignPos() {
    return sign_pos;
}

tesShopInstance* tesShopInstance::setSignPos(std::string SignPos_) {
    sign_pos = std::move(SignPos_);
    return this;
}

BlockPos tesShopInstance::getChestBlockPos() {
    return chest_block;
}

BlockPos tesShopInstance::getSignBlockPos() {
    return sign_block;
}

tesShopInstance::tesShopInstance()  = default;
