#include "Enemy.hpp"
#include <functional>
#include <random> 
#include <string>

std::string Enemy::getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
}

void Enemy::behavior() {
    Main::ticker.addNews("Placeholder attack! ZAMN!");
}

