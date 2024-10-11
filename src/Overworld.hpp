#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <memory>

#include <SFML/Graphics.hpp>
#include "Player.hpp"

class Overworld {
public:
	static float obstacleChance;
	static float enemyChance;
	static float chestChance;
	static int overworldX;
	static int overworldY;
	static int gameSeed;
	static void overworldPopulate(float obstacleChance, float enemyChance, float chestChance);
	static void overworldHandler(sf::Keyboard::Key key);
	static void overworldInit();
	static void overworldChangeScreen(int direction);
	static bool checkCollision(int direction);
	static void updateStats();
	static void updateMinimap();
	static void overworldMapCalculator(float obstacleChance, float enemyChance, float chestChance);
	static int getScreenSeed(int gameSeed, int overworldX, int overworldY);
};

#endif