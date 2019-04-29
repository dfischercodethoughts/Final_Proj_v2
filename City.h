//
// Created by JING LU on 2019-04-19.
//

#ifndef CIV_CITY_H
#define CIV_CITY_H
#include "Validator.h"
#include "Tile.h"
#include "Building.h"
#include <vector>
#include <set>

class City {
private:
    enum production_type {
        BUILDING,
        UNIT,
        NONE
    };

    bool ready_to_grow;
    /*
    bool ready_to_produce;
    production_type prod_type;

    Building_Name::names building_in_production;
    Unit::Unit_Type unit_in_production;
     */
    std::string name;
    int production;
    int food;
    int population;
    std::set<Tile *> tiles;
    Tile * home_tile;

    void increment_population();

public:
    //default city does not init tiles or home tile
    City();
    City(City * c);
    explicit City(Tile & home);

    std::string get_name() const;
    void set_name(std::string newname);

    /*
    void clear_build_settings();
    bool is_ready_to_produce() const;
    bool get_ready_to_produce() const;
     */
    bool is_ready_to_grow() const;
    bool get_ready_to_grow() const;

     //std::string get_production_item() const;
     void set_production(int prod);

    int get_production_output() const;
    int get_food_output() const;
    int get_gold_output() const;

    int get_population() const;
    int get_production() const;
    int get_food() const;

    Tile_Output get_output() const;

    std::vector<Tile *> get_tiles();
    void add_tiles(std::vector<Tile*> & to_add);

    std::vector<const Tile *> get_tiles_const() const;

    Tile_Output collect_resources();

    Tile * get_home_tile() const;
    void set_home_tile(Tile & newt);

    bool has_barracks()const;

    //actual building of unit or building done by civilization


    //flips is ready to grow, sets food to zero, and adds given tiles
    void grow(std::vector<Tile *> tiles);

    void draw_on_viewport(Square sq);


    /******************************************************************************************
     * operators
     */
     City & operator=(const City & rhs);

     /**
      * outputs CITY
      *             name
      *             production
      *             food
      *             population
      *             home_tile_id
      *             is_ready_to_grow
      *      Note that this does not populate the cities tiles, but fills it with placeholders (with the proper id)
      *      game will need to iterate through a civ's cities, and tie them to the map tiles
      * @param outs
      * @param city to print or city to fill
      * @return
      */
     friend std::ostream & operator<<(std::ostream & outs, const City & ct);
     friend std::istream & operator>>(std::istream & ins, City & fill);
};

bool operator==(const City & lhs, const City & rhs);
bool operator!=(const City & lhs, const City & rhs);
#endif //CIV_CITY_H
