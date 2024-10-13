#include "Enemy.hpp"

std::string Enemy::getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
}

Enemy sik("sik", 9999999, 99999, 999, 999, 0);
Enemy frog("Frog", 25, 10, 2, 1, 0);
Enemy lurker("Lurker", 25, 10, 2, 1, 0);

Enemy enemies[2] = { frog, lurker };
Enemy Enemy::getRandomEnemy() {
    return enemies[rand() % 2];
} 

int Enemy::getRandomEnemyID() {
    return rand() % 2;
}

