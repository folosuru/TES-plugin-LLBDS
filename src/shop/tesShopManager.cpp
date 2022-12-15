//
// Created by folosuru on 2022/11/07.
//

#include "tesShopManager.hpp"
#include "tesShopInstance.hpp"
#include "llapi/mc/ItemStack.hpp"
#include "../data/tesCountryData.hpp"
#include <llapi/mc/Level.hpp>
#include <llapi/mc/Player.hpp>
#include <string>
#include <utility>


tesShopManager& tesShopManager::getInstance() {
    static tesShopManager instance;
    return instance;
}

void tesShopManager::playerPlaceBlockEvent(const Event::PlayerPlaceBlockEvent& event) {
    BlockInstance block = event.mBlockInstance;
    if (block.hasContainer()) {
        latestEventBlockAbelToBeShop = true;
        latestEventBlockPos = block.getPosition();
        event.mPlayer->sendText("Trueやで");
        return;
    }
    latestEventBlockAbelToBeShop = false;
}

void tesShopManager::blockPlacedByPlayerEvent(const Event::BlockPlacedByPlayerEvent& event) {
    if (latestEventBlockAbelToBeShop){
        event.mPlayer->sendText("shop (chest)");
        bool is_sign = false;
        BlockInstance block = event.mBlockInstance;
        for (int i: SignBlockIdList) {
            event.mPlayer->sendText(std::to_string(i));
            if (block.getBlock()->getId() == i) {
                is_sign = true;
                event.mPlayer->sendText(std::to_string(i) + "true.");
            }
        }
        if (!is_sign) return;
        shop_queue[block.getPosition().toString()]= new tesShopInstance(
                latestEventBlockPos,        //chest
                block.getPosition(),     //sign
                event.mPlayer->getRealName()        //owner
                );
        event.mPlayer->sendText("shop (sign)");
    }else{
        event.mPlayer->sendText("Falseやで");
    }
}

void tesShopManager::blockClickByAxeEvent(const Event::PlayerStartDestroyBlockEvent& event) {
    BlockInstance block = event.mBlockInstance;
    std::string block_position = block.getPosition().toString();
    if (shop_queue.find(block_position) != shop_queue.end()) {
        if (shop_queue[block_position]->getOwner() != event.mPlayer->getRealName()) {
            return;
        }
        tesShopInstance new_shop = *shop_queue[block_position];
        std::vector<std::string> currency_name_list;
        tesMainClass mainClass = tesMainClass::getInstance();

        Form::CustomForm form("SHOP setup");

        std::optional<tesCountryData> country = mainClass.getCountry(
                tesMainClass::getInstance().getDominion((int) block.getPosition().x,
                                                        (int) block.getPosition().z)->getCountryID());
        if (country) {
            std::vector<int> currency_list = country.value().aspect_currency_list;
            std::string currency_name_list_string = "この国での法定通貨は: ";
            for (auto id: currency_list) {
                currency_name_list.push_back(tesMainClass::getInstance().getCurrency(id).value());
                currency_name_list_string += tesMainClass::getInstance().getCurrency(id).value();
                currency_name_list_string += ',';
            }
            form.addLabel("label1", currency_name_list_string);
        } else {
            form.addLabel("label1", "この場所は国家に所属していないためすべての通貨が使用できます...");
        }
        form.addInput("price", "価格", "価格を半角数字で入力……")
                .addInput("currency", "通貨", "通貨を入力...")
                .addInput("amount", "量", "販売量を入力...")
                .sendTo(event.mPlayer,
                        [country, &new_shop](Player *player, auto result) {
                            if (result.empty())
                                return;
                            if (country) { // if place in country, check currency.
                                if (true) {
                                    player->sendText("currency dame");
                                    return;
                                }
                            }
                            if (result["price"]->getInt() <= 0) {
                                player->sendText("Price cannnot be under 0");
                                return;
                            }
                            if (result["amount"]->getInt() <= 0) {
                                player->sendText("Amount cannnot be under 0");
                                return;
                            }

                            new_shop.setPrice(result["price"]->getInt())
                                    .setPrice(
                                            tesMainClass::getInstance().getCurrencyID(result["currency"]->getString()).value())
                                    .setPrice(result["amount"]->getInt())
                                    .setActivate(true);
                            tesShopManager::getInstance().registerShop(new_shop);
                        }
                );
    }
}

void tesShopManager::registerShop(tesShopInstance& shop_){
    shop[shop_.getSignPos()] = shop_;
}

int tesShopManager::canBuy(const std::string& sign,const std::string& player){
    std::optional<tesShopInstance> shopInstance = getShop(sign);
    if (shopInstance){
        if (!tesMainClass::getInstance().getPlayerData(player).value().hasMoney(shopInstance.value().getCurrency(), shopInstance.value().getPrice())){
            return TES_SHOP_BUY_ERROR_MONEY;
        }

        BlockInstance chest = Level::getBlockInstance(shopInstance->getChestBlockPos(), 0); 
        if (!chest.hasContainer()){
            return TES_SHOP_BUY_ERROR_SHOP;
        }

        Container* container = chest.getContainer();
        int item_count = 0;
        for (const ItemStack *item : container->getAllSlots()){
            item_count += item->getCount();
        }
        if (item_count < shopInstance.value().getAmount()){
            return TES_SHOP_BUY_ERROR_STOCK;
        }
        return TES_SHOP_BUY_ABLE;
    }
    return TES_SHOP_BUY_ERROR_STOCK;
}

std::optional<tesShopInstance> tesShopManager::getShop(const std::string& pos){
    if (shop.find(pos) != shop.end()){
        return shop[pos];
    }else {
        return std::nullopt;
    }
}

bool tesShopManager::buy(const std::string& sign,const std::string& player_name){
    if (canBuy(sign,player_name) == TES_SHOP_BUY_ABLE){
        auto chest = Level::getBlockInstance(shop[sign].getChestBlockPos(),0);
        auto container = chest.getContainer();
        int amount = shop[sign].getAmount();
        Player* player = Global<Level>->getPlayer(player_name);
        for (int i=0;i < container->getSize() && amount > 0;i++){ //give item_ to player and remove item_ from chest
            ItemStack* item_ = container->getSlot(i);
            if (item_ == nullptr){
                continue;
            }
            if (amount >= item_->getCount()){
                int count = item_->getCount();
                amount = amount - count;
                player->giveItem(item_->clone_s());
                container->removeItem_s(i, count);
            } else { //amount < item_->getCount()
                player->giveItem(
                        ItemStack::create(item_->getTypeName(), amount)
                );
                container->removeItem_s(i,amount);
                amount = 0;
            }
        }

        tesMainClass::getInstance().getPlayerData(player_name).value().removeMoney(getShop(sign)->getCurrency(),getShop(sign)->getPrice());
        tesMainClass::getInstance().getPlayerData(getShop(sign)->getOwner()).value().addMoney(getShop(sign)->getCurrency(),getShop(sign)->getPrice());
    }else{
        return false;
    }
}


