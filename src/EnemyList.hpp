#pragma once
#ifndef ENEMYLIST_H
#define ENEMYLIST_H

#include "Enemy.hpp"

const Enemy enemyList[] = {
    Enemy("Lurker", 200, 10, 10, 0),
    Enemy("Flamefiend", 150, 20, 5, 2),
    Enemy("AquaSerpent", 180, 15, 12, 1),
    Enemy("WindReaper", 160, 18, 8, 3)
};

/*Enemy getRandomEnemy() {
    return enemyList[rand() % 4];
}*/

#endif