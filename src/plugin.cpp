/**
 * @file plugin.cpp
 * @brief The main file of the plugin
 */

#include <llapi/LoggerAPI.h>

#include "version.h"
#include <string>
#include <vector>

#include <llapi/MC/ItemStack.hpp>
#include <llapi/MC/Level.hpp>
#include <llapi/MC/Player.hpp>
#include <llapi/mc/Types.hpp>
#include <llapi/mc/Block.hpp>
#include <llapi/mc/BlockInstance.hpp>
#include <llapi/mc/Container.hpp>

#include <llapi/EventAPI.h>
#include <llapi/GlobalServiceAPI.h>
#include <llapi/FormUI.h>
#include <llapi/DynamicCommandAPI.h>

#include "tesMainClass.hpp"
// We recommend using the global logger.
extern Logger logger;
std::string latest_player_xuid;

/**
 * @brief The entrypoint of the plugin. DO NOT remove or rename this function.
 *        
 */
void PluginInit()
{
    // Your code here
    Logger logger(PLUGIN_NAME);
    logger.info("Hello, world!");

    Event::PlayerJoinEvent::subscribe([](const Event::PlayerJoinEvent& event) {
        auto* item = ItemStack::create("minecraft:diamond_hoe",1);
        item->setCustomName("Tool Stick");
        /*std::vector<std::string> lore;
        lore[0] = "Click Something to...?";
        item->setLore(lore);*/
        event.mPlayer->giveItem(item);
        delete item;
        return true;
    });

    Event::PlayerStartDestroyBlockEvent::subscribe([](const Event::PlayerStartDestroyBlockEvent& event){
        event.mPlayer->sendText(event.mPlayer->getSelectedItem().getTypeName());
        auto item = event.mPlayer->getSelectedItem();
        BlockInstance block = event.mBlockInstance;
        event.mPlayer->sendText(std::to_string(item.getId()));
        if (item.getId() == 311 /* id of wooden axe. why different to wiki??*/){
            tesShopManager::getInstance().blockClickByAxeEvent(event);
            event.mPlayer->sendText("Axe");
            Form::CustomForm form("test title");
            form.addLabel("label1", "Personal Information")
            .addInput("username", "Your Name")
            .addDropdown("sex", "Your Sex", { "Male","Female","Secret" })
            .addSlider("age", "Your Age", 3, 100)
            .addLabel("label2", "MC Information")
            .addToggle("licensed", "Purchased a licensed Minecraft?", true)
            .addStepSlider("skill", "Skill Lvl", { "Beginner", "Amateur", "Pro" })
            .sendTo(event.mPlayer,[](Player* player, auto result){
                    if (result.empty())
                        return;
                    player->sendText("You have commited the form.");
                    player->sendFormattedText("Your name: {}", result["username"]->getString());
                    player->sendFormattedText("Your sex: {}", result["sex"]->getString());
                    player->sendFormattedText("Your age: {}", result["age"]->getInt());
                    player->sendFormattedText("Your license: {}", result["licensed"]->getBool() ? "yes" : "no");
                    player->sendFormattedText("Your skill level: {}:", result["skill"]->getString());
            });
        }
        return true;
    });



    Event::BlockPlacedByPlayerEvent::subscribe([](const Event::BlockPlacedByPlayerEvent& event) {
        BlockInstance blockInstance = event.mBlockInstance;
        event.mPlayer->sendText(std::to_string(blockInstance.getBlock()->getId()));
        tesShopManager::getInstance().blockPlacedByPlayerEvent(event);
        return true;
    });
    Event::PlayerPlaceBlockEvent::subscribe([](const Event::PlayerPlaceBlockEvent& event) {
        tesShopManager::getInstance().playerPlaceBlockEvent(event);
        tesMainClass::getInstance();
        return true;
    });

    Event::PlayerDestroyBlockEvent::subscribe([](const Event::PlayerDestroyBlockEvent& event){
        if (event.mPlayer->isOP()){ //please fix here; this line is easy to hacking by OP hack 
            return true;
        }

        BlockInstance block = event.mBlockInstance;
        if (block.getDimensionId() ==  0/* enter id of the end */){
            return false;
        }

        //----land and dominion----//
        tesMainClass main = tesMainClass::getInstance();
        auto dominion = main.getDominion(block.getPosition().x,block.getPosition().z);
        if (!dominion){
            return true;    //そもそも国の領土じゃないので管理する必要は無
        }
        //----この下は国の領土----//
        if (dominion.value().getCountryID() != main.getPlayerData(event.mPlayer->getName())->getCountry()) {
            return false;    //部外者なので権限なし
        }

        int land_id = dominion.value().getLandId(block.getPosition().x, block.getPosition().z);

        if (land_id == -1) {
            return true;    //私有地でないのでままええわ（国によって設定できるようにすべき？どっちでもいいか）
        }
        if (dominion.value().getLand(land_id).canUse(event.mPlayer->getName())) {
            return true;    //国の領土かつ、自分が持っている私有地
        } else {
            return false;    //国の領土かつ、自分の私有地でない
        }
    });

    Event::BlockPlacedByPlayerEvent::subscribe([](const Event::BlockPlacedByPlayerEvent& event){
        if (event.mPlayer->isOP()){ //please fix here; this line is easy to hacking by OP hack
            return true;
        }
        BlockInstance block = event.mBlockInstance;
        if (block.getDimensionId() ==  0/* enter id of the end */){
            return false;
        }
//----land and dominion----//
        tesMainClass main = tesMainClass::getInstance();
        auto dominion = main.getDominion(block.getPosition().x,block.getPosition().z);
        if (!dominion){
            return true;    //そもそも国の領土じゃないので管理する必要は無
        }
//----この下は国の領土----//
        if (dominion.value().getCountryID() != main.getPlayerData(event.mPlayer->getName())->getCountry()) {
            return false;    //部外者なので権限なし
        }
        int land_id = dominion.value().getLandId(block.getPosition().x, block.getPosition().z);
        if (land_id == -1) {
            return true;    //私有地でないのでままええわ（国によって設定できるようにすべき？どっちでもいいか）
        }
        if (dominion.value().getLand(land_id).canUse(event.mPlayer->getName())) {
            return true;    //国の領土かつ、自分が持っている私有地
        } else {
            return false;    //国の領土かつ、自分の私有地でない
        }
    });
}
