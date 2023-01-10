#include "tesCountryData.hpp"

role_list tesCountryData::getRole(std::string name) {
    if (player.find(name) == player.end()){
        return role_list::none;
    } else {
        return player[name][TES_COUNTRY_ROLE_CATEGORY];
    }
}