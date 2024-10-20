#pragma once
#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include "Main.hpp"
#include <memory>

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
    static Enemy getRandomEnemy();
    //custom behavior for each enemy
    virtual void behavior();
    virtual std::string getArt();
    virtual ~Enemy() {}
};

class Sik : public Enemy {
public:
    Sik() : Enemy("Sik", 9999999, 10000, 750, 100, 0) {}
    std::string getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override{
        Main::ticker.addNews("I am Sik, the king of all Sik...!");
        Player::health -= 50;
    }
};

class Frog : public Enemy {
public:
    Frog() : Enemy("Frog", 25, 10, 2, 1, 0) {}
    std::string getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override{

        Main::ticker.addNews("RIBBIT");
        
    }
};

#endif