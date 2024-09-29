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
	int maxHealth = 200;
    int health = 200;
    int maxMana = 100;
    int mana = 100;
    int xp = 0;
    int level = 1;
    Player(int x, int y, std::string name);
    std::string getArt();
    void updateLocation();
};

#endif