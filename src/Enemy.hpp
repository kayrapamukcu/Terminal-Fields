#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

class Enemy {
public:
    std::string name;
    int maxHealth;
    int health;
    int maxMana;
    int mana;
    int atk;
    int def;
    int type; //0: earth, 1: water, 2: fire, 3: air

    Enemy(std::string n, int h, int m, int at, int de, int t) {
        name = n;
        maxHealth = h;
        health = h;
        maxMana = m;
        mana = m;
        atk = at;
        def = de;
        type = t;
    }
    std::string getArt();
    static Enemy getRandomEnemy();
    static int getRandomEnemyID();
};

#endif