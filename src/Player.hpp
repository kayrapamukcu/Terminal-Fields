#pragma once

#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    static std::string getName();
    static int getX();
    static int getY();
    static int getLevel();
    static int getXP();
    static int getGold();
    static int getHealth();
    static int getMaxHealth();
    static int getMana();
    static int getMaxMana();

    static int getAtk();
    static int getDef();
    static int getAgi();
    static int getMag();
    static int getIntell();

    static void setX(int x);
    static void setY(int y);
    static void setLevel(int level);
    static void setXP(int xp);
    static void setGold(int gold);
    static void setHealth(int health);
    static void setMaxHealth(int maxHealth);
    static void setMana(int mana);
    static void setMaxMana(int maxMana);

    static void setAtk(int atk);
    static void setDef(int def);
    static void setAgi(int agi);
    static void setMag(int mag);
    static void setIntell(int intell);

    Player(int x, int y, std::string name);
    static std::string getArt();
    static void updateLocation();
private:
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
    static int level;
    static int gold;

    static int atk;
    static int def;
    static int agi;
    static int mag;
    static int intell;

};

#endif