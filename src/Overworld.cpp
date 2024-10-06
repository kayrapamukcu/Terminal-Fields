#include "Player.hpp"
#include <random>
#include "Main.hpp"
#include "Screen.hpp"
#include "Overworld.hpp"
#include <string>
#include "Battle.hpp"
#include "NewsTicker.hpp"

float Overworld::obstacleChance = 10.0f;
float Overworld::enemyChance = 1.0f;
float Overworld::chestChance = 0.1f;

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
    		std::uniform_real_distribution<> dist(0, 100);
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

	Screen::clearTerminal();
	Screen::clearTerminalColor();

	auto seed = (255 + overworldX) * (9 * ( 255 + overworldY)) * (gameSeed % 65535);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(0, 100);

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
	overworldPopulate(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
	overworldMapCalculator(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
	overworldHandler(sf::Keyboard::Unknown);
}

void Overworld::overworldChangeScreen(int direction, Player& player) {
	switch (direction) {
		//try making all these switch cases better
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
	
	Screen::clearTerminalBuffer(true);
	Screen::transition(direction, 0.00008f, false);
	Overworld::overworldPopulate(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
	Overworld::updateStats(player);
	Screen::transition(direction, 0.00008f, true);
}

bool Overworld::checkCollision(int direction, Player& player) {
	switch (direction) {
	case 0: //up
		if (Main::terminal[player.y - 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y - 1][player.x] == 'E') {
			Screen::transition(4, 0.0003f, false);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 1: //down
		if (Main::terminal[player.y + 1][player.x] == '#') {
			return false;
		}
		else if (Main::terminal[player.y + 1][player.x] == 'E') {
			Screen::transition(4, 0.0003f, false);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 2: //left
		if (Main::terminal[player.y][player.x - 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x-1] == 'E') {
			Screen::transition(4, 0.0003f, false);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	case 3: //right
		if (Main::terminal[player.y][player.x + 1] == '#') {
			return false;
		}
		else if (Main::terminal[player.y][player.x+1] == 'E') {
			Screen::transition(4, 0.0003f, false);
			Main::gameState = 2;
			Battle::battleInit(player);
		}
		break;
	}
	return true;
}

Player player(Main::FIELD_HEIGHT/2, Main::FIELD_HEIGHT/2 + 11, "Kayra");

void Overworld::updateStats(Player& player) {
	//bottom text
	std::string statsText = "Hello " + player.name + "! You are currently on screen (" + std::to_string(overworldX) + "," + std::to_string(overworldY) + ")\nX: " + std::to_string(player.x) + " Y: " + std::to_string(player.y) +  " XP: " + std::to_string(player.xp) + "\x3";
	Screen::deleteTerminal(2, Main::FIELD_HEIGHT - 3, 2, Main::FIELD_WIDTH - 24);
	Screen::updateTerminal(2, Main::FIELD_HEIGHT - 3, &statsText[0], false, sf::Color(255, 255, 0));
	//health and mana bars
	char barSize[18];
	for (int i = 0; i < 17; ++i) {
    	barSize[i] = -37;
	} //have to initialize the char array like this otherwise it doesn't work for whatever reason lol (extended ascii is weird)
	barSize[17] = '\x3';
	Screen::updateTerminal(80, 14, "HP\x3", false, sf::Color::Red);
	Screen::updateTerminal(80, 15, barSize, false, sf::Color(96,0,0));
	Screen::updateTerminal(80, 17, "MP\x3", false, sf::Color::Blue);
	Screen::updateTerminal(80, 18, barSize, false, sf::Color(0,0,96));
	int healthToBeFilled = 0;
	int manaToBeFilled = 0;
	float hpPerBlock = static_cast<float>(player.maxHealth) / 17.0f;
	float mpPerBlock = static_cast<float>(player.maxMana) / 17.0f;
	for (int i = 0; i < 15; i++) {
		if (player.health > (static_cast<float>(player.maxHealth) / 17.0f) * i) {
			healthToBeFilled++;
		} else {
			Screen::updateTerminalColor(80+i, 15, 1, 1, sf::Color(96+static_cast<int>(159 * std::fmod(player.health, hpPerBlock) / hpPerBlock),0,0));
			break;
		}
	}
	for (int i = 0; i < 15; i++) {
		if (player.mana > (static_cast<float>(player.maxMana) / 17.0f) * i) {
			manaToBeFilled++;
		} else {
			Screen::updateTerminalColor(80+i, 18, 1, 1, sf::Color(0,0,96+static_cast<int>(159 * std::fmod(player.mana, mpPerBlock) / hpPerBlock)));
			break;
		}
	}
	Screen::updateTerminalColor(80, 15, 1, healthToBeFilled, sf::Color::Red);
	Screen::updateTerminalColor(80, 18, 1, manaToBeFilled, sf::Color::Blue);

	//doing all this so the hp/mana text is right aligned
	std::string statStr = std::to_string(player.health);
	std::string maxStatStr = std::to_string(player.maxHealth);
	std::vector<char>statBar(3+statStr.length()+maxStatStr.length(), ' ');
	int ind = 0;
	for (ind = 0; ind < statStr.length(); ind++) {
		statBar[ind] = statStr[ind];
	}
	statBar[ind] = '/';
	ind ++;
	for (int i = 0; i < maxStatStr.length(); i++) {
		statBar[ind] = maxStatStr[i];
		ind++;
	}
	statBar[ind] = '\x3';
	Screen::updateTerminal(80+(17-ind), 16, &statBar[0], false, sf::Color::Red);
	statStr = std::to_string(player.mana);
	maxStatStr = std::to_string(player.maxMana);
	statBar = std::vector<char>(3+statStr.length()+maxStatStr.length(), ' ');
	ind = 0;
	for (ind = 0; ind < statStr.length(); ind++) {
		statBar[ind] = statStr[ind];
	}
	statBar[ind] = '/';
	ind ++;
	for (int i = 0; i < maxStatStr.length(); i++) {
		statBar[ind] = maxStatStr[i];
		ind++;
	}
	statBar[ind] = '\x3';
	Screen::updateTerminal(80+(17-ind), 19, &statBar[0], false, sf::Color::Blue);
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