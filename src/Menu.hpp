#pragma once
#ifndef MENU_H
#define MENU_H

#include <string>

#include "Main.hpp"

class Menu {
   public:
    std::vector<std::string> buttonNames;
    Menu(int x, int y, int buttonWidth, int spaceBetweenButtons, int cursorOffset, std::vector<std::string> buttonNames);
    void display();
    void handleMovement(int direction);
    int cursorLocation = 0;
    int cursorLocationPrev = 0;
   private:
    int x;
    int y;
    int buttonWidth;
    int spaceBetweenButtons;
    int cursorOffset;
    int buttonCount = 0;
};

#endif