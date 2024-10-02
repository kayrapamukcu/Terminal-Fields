#include "Player.hpp"
#include <random>
#include "Main.hpp"
#include "Screen.hpp"
#include "Overworld.hpp"
#include <string>
#include "Battle.hpp"
#include "NewsTicker.hpp"

int Overworld::overworldX = 0;
int Overworld::overworldY = 0;
int Overworld::gameSeed = 0;
int monsterCountArray[9]{0}; //9 screens
int chestCountArray[9]{0};

void Overworld::updateMinimap() {
	for (int i = 0; i < 9; i++) {
		std::string monsterCount = std::to_string(monsterCountArray[i]) + "\x3";
		std::string chestCount = std::to_string(chestCountArray[i]) + "\x3";
		Screen::updateTerminal(82 + (i % 3) * 5, 2 + (i / 3) * 4, &monsterCount[0], false, sf::Color::Red);
		Screen::updateTerminal(82 + (i % 3) * 5, 3 + (i / 3) * 4, &chestCount[0], false, sf::Color(150, 150, 0));
	}
}

int Overworld::getScreenSeed(int gameSeed, int overworldX, int overworldY) {
	auto seed = (255 + overworldX) * (9 * ( 255 + overworldY)) * (gameSeed % 65535);
	return seed;
}

void Overworld::overworldMapCalculator(float obstacleChance, float enemyChance, float chestChance) {

	//to optimize the code, i can asssume obstacleChance is bigger than enemyChance, and enemyChance is bigger than chestChance, and nest some if statements together in the for loop here, but I'm not doing that just yet.

	for (int i = Overworld::overworldX - 1; i < 2; i++) {
		for (int j = Overworld::overworldY - 1; j < 2; j++) {
			auto seed = getScreenSeed(gameSeed, i, j);
			std::mt19937 gen(seed);
    		std::uniform_int_distribution<> dist(1, 100);
			for (int k = 1; k < Main::FIELD_HEIGHT-5; k++) {
        		for (int l = 1; l < Main::FIELD_WIDTH-23; l++) {
				//if (dist(gen) < obstacleChance) {
				//}
				if (dist(gen) <= enemyChance) {
						monsterCountArray[(i + 1) * 3 + (j + 1)] ++;
					}
				if (dist(gen) <= chestChance) {
						chestCountArray[(i + 1) * 3 + (j + 1)] ++;
				}
            }
        }
    }
	}
	updateMinimap();
}



void Overworld::overworldPopulate(float obstacleChance, float enemyChance, float chestChance) {
	auto seed = (255 + overworldX) * (9 * ( 255 + overworldY)) * (gameSeed % 65535);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(1, 100);

    for (int i = 1; i < Main::FIELD_HEIGHT-5; i++) {
        for (int j = 1; j < Main::FIELD_WIDTH-23; j++) {
            if (dist(gen) <= obstacleChance) {
                Main::terminal[i][j] = '#';
            }
			if (dist(gen) <= enemyChance) {
				Main::terminal[i][j] = 'E';
				Main::terminalColor[i][j] = sf::Color::Red;
			}
			if (dist(gen) <= chestChance) {
				Main::terminal[i][j] = 'C';
				Main::terminalColor[i][j] = sf::Color::Yellow;
				//ain::terminalColor[i][j] = sf::Color(150, 150, 155);
			}
        }
    }
	for (int i = 0; i < Main::FIELD_HEIGHT; i++) {
		Screen::updateTerminal(78, i, "|\x3", false, Main::terminalColor[i][0]);
	}
	std::string screenText = "On screen (" + std::to_string(overworldX) + ", " + std::to_string(overworldY) + ")";
	Main::ticker.addNews(screenText);

	//check for borders
	if (overworldX == -1) {
		for (int i = 0; i < Main::FIELD_HEIGHT - 4; i++) {
			Main::terminal[i][0] = '#';
		}
	}
	if (overworldX == 1) {
		for (int i = 0; i < Main::FIELD_HEIGHT - 4; i++) {
			Main::terminal[i][Main::FIELD_WIDTH - 23] = '#';
		}	
	}
	if (overworldY == -1) {
		for (int i = 0; i < Main::FIELD_WIDTH - 22; i++) {
			Main::terminal[0][i] = '#';
		}
	}
	if (overworldY == 1) {
		for (int i = 0; i < Main::FIELD_WIDTH - 22; i++) {
			Main::terminal[Main::FIELD_HEIGHT - 5][i] = '#';
		}
	}
	updateMinimap();
}



void Overworld::overworldInit() {
	Main::ticker.changeSize(19, Main::FIELD_HEIGHT - 22, 32, 80, 22);
	Main::ticker.addNews("Entered new game!"); 
	std::random_device rd;
	Overworld::gameSeed = rd();
	Screen::clearTerminal();
	Screen::clearTerminalColor();
	overworldPopulate(10, 5, 5);
	overworldMapCalculator(10, 5, 5);
	overworldHandler(sf::Keyboard::Unknown);
}

void Overworld::overworldChangeScreen(int direction, Player& player) {
	switch (direction) {
	case 0: //up
		Overworld::overworldY--;
		player.y = Main::FIELD_HEIGHT - 5;
		break;
	case 1: //down
		Overworld::overworldY++;
		player.y = 0;
		break;
	case 2: //left
		Overworld::overworldX--;
		player.x = Main::FIELD_WIDTH - 23;
		break;
	case 3: //right
		Overworld::overworldX++;
		player.x = 0;
		break;
	}
	Screen::clearTerminal();
	Screen::clearTerminalColor();
	overworldPopulate(10, 5, 5);
}



bool Overworld::checkCollision(int direction, Player& player) {
	switch (direction) {
	case 0: //up
		if (Main::terminal[player.y - 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y - 1][player.x] == 'E') {
			Screen::transition(3);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 1: //down
		if (Main::terminal[player.y + 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y + 1][player.x] == 'E') {
			Screen::transition(3);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 2: //left
		if (Main::terminal[player.y][player.x - 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x-1] == 'E') {
			Screen::transition(3);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 3: //right
		if (Main::terminal[player.y][player.x + 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x+1] == 'E') {
			Screen::transition(3);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	}
	return true;
}

Player player(Main::FIELD_HEIGHT/2, Main::FIELD_HEIGHT/2 + 11, "Kayra");

void Overworld::updateStats(Player& player) {
	std::string statsText = "Hello " + player.name + "! You are currently on screen (" + std::to_string(overworldX) + "," + std::to_string(overworldY) + ")\nX: " + std::to_string(player.x) + " Y: " + std::to_string(player.y) + " HP: " + std::to_string(player.health) + " MP: " + std::to_string(player.mana) + " XP: " + std::to_string(player.xp) + "\x3";
	char* charStatsText = &statsText[0];
	Screen::deleteTerminal(2, Main::FIELD_HEIGHT - 3, 2, Main::FIELD_WIDTH - 24);
	Screen::updateTerminal(2, Main::FIELD_HEIGHT - 3, charStatsText, false, sf::Color(255, 255, 0));
}

void Overworld::overworldHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		if (Overworld::checkCollision(0, player)) {
			player.y--;
			if (player.y < 0) {
				Overworld::overworldChangeScreen(0, player);
			}
		}
		break;
	case sf::Keyboard::Down:
		if (Overworld::checkCollision(1, player)) {
			player.y++;
			if (player.y > Main::FIELD_HEIGHT - 5) {
				Overworld::overworldChangeScreen(1, player);
			}
		}
		break;
	case sf::Keyboard::Left:
		if (Overworld::checkCollision(2, player)) {
			player.x--;
			if (player.x < 0) {
				Overworld::overworldChangeScreen(2, player);
			}
		}

		break;
	case sf::Keyboard::Right:
		if (Overworld::checkCollision(3, player)) {
			player.x++;
			if (player.x > Main::FIELD_WIDTH - 23) {
				Overworld::overworldChangeScreen(3, player);
			}
		}
		break;
	}
	if (Main::gameState == 1) {
		player.updateLocation();
		Overworld::updateStats(player);
	}
}