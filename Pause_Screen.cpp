//
// Created by david on 4/1/2019.
//

#include "Pause_Screen.h"

Pause_Screen::Pause_Screen() {
    return_to_start = Square();
    return_to_game = Square();
    exit = Square();
    message = "";
}

Pause_Screen::Pause_Screen(int h, int w) {
    init(h,w);
}

void Pause_Screen::init(int h, int w) {
    return_to_start = Square({w/2,2*h/8},Colors::RED,Colors::BLACK,h/8,w/4,"RETURN TO START", true);
    return_to_game = Square({w/2,3*h/8},Colors::RED,Colors::BLACK,h/8,w/4,"RETURN TO GAME", true);
    save = Square({w/2,h/2},Colors::RED,Colors::BLACK,h/8,w/4,"SAVE GAME", true);
    load = Square({w/2,5*h/8},Colors::RED,Colors::BLACK,h/8,w/4,"LOAD GAME", true);
    exit = Square({w/2,6*h/8},Colors::RED,Colors::BLACK,h/8,w/4,"EXIT GAME", true);

    message = "PAUSE SCREEN";
}

void Pause_Screen::draw() {
    Square(return_to_game.get_center(),Colors::WHITE,return_to_game.get_center().y * 2,return_to_game.get_center().x * 2,true);
    save.draw();
    load.draw();
    return_to_game.draw();
    return_to_start.draw();
    exit.draw();

    glColor3f(0,0,0);
    glRasterPos2i(return_to_start.get_center().x,return_to_start.get_center().y/2);
    for (char c : message) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,c);
    }


}


Screen::names Pause_Screen::get_type() const {
    return Screen::PAUSE_SCREEN;
}

Screen::menu_options Pause_Screen::check_click(Coordinate click) {
    if (return_to_game.check_click(click)) {
        return Screen::RETURN_TO_GAME;
    }
    else if (return_to_start.check_click(click)) {
        return Screen::RETURN_TO_START;
    }
    else if (exit.check_click(click)) {
        return Screen::EXIT_GAME;
    }
    else if (save.check_click(click)) {
        return Screen::SAVE_GAME;
    }
    else if (load.check_click(click)) {
        return Screen::LOAD_GAME;
    }

    return Screen::NONE;
}

Pause_Screen::~Pause_Screen() {
    return_to_start = Square();
    return_to_game = Square();
    exit = Square();
    message = "";
}