//
// Created by folosuru on 2022/11/07.
//
#pragma once
#include <vector>

#include <llapi/mc/BlockPos.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/BlockPos.hpp>
#include <llapi/mc/Container.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/BlockLegacy.hpp>
#include <llapi/mc/SignBlock.hpp>

#include <llapi/EventAPI.h>
#include <llapi/FormUI.h>


#include "../tesMainClass.hpp"
#include "tesShopInstance.hpp"

class CustomForm;

class tesShopManager {
public:

    static tesShopManager& getInstance();
/*
    int getPrice(BlockPos pos);
    int getCurrency(BlockPos pos);
    int getAmount(BlockPos pos);

    void buy(BlockPos pos,Player player);
*/

    void blockClickByAxeEvent(const Event::PlayerStartDestroyBlockEvent& event);

    /**
     * call when PlayerPlaceBlockEvent().
     */
    void playerPlaceBlockEvent(const Event::PlayerPlaceBlockEvent &event);

    /**
     * call when BlockPlacedByPlayerEvent().
     */
    void blockPlacedByPlayerEvent(const Event::BlockPlacedByPlayerEvent& event);

    int canBuy(const std::string& sign,const std::string& player);
    bool buy(const std::string& sign,const std::string& player);

    void registerShop(tesShopInstance& shop);

    std::optional<tesShopInstance> getShop(const std::string& pos);

private:
    std::unordered_map<std::string , tesShopInstance> shop;
    std::unordered_map<std::string , tesShopInstance*> shop_queue;

    bool latestEventBlockAbelToBeShop{};
    BlockPos latestEventBlockPos;

    tesShopManager() = default;
    int SignBlockIdList[12] = {63,68,-181,-182,-186,-187,-188,-189,-190,-191,-192,-193};

    const int TES_SHOP_BUY_ABLE = 0;
    const int TES_SHOP_BUY_ERROR_STOCK = 1; //return when item's stock are less  
    const int TES_SHOP_BUY_ERROR_MONEY = 2; //return when player's money not 
    const int TES_SHOP_BUY_ERROR_PERMISSION = 3; //maybe unuse
    const int TES_SHOP_BUY_ERROR_SHOP = 4; //when not found the chest,or other shop error.    

};

