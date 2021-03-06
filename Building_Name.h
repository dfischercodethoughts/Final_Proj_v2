//
// Created by willi on 4/19/19.
//

#ifndef CIV_BUILDING_NAME_H
#define CIV_BUILDING_NAME_H

#include <string>

/**
 * basic enum to hold building names, and static methods related to buildings
 */
struct Building_Name {
    enum names {
        FARM,
        MINE,
        HARBOR,
        TRADING_POST,
        WORKSHOP,
        LOGGING_CAMP,
        MARKET,
        BARRACKS,
        NONE
    };

    //returns production cost of building n
    static int get_production_cost(names n);

    //returns a string from the specified building name
    static std::string building_name_to_string(names);

    //returns a Building_Name from the string of a building name
    static names string_to_building_name(std::string name);
};

#endif //CIV_BUILDING_NAME_H
