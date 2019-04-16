//


// Created by david on 4/3/2019.
//

#include "Main_Screen.h"
Main_Screen::Main_Screen() {
    game = Game();
    next_turn = Square();
    next_phase = Square();
    build_view_port = Square();
    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}

Main_Screen::Main_Screen(int h, int w, int vecx, int vecy) {
    init(h,w,vecx,vecy);
}

void Main_Screen::init(int h, int w) {
    init(h,w,8,8);
}

void Main_Screen::init(int h, int w,int x, int y) {
    set_screen_height(h);
    set_screen_width(w);
    set_center({w/2,h/2});
    game = Game(3*w/4,3*h/4,x,y);

    next_phase = Square({7*w/8,22*h/32},Colors::WHITE,Colors::BLACK,h/12,w/5, "NEXT PHASE",true);//TODO::create a next phase button, update button text with the turn we are on

    build_view_port = Square({3*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/3,"BUILDING MENU",true);

    next_turn = Square({7*w/8,7*h/8},Colors::WHITE,Colors::BLACK,h/4,w/5,"Next Turn",true);
    next_turn.set_x_offset(-25);
    next_turn.set_y_offset(-25);
    game_view_port = Square({3*w/8,3*h/8},Colors::WHITE,3*h/4,3*w/4,false);
    piece_view_port = Square({7*w/8,1*h/8},Colors::WHITE,Colors::BLACK,2*h/8,w/4,"Unit Info",true);
    piece_view_port.set_y_offset(-3*h/16);
    tile_view_port = Square({7*w/8,4*h/8},Colors::WHITE,Colors::BLACK,3*h/16,w/8,"TILE INFO",true);
    tile_view_port.set_y_offset(-3*h/16);
}

void Main_Screen::draw() {
    //TODO:: build draw boxes for other phases

    game_view_port.draw();
    game.get_map().draw();//tiles have references to units, and will draw if visible
    next_turn.draw();
    next_phase.draw();
    game.phase_on_button(next_phase);

    if (game.has_active_unit()) {
        game.get_active_unit()->draw_on_viewport(piece_view_port);
    }
    if (game.has_active_tile()) {
        game.get_active_tile()->draw_on_viewport(tile_view_port);
    }
    if (game.get_phase() == "BUILD"){
        build_view_port.draw();
    }
}

Screen::names Main_Screen::get_type() const {
    return Screen::MAIN_GAME;
}

void Main_Screen::clear_active() {
    game.clear_active_unit();
    game.clear_active_tile();
}

Screen::menu_options Main_Screen::check_click(Coordinate click) {
    if (next_turn.check_click(click)) {
        game.next_turn();
    }
    else if (next_phase.check_click(click) && Turn_Phase::string_to_turn_phase(game.get_phase()) != Turn_Phase::AI_TURN) {
        game.next_phase();
    }
    else {
        switch (Turn_Phase::string_to_turn_phase(game.get_phase())) {
            case (Turn_Phase::MOVE): {
                process_move(click);
                break;
            }

            case (Turn_Phase::BUILD): {
                process_build(click);
                break;
            }
        }
    }

    //todo: implement next phase button, build button, buy button,
}

void Main_Screen::process_move(Coordinate click) {

     if (game.get_active_unit() != nullptr) {
         //only go through this stuff if it's the move phase
         //TODO::fix error where view port only displays tiles to the left and right of it

         Unit *unit = &*game.get_active_unit();
         Tile *tile_clicked = &*game.get_map().get_tile_from_click(click);
         if (unit->get_current_movement() > 0) {
             if (unit->get_unit_type() == Unit::ARCHER) {
                 //get tile and get tiles available to move to with a range of 2
                 if (tile_clicked->has_unit()) {
                     std::vector<Tile *> *tiles_in_range = game.get_map().get_tiles_within_range(
                             game.get_map().get_tile_from_id(game.get_active_unit()->get_location_id()), 2);
                     for (int i = 0; i < tiles_in_range->size(); i++) {
                         if (*((*tiles_in_range)[i]) == *tile_clicked) {
                             //cause archer damage on unit
                             tile_clicked->get_unit()->cause_damage(Unit::ARCHER);
                             break;
                         }
                     }
                 }
             } else if (unit->get_unit_type() == Unit::BOAT) {//is a non archer unit
                 //implement boat move/attack
             } else {
                 //only do stuff if tile selected is right next to tile of unit
                 if (game.get_map().is_adjacent(*tile_clicked,
                                                *game.get_map().get_tile_from_id(unit->get_location_id()))) {
                                                  //set unit to new tile
                     if (game.move_active_unit(*tile_clicked)) {
                         //clear unit from active tile
                         game.get_active_tile()->clear_unit();
                         //redraw active tile
                         game.get_active_tile()->draw();
                         clear_active();
                     }
                 }
             }
         } else {//current unit has no movement left, so clear the selection
             game.clear_active_tile();
             tile_view_port.hide();
             game.clear_active_unit();
             piece_view_port.hide();
         }

     }//end if has active unit, so has no active unit, so set active tile and active unit
     else {
         game.set_active_tile(*game.get_map().get_tile_from_click(click));
         tile_view_port.reveal();
         if (game.get_active_tile_const()->has_unit()) {
             game.set_active_unit(*game.get_map().get_tile_from_click(click)->get_unit());
            piece_view_port.reveal();
         }
     }
}

void Main_Screen::process_build(Coordinate click) {
    /**
     * logic to come
     * in pseudo code
     * if a city is selected and has something to place, then if the click is on the game viewport
     *      and the tile selected is empty of buildings or cities (or enemy units) call the active
     *      city's build function on tile selected (which will check if tile is in range before building)
     * if city is selected and has something to place and click is on the build menu, do nothing (have to
     *      place unit/building to be build before selecting new production)
     * if a city is selected and has nothing to place, then do clear active if click on game viewport.
     *      if click is on the building menu, then switch active city's active production to the item selected
     * if city selected, nothing to place, and click is on build, then switch production to selected item
     */
}

Game* Main_Screen::get_game() {
    return &game;
}

Main_Screen::~Main_Screen() {
    game = Game();
    next_turn = Square();
    next_phase = Square();
    build_view_port = Square();
    game_view_port = Square();
    piece_view_port = Square();
    tile_view_port = Square();
}