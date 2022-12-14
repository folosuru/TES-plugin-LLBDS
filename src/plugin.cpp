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

#include <llapi/MC/CommandOrigin.hpp>
#include <llapi/MC/CommandOutput.hpp>

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
        auto main = tesMainClass::getInstance();
        if (main.getPlayerData(event.mPlayer->getName())){
            return true;
        }
        event.mPlayer->teleport(Vec3(0,128,0),0);
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
        auto dominion = main.getDominionByPos(block.getPosition().x,block.getPosition().z);
        if (!dominion){
            return true;    //??????????????????????????????????????????????????????????????????
        }
        //----????????????????????????----//
        if (dominion.value().getCountryID() != main.getPlayerData(event.mPlayer->getName())->getCountry()) {
            return false;    //??????????????????????????????
        }

        int land_id = dominion.value().getLandId(block.getPosition().x, block.getPosition().z);

        if (land_id == -1) {
            return true;    //????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
        }
        if (dominion.value().getLand(land_id).canUse(event.mPlayer->getName())) {
            return true;    //??????????????????????????????????????????????????????
        } else {
            return false;    //????????????????????????????????????????????????
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
        auto dominion = main.getDominionByPos(block.getPosition().x,block.getPosition().z);
        if (!dominion){
            return true;    //??????????????????????????????????????????????????????????????????
        }
//----????????????????????????----//
        if (dominion.value().getCountryID() != main.getPlayerData(event.mPlayer->getName())->getCountry()) {
            return false;    //??????????????????????????????
        }
        int land_id = dominion.value().getLandId(block.getPosition().x, block.getPosition().z);
        if (land_id == -1) {
            return true;    //????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????
        }
        if (dominion.value().getLand(land_id).canUse(event.mPlayer->getName())) {
            return true;    //??????????????????????????????????????????????????????
        } else {
            return false;    //????????????????????????????????????????????????
        }
    });

    DynamicCommand::setup(
        "hub", // The command
        "return to hub.", // The description
        {}, // The enumeration
        {}, // The parameters
        {{},}, // The overloads
        [](
            DynamicCommand const& command,
            CommandOrigin const& origin,
            CommandOutput& output,
            std::unordered_map<std::string, DynamicCommand::Result>& results
        ) {
            
            if (origin.getPlayer() == nullptr){
                output.error("this command only for player");
            }

            auto main = tesMainClass::getInstance();
            auto player = main.getPlayerData(origin.getPlayer()->getName());
            if (player){
                player.value().setLastPosition(origin.getPlayer()->getPosition(),origin.getPlayer()->getDimensionId());
                origin.getPlayer()->teleport(Vec3(0,128,0),2);
            } else {
                output.error("you not registered");
            }
        }// The callback function
    );
}
