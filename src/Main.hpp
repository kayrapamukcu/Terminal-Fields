#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>
#include "NewsTicker.hpp"

static const sf::Color defaultColor(170, 170, 170);

class Main {
public:
	static constexpr int FIELD_WIDTH = 100;
	static constexpr int FIELD_HEIGHT = 50;
	static constexpr int TILE_WIDTH = 8;
	static constexpr int TILE_HEIGHT = 12;
	static constexpr int TRANSITION_VARIETY = 13;
	//static constexpr int STAGE_SIZE = 3;
	static constexpr auto GAME_VERSION = "alpha 0.0.8";
	static constexpr bool VSYNC = true;
	static bool quit;
	static int gameState;
	static char terminal[FIELD_HEIGHT][FIELD_WIDTH];
	static sf::Color terminalColor[FIELD_HEIGHT][FIELD_WIDTH];
	static NewsTicker ticker;
private:
	
};




#endif