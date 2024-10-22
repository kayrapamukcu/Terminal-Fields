#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Window/Keyboard.hpp>

#include "Menu.hpp"

class MainMenu {
   public:
    static void mainMenuInit();
    static void mainMenuHandler(sf::Keyboard::Key key);
    static int cursorLocation;
    static bool inSubMenu;  // awful
    static Menu menu;

   private:
};

#endif