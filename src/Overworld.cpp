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

void Overworld::overworldPopulate(int obstacleChance, int enemyChance) {
	auto seed = (255 + overworldX) * (9 * ( 255 + overworldY)) * (gameSeed % 65535);
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dist(1, 100);

    for (int i = 1; i < Main::FIELD_HEIGHT-5; i++) {
        for (int j = 1; j < Main::FIELD_WIDTH-23; j++) {
            if (dist(gen) < obstacleChance) {
                Main::terminal[i][j] = '#';
				if (dist(gen) <= enemyChance) {
					Main::terminal[i][j] = 'E';
					Main::terminalColor[i][j] = sf::Color::Red;
				}
            }
        }
    }
	for (int i = 0; i < Main::FIELD_HEIGHT; i++) {
		Screen::updateTerminal(78, i, "|\x3", false, Main::terminalColor[i][0]);
	}
	std::string screenText = "On screen (" + std::to_string(overworldX) + ", " + std::to_string(overworldY) + ")";
	Main::ticker.addNews(screenText);
}

void Overworld::overworldInit() {
	std::random_device rd;
	Overworld::gameSeed = rd();
	Screen::clearTerminal();
	Screen::clearTerminalColor();
	overworldPopulate(10, 5);
	overworldHandler(sf::Keyboard::Unknown);
	Main::ticker.changeSize(19, Main::FIELD_HEIGHT - 22, 32, 80, 22);
	Main::ticker.addNews("Entered new game!"); 
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
	overworldPopulate(10, 5);
}

bool Overworld::checkCollision(int direction, Player& player) {
	switch (direction) {
	case 0: //up
		if (Main::terminal[player.y - 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y - 1][player.x] == 'E') {
			Screen::transition(0);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 1: //down
		if (Main::terminal[player.y + 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y + 1][player.x] == 'E') {
			Screen::transition(0);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 2: //left
		if (Main::terminal[player.y][player.x - 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x-1] == 'E') {
			Screen::transition(0);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 3: //right
		if (Main::terminal[player.y][player.x + 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x+1] == 'E') {
			Screen::transition(0);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	}
	return true;
}

Player player(Main::FIELD_HEIGHT/2, Main::FIELD_HEIGHT/2 + 11, "Kayra");

void Overworld::updateStats(Player& player) {
	std::string statsText = "Hello " + player.name + "! You are currently on screen 0, 0\nX: " + std::to_string(player.x) + " Y: " + std::to_string(player.y) + " HP: " + std::to_string(player.health) + " MP: " + std::to_string(player.mana) + " XP: " + std::to_string(player.xp) + "\x3";
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
	//todo: integrate screen border collision checks into checkCollision
	if (Main::gameState == 1) {
		player.updateLocation();
		Overworld::updateStats(player);
	}
}