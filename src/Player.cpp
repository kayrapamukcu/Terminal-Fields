#include "Player.hpp"
#include "Main.hpp"
#include <string>

int Player::maxHealth = 100;
int Player::health = 100;
int Player::maxMana = 50;
int Player::mana = 50;
int Player::xp = 0;
int Player::xpToLevelUp = 100;
int Player::level = 1;
int Player::gold = 0;
int Player::x = 40;
int Player::y = 25;
int Player::oldX = 40;
int Player::oldY = 25;

//I'm not too sure about the level scaling yet.

int Player::atk = 2;
int Player::def = 2;
int Player::agi = 2;
int Player::mag = 2;
int Player::intell = 2;

int Player::critChance = 10; //percent
float Player::critMult = 1.5f; //multiplier

std::string Player::name = "Player";

void Player::updateLocation() {
	if(Main::terminal[oldY][oldX] != '#') {
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
	Player::atk = 2;
	Player::def = 2;
	Player::agi = 2;
	Player::mag = 2;
	Player::intell = 2;
	Player::critChance = 10;
	Player::critMult = 1.5f;
	Player::name = name;
}

std::string Player::getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
}

void Player::processXP() {
	if (Player::xp >= 100) {
		Player::level++;
		Player::xp -= 100;
	}
}