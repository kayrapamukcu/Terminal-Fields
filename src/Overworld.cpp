#include "Overworld.hpp"

#include <random>
#include <sstream>
#include <string>
#include <unordered_map>

#include "Battle.hpp"
#include "Main.hpp"
#include "NewsTicker.hpp"
#include "Player.hpp"
#include "Screen.hpp"

int Overworld::gameSeed = 0;
int Overworld::currentZone = 1;
int Overworld::selectedMenu = 0;

float Overworld::obstacleChance = 10.0f;
float Overworld::enemyChance = 1.0f;
float Overworld::chestChance = 0.1f;

int Overworld::overworldX = 0;
int Overworld::overworldY = 0;
int Overworld::monsterCountArray[9]{0};  // 9 screens
int Overworld::chestCountArray[9]{0};

std::unordered_map<Overworld::MonsterKey, bool, Overworld::MonsterKeyHash> Overworld::monsterKilledMap;

bool Overworld::isMonsterKilled(int overworldX, int overworldY, int x, int y) {
    Overworld::MonsterKey key = {overworldX, overworldY, x, y};
    auto it = Overworld::monsterKilledMap.find(key);
    if (it != Overworld::monsterKilledMap.end()) {
        return true;
    }
    return false;
}

void Overworld::updateMinimap() {
    for (int i = 0; i < 9; i++) {
        std::string monsterCount = std::to_string(Overworld::monsterCountArray[i]) + "\x3";
        std::string chestCount = std::to_string(Overworld::chestCountArray[i]) + "\x3";
        Screen::updateTerminal(83 + (i % 3) * 5, 2 + (i / 3) * 4, &monsterCount[0], false, sf::Color::Red);
        Screen::updateTerminal(83 + (i % 3) * 5, 3 + (i / 3) * 4, &chestCount[0], false, sf::Color(150, 150, 0));
    }
}

int Overworld::getScreenSeed(int gameSeed, int overworldX, int overworldY) {
    auto seed = (255 + overworldX) * (9 * (255 + overworldY)) * (gameSeed % 65535);
    return seed;
}

void Overworld::overworldMapCalculator(float obstacleChance, float enemyChance, float chestChance) {
    // to optimize the code, i can asssume obstacleChance is bigger than enemyChance, and enemyChance is bigger than chestChance, and nest some if statements together in the for loop here, but I'm not doing that just yet.

    for (int i = Overworld::overworldX - 1; i < 2; i++) {
        for (int j = Overworld::overworldY - 1; j < 2; j++) {
            auto seed = getScreenSeed(gameSeed, i, j);
            std::mt19937 gen(seed);
            std::uniform_real_distribution<> dist(0, 100);
            for (int k = 1; k < Main::FIELD_HEIGHT - 5; k++) {
                for (int l = 1; l < Main::FIELD_WIDTH - 23; l++) {
                    // if (dist(gen) < obstacleChance) {
                    // }
                    if (dist(gen) <= enemyChance) {
                        monsterCountArray[(i + 1) * 3 + (j + 1)]++;
                    }
                    if (dist(gen) <= chestChance) {
                        chestCountArray[(i + 1) * 3 + (j + 1)]++;
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

    auto seed = (255 + overworldX) * (9 * (255 + overworldY)) * (gameSeed % 65535);
    std::mt19937 gen(seed);
    std::uniform_real_distribution<> dist(0, 100);

    for (int i = 1; i < Main::FIELD_HEIGHT - 5; i++) {
        for (int j = 1; j < Main::FIELD_WIDTH - 23; j++) {
            if (dist(gen) <= obstacleChance) {
                Main::terminal[i][j] = '#';
            }
            if (dist(gen) <= enemyChance) {
                if (!Overworld::isMonsterKilled(overworldX, overworldY, j, i)) {
                    Main::terminal[i][j] = 'E';
                    Main::terminalColor[i][j] = sf::Color::Red;
                }
            }
            if (dist(gen) <= chestChance) {
                Main::terminal[i][j] = 'C';
                Main::terminalColor[i][j] = sf::Color::Yellow;
            }
        }
    }

    Main::ticker.addNews("On screen (" + std::to_string(overworldX) + ", " + std::to_string(overworldY) + ")");

    // place borders
    if (overworldX == -1) {
        for (int i = 0; i < Main::FIELD_HEIGHT - 4; i++) {
            Main::terminal[i][0] = '#';
        }
    } else if (overworldX == 1) {
        for (int i = 0; i < Main::FIELD_HEIGHT - 4; i++) {
            Main::terminal[i][Main::FIELD_WIDTH - 23] = '#';
        }
    }
    if (overworldY == -1) {
        for (int i = 0; i < Main::FIELD_WIDTH - 22; i++) {
            Main::terminal[0][i] = '#';
        }
    } else if (overworldY == 1) {
        for (int i = 0; i < Main::FIELD_WIDTH - 22; i++) {
            Main::terminal[Main::FIELD_HEIGHT - 5][i] = '#';
        }
    }
    // right side stuff
    updateMinimap();
    for (int i = 0; i < Main::FIELD_HEIGHT; i++) {
        Screen::updateTerminal(78, i, "|\x3", false, Main::terminalColor[i][0]);
    }
    for (int i = 26; i < Main::FIELD_HEIGHT; i++) {
        Screen::updateTerminal(99, i, "|\x3", false, Main::terminalColor[i][0]);
    }
    for (int i = 79; i < Main::FIELD_WIDTH; i++) {
        Screen::updateTerminal(i, 25, "-\x3", false, Main::terminalColor[0][i]);
    }
    Screen::updateTerminal(81, Main::FIELD_HEIGHT - 27, "______   _____\x3", false, defaultColor);
    Screen::updateTerminal(80, Main::FIELD_HEIGHT - 26, "|Ticker| |Stats|\x3", false, defaultColor);
    Overworld::processRightMenu(false);
}

void Overworld::overworldInit(std::string playerName, int seed) {
    Overworld::overworldX = 0;
    Overworld::overworldY = 0;
    Overworld::monsterKilledMap.clear();
    std::fill(Overworld::monsterCountArray, Overworld::monsterCountArray + 9, 0);
    std::fill(Overworld::chestCountArray, Overworld::chestCountArray + 9, 0);
    Overworld::currentZone = 1;

    Main::ticker.changeSize(19, Main::FIELD_HEIGHT - 26, 32, 80, 26);
    Main::ticker.addNews("Entered new game!");
    Player::initializePlayer(playerName);
    std::random_device rd;
    Overworld::gameSeed = seed;  // TODO: randomize if no seed entered
    Screen::clearTerminal();
    Screen::clearTerminalColor();
    overworldPopulate(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
    overworldMapCalculator(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
    overworldHandler(sf::Keyboard::Unknown);
}

void Overworld::overworldInitLater() {
    Main::ticker.changeSize(19, Main::FIELD_HEIGHT - 26, 32, 80, 26);
    Screen::clearTerminal();
    Screen::clearTerminalColor();
    overworldPopulate(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
    overworldHandler(sf::Keyboard::Unknown);
}

void Overworld::overworldChangeScreen(int direction) {
    switch (direction) {
        case 0:  // up
            Overworld::overworldY--;
            Player::y = Main::FIELD_HEIGHT - 5;
            break;
        case 1:  // down
            Overworld::overworldY++;
            Player::y = 0;
            break;
        case 2:  // left
            Overworld::overworldX--;
            Player::x = Main::FIELD_WIDTH - 23;
            break;
        case 3:  // right
            Overworld::overworldX++;
            Player::x = 0;
            break;
    }

    Screen::clearTerminalBuffer(true);
    Screen::transition(direction, 0.00008f, false);
    Overworld::overworldPopulate(Overworld::obstacleChance, Overworld::enemyChance, Overworld::chestChance);
    Overworld::updateStats();
    Screen::transition(direction, 0.00008f, true);
}

bool Overworld::checkCollision(int direction) {
    int newY = Player::y;
    int newX = Player::x;
    switch (direction) {
        case 0:
            newY--;
            break;
        case 1:
            newY++;
            break;
        case 2:
            newX--;
            break;
        case 3:
            newX++;
            break;
    }
    if (Main::terminal[newY][newX] == '#') {
        return false;
    } else if (Main::terminal[newY][newX] == 'E') {
        if(selectedMenu == 1) {
            processRightMenu(true);
        }
        Screen::transition(4, 0.0002f, false);
        Main::gameState = 2;
        Battle::battleInit(newX, newY);
        return false;
    }
    return true;
}

void Overworld::updateStats() {
    // bottom text
    std::string statsText = "Hello " + Player::name + "! You are currently on screen (" + std::to_string(overworldX) + "," + std::to_string(overworldY) + ")\nX: " + std::to_string(Player::x) + " Y: " + std::to_string(Player::y) + " XP: " + std::to_string(Player::xp) + "\x3";
    Screen::deleteTerminal(2, Main::FIELD_HEIGHT - 3, 2, Main::FIELD_WIDTH - 24, true);
    Screen::updateTerminal(2, Main::FIELD_HEIGHT - 3, &statsText[0], false, sf::Color(255, 255, 0));
    // health and mana bars
    Screen::renderBarStats(80, 14, Player::health, Player::maxHealth, Player::mana, Player::maxMana, true);
}

void Overworld::processRightMenu(bool change) {
    if(change) {
        if(selectedMenu == 0) {
            selectedMenu = 1;
        } else {
            selectedMenu = 0;
        }
    }
    if (selectedMenu == 1) {
        NewsTicker::renderTicker = false;
        Screen::deleteTerminal(80, Main::FIELD_HEIGHT - 24, 24, 19, true);
        Screen::updateTerminalColor(88, Main::FIELD_HEIGHT - 27, 2, 8, menuSelectedColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 27, 2, 8, defaultColor);
        // render player stats
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 24, "-- Player Stats --\x3", false, sf::Color::White);

        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 22, &("Name: " + Player::name + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 22, 1, 5, menuSelectedColor);

        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 20, &("Level: " + std::to_string(Player::level) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 20, 1, 6, sf::Color::Green);
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 19, &("Gold: " + std::to_string(Player::gold) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 19, 1, 5, sf::Color::Yellow);

        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 17, &("Attack: " + std::to_string(Player::atk) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 17, 1, 7, sf::Color(120, 32, 216));
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 16, &("Defense: " + std::to_string(Player::def) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 16, 1, 8, sf::Color(108, 108, 108));
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 15, &("Agility: " + std::to_string(Player::agi) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 15, 1, 8, sf::Color(144, 196, 216));
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 14, &("Magic: " + std::to_string(Player::mag) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 14, 1, 6, sf::Color(0, 128, 255));
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 13, &("Intelligence: " + std::to_string(Player::intell) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 13, 1, 12, sf::Color(160, 196, 160));

        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 11, &("Crit. Chance: " + std::to_string(Player::critChance) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 11, 1, 12, sf::Color(144, 0, 0));
        std::ostringstream formattedCritMult;
        formattedCritMult << Player::critMult;
        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 10, &("Crit. Multi.: " + formattedCritMult.str() + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 10, 1, 12, sf::Color(192, 0, 0));

        Screen::updateTerminal(80, Main::FIELD_HEIGHT - 8, &("Total XP: " + std::to_string(Player::totalXP+Player::xp) + "\x3")[0], false, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 8, 1, 10, sf::Color(0, 255, 0));
    } else {
        Screen::deleteTerminal(80, Main::FIELD_HEIGHT - 24, 24, 19, true);
        NewsTicker::renderTicker = true;
        Screen::updateTerminalColor(88, Main::FIELD_HEIGHT - 27, 2, 8, defaultColor);
        Screen::updateTerminalColor(80, Main::FIELD_HEIGHT - 27, 2, 8, menuSelectedColor);
    }
}

void Overworld::overworldHandler(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Up:
            if (Overworld::checkCollision(0)) {
                Player::y -= 1;
                if (Player::y < 0) {
                    Overworld::overworldChangeScreen(0);
                }
            }
            break;
        case sf::Keyboard::Down:
            if (Overworld::checkCollision(1)) {
                Player::y += 1;
                if (Player::y > Main::FIELD_HEIGHT - 5) {
                    Overworld::overworldChangeScreen(1);
                }
            }
            break;
        case sf::Keyboard::Left:
            if (Overworld::checkCollision(2)) {
                Player::x -= 1;
                if (Player::x < 0) {
                    Overworld::overworldChangeScreen(2);
                }
            }

            break;
        case sf::Keyboard::Right:
            if (Overworld::checkCollision(3)) {
                Player::x += 1;
                if (Player::x > Main::FIELD_WIDTH - 23) {
                    Overworld::overworldChangeScreen(3);
                }
            }
            break;
        case sf::Keyboard::C:
            processRightMenu(true);
            break;
    }
    if (Main::gameState == 1) {
        Main::player.updateLocation();
        Overworld::updateStats();
    }
}