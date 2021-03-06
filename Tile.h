//
// Created by david on 4/3/2019.
//

#ifndef CIV_TILE_H
#define CIV_TILE_H

#include "Tile_Terrain.h"
#include "Tile_Resource.h"
#include "Piece.h"
#include <memory>
#include "Unit.h"
#include "Building.h"
#include "Tile_Output.h"
#include "Building.h"
#include "Civilization_Name.h"

class City;

/**
 * tile class has a pointer to a city or unit (which are owned by civilization)
 * also has a terrain, resource, and building
 * the building defaults to a building name of none
 */
class Tile : public Piece {
private:
    int id;

    Tile_Terrain::names terrain;
    Tile_Resource::names resource;

    Civilization_Name::Names owner;

    Building building;

    Unit * unit;

    City * city;

    Tile_Output output;

    /**
     * increments tile ouput based on type of terrain and resource
     */
    void init_output();
    //destroys the resource on the tile
    void clear_resource();

public:
    static int num_tiles;


    //inits piece type to tile; increments num tiles and sets id to numtiles
    Tile();
    explicit Tile(Tile * copy);
    Tile(const Tile * cp);
    Tile(const Tile & cp);
    explicit Tile(std::unique_ptr<Tile> tile);
    Tile(std::string ter, std::string res);
    Tile(Tile_Terrain::names ter,Tile_Resource::names res);
    Tile(std::string ter, std::string res, Unit & unit);
    Tile(Tile_Terrain::names ter,Tile_Resource::names res, Unit & unit);
    Tile(Tile_Terrain::names);
    Tile(std::string ter, std::string res, std::shared_ptr<Unit> & unt);
    Tile(Tile_Terrain::names ter,Tile_Resource::names res, std::shared_ptr<Unit> & unt);
    Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res);
    Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,int id);
    Tile(Coordinate cnt, int h, int w, Color fill, Color text, Tile_Terrain::names ter,Tile_Resource::names res,bool vis);

    //constructors use basic init functions
    void init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * newu,bool visible);
    //allows setting of id for file IO
    void init(Tile_Terrain::names ter, Tile_Resource::names res, Unit * newu,bool visible,int id);

    //upon creating a new map, tiles will set their own id in an incremental fashion in the order
    //in which they are created
    static int get_num_tiles();
    static void increment_num_tiles();
    static void init_id();

    //if the tile is owned by a city, it will have its owner property set
    Civilization_Name::Names get_owner() const;
    void set_owner(Civilization_Name::Names no);
    bool has_owner() const;

    //building getters and setters (creates a new building to add to the tile)
    Building get_building() const;
    bool add_building(Building_Name::names bld);
    bool has_building() const;

    //allows interacting with a shallow copy of the base square
    Square get_base_square() const;
    void set_base_square(Square set);

    //allows interacting with cities on the tile
    City * get_city();
    //set city and build city are the same
    void set_city(City & newc);
    void build_city(City & newc);
    bool has_city() const;
    void remove_city();//destroys city

    Tile_Terrain::names get_terrain() const;
    Tile_Resource::names get_resource() const;

    int get_id() const;

    /**clears the unit pointer
     * does not remove the unit from the civilization class
     */
    void clear_unit();
    bool has_unit() const;
    //returns pointer to original unit, hopefully (units are owned by civilizations)
    Unit * get_const_unit() const;
    Unit * get_unit();
    void set_unit(Unit & newu);
    void set_unit(Unit * newu);

    void set_background_square(Square set);

    /**
     * returns shallow copy of tile output property
     * @return
     */
    Tile_Output get_output() const;

    void draw() const override;

    void draw_on_viewport( Square viewport_base) override;

    /**
     * overloaded operators
     */

    /**
     * prints tiles: "TILE\nBASE_SQUARE\nTERRAIN\nRESOURCE\nBUILDING\nID\n"
     * note does NOT ouput unit ( nor square )
     * @throws input error
     * @param outs
     * @param print
     * @return
     */
    friend std::ostream & operator<<(std::ostream & outs, const Tile & print);
    /**
     * input assumes "TILE\n" already read
        input does NOT input base square information (map class should do so
        input does set fill piece_type
        note does NOT input unit
    */
    friend std::istream & operator>>(std::istream & ins, Tile & fill);

     Tile & operator=(const Tile & rhs);

    /**
     * equal operator uses the coordinate to  tiles
     * @param rhs
     * @return
     */
    bool operator==(Tile const & rhs) const;
    bool operator!=(Tile const & rhs) const;
    /**
     * order by id of tiles
     * used to get rid of duplicates in get tiles within range in map
     * @param rhs
     * @return
     */
    bool operator<(const Tile & rhs) const;

    ~Tile();
};


#endif //CIV_TILE_H
