#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    std::string name;
    int x;
    int y;
    int oldX;
    int oldY;
	int maxHealth = 200232;
    int health = 122121;
    int maxMana = 100;
    int mana = 26;
    int xp = 0;
    int level = 1;
    int gold = 0;
    Player(int x, int y, std::string name);
    std::string getArt();
    void updateLocation();
};

#endif