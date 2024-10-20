#pragma once
#ifndef MAIN_H
#define MAIN_H
#include <SFML/Graphics.hpp>
#include "NewsTicker.hpp"
#include "Player.hpp"
#include <memory>

static const sf::Color defaultColor(170, 170, 170);

class Main {
public:
	static constexpr int FIELD_WIDTH = 100;
	static constexpr int FIELD_HEIGHT = 50;
	static constexpr int TILE_WIDTH = 8;
	static constexpr int TILE_HEIGHT = 12;
	static constexpr int TRANSITION_VARIETY = 13;
	static constexpr auto GAME_VERSION = "alpha 0.1.2-dev";
	static constexpr bool VSYNC = true;
	static int currentZone;
	static bool quit;
	static bool renderTerminalBuffer;
	static int gameState;
	static char terminal[FIELD_HEIGHT][FIELD_WIDTH];
	static bool terminalBuffer[FIELD_HEIGHT][FIELD_WIDTH];
	static sf::Color terminalColor[FIELD_HEIGHT][FIELD_WIDTH];
	static NewsTicker ticker;
	static Player player;
private:
	
};
#endif



