#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Overworld {
public:
	static int overworldX;
	static int overworldY;
	static int gameSeed;
	static void overworldPopulate(int obstacleChance, int enemyChance);
	static void overworldHandler(sf::Keyboard::Key key);
	void overworldPopulate(int obstacleChance, int enemyChance, int gameSeed);
	static void overworldInit();
	static void overworldChangeScreen(int direction, Player& player);
	static void overworldChangeScreen(int direction);
	static bool checkCollision(int direction, Player& player);
	static void updateStats(Player& player);
};

#endif