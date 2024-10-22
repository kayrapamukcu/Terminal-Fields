#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
   public:
    static std::string name;
    static int x;
    static int y;
    static int oldX;
    static int oldY;
    static int maxHealth;
    static int health;
    static int maxMana;
    static int mana;
    static int xp;
    static int xpToLevelUp;
    static int level;
    static int gold;
    static int totalXP;

    static int atk;
    static int def;
    static int agi;
    static int mag;
    static int intell;

    static int currentStatPoints;

    static int critChance;
    static float critMult;

    Player(int x, int y, std::string name);
    static std::string getArt();
    static void updateLocation();
    static void processXP();
    static void initializePlayer(std::string name);

   private:
};

#endif