#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    std::string name;
    int maxHealth;
    int health;
    int attack;
    int defense;
    int type; //0: earth, 1: water, 2: fire, 3: air

    Enemy(std::string n, int h, int atk, int def, int t)
        : name(n), maxHealth(h), health(h), attack(atk), defense(def), type(t) {}

};

#endif