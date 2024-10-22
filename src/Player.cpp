#include "Player.hpp"

#include <cmath>
#include <string>

#include "Main.hpp"
#include "Battle.hpp"

int Player::maxHealth = 100;
int Player::health = 100;
int Player::maxMana = 50;
int Player::mana = 50;
int Player::xp = 0;
int Player::xpToLevelUp = 100;
int Player::totalXP = 0;
int Player::level = 1;
int Player::gold = 0;
int Player::x = 40;
int Player::y = 25;
int Player::oldX = 40;
int Player::oldY = 25;
int Player::currentStatPoints = 0;

int Player::atk = 5;
int Player::def = 5;
int Player::agi = 5;
int Player::mag = 5;
int Player::intell = 5;

int Player::critChance = 10;    // percent
float Player::critMult = 1.5f;  // multiplier

std::string Player::name = "Player";

void Player::updateLocation() {
    if (Main::terminal[oldY][oldX] != '#') {
        Main::terminal[oldY][oldX] = ' ';
    }
    Main::terminal[y][x] = 'P';
    Main::terminalColor[oldY][oldX] = defaultColor;
    Main::terminalColor[y][x] = sf::Color::Green;
    Player::oldX = Player::x;
    Player::oldY = Player::y;
}

Player::Player(int x, int y, std::string name) {
    this->name = name;
    this->x = x;
    this->y = y;
    oldX = x;
    oldY = y;
    updateLocation();
}

void Player::initializePlayer(std::string name) {
    Player::maxHealth = 100;
    Player::maxMana = 50;
    Player::health = Player::maxHealth;
    Player::mana = Player::maxMana;
    Player::xp = 0;
    Player::level = 1;
    Player::gold = 0;
    Player::x = 40;
    Player::y = 25;
    Player::oldX = 40;
    Player::oldY = 25;
    Player::atk = 5;
    Player::def = 5;
    Player::agi = 5;
    Player::mag = 5;
    Player::intell = 5;
    Player::critChance = 10;
    Player::critMult = 1.5f;
    Player::name = name;
    Player::currentStatPoints = 0;
}

std::string Player::getArt() {
    return "  O\n\\_|_/\n  |\n / \\\x3";
}

void Player::processXP() {
    if (Player::xp >= xpToLevelUp) {
        // level up!
        Player::level++;
        Player::totalXP += Player::xpToLevelUp;
        Player::xp -= xpToLevelUp;
        processXP();
        Player::maxHealth += 16 * pow(Player::level, 1.2);
        Player::maxMana += 4 * pow(Player::level, 1.1);
        Player::atk++;
        Player::def++;
        Player::agi++;
        Player::mag++;
        Player::intell++;
        Player::currentStatPoints += 5;
        Player::health = Player::maxHealth;
        Player::mana = Player::maxMana;
        Main::ticker.addNews("Level up! Reached level " + std::to_string(Player::level) + "!");
        Battle::pause(2000, false);
    }
    Player::xpToLevelUp = 50 + (50 * pow(Player::level, 1.75));
}