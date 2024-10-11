#include "Enemy.hpp"

std::string Enemy::getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
}

Enemy frog("Frog", 100, 2, 1, 0);
Enemy sik("sik", 9999999, 999, 999, 0);
Enemy lurker("Lurker", 100, 2, 1, 0);

Enemy enemies[3] = { frog, sik, lurker };
Enemy Enemy::getRandomEnemy() {
    return enemies[rand() % 3];
} 

