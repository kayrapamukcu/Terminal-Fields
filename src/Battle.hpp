#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <SFML/Window/Keyboard.hpp>

#include "Menu.hpp"
#include "Player.hpp"

class Battle {
   public:
    static void battleHandler(sf::Keyboard::Key key);
    static void battleInit(int monsterX, int monsterY);
    static void updateDisplays();
    static void pause(int duration, bool skippable);
    static void enemyTurn();
    static void playerDeath();
    static void optionInfo();
    static void manaControl(int val, bool isForPlayer);
    static void healthControl(int val, bool isForPlayer);
    static Menu battleMenu;
    static Menu specialMenu;
   private:
    static int x;
    static int y;
    static bool inSubMenu;  // awful
};

#endif