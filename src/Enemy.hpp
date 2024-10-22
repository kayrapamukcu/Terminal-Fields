#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>

#include "Battle.hpp"
#include "Main.hpp"

class Enemy {
   public:
    std::string name;
    int maxHealth;
    int health;
    int maxMana;
    int mana;
    int atk;
    int def;
    int type;  // 0: earth, 1: water, 2: fire, 3: air
    int dmg = 0;
    int xpDrop;

    Enemy(std::string n, int h, int m, int at, int de, int xp, int t) {
        name = n;
        maxHealth = h;
        health = h;
        maxMana = m;
        mana = m;
        atk = at;
        def = de;
        type = t;
        xpDrop = xp;
    }
    static Enemy getRandomEnemy();
    // custom behavior for each enemy
    virtual void behavior();
    virtual std::string getArt();
    virtual ~Enemy() {}
    int capNumber(int num, int min, int max) {
        if (num < min) {
            return min;
        } else if (num > max) {
            return max;
        }
        return num;
    }
};

class Sik : public Enemy {
   public:
    Sik() : Enemy("Sik", 9999999, 10000, 750, 100, 999999999, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        Main::ticker.addNews("I am Sik, the king of all Sik...!");
        Player::health -= 50;
    }
};

#endif