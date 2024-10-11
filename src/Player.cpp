#include "Player.hpp"
#include "Main.hpp"
#include <string>

int Player::maxHealth = 200232;
int Player::health = 122121;
int Player::maxMana = 100;
int Player::mana = 26;
int Player::xp = 0;
int Player::level = 1;
int Player::gold = 0;
int Player::x = 0;
int Player::y = 0;
int Player::oldX = 0;
int Player::oldY = 0;

int Player::atk = 10;
int Player::def = 10;
int Player::agi = 10;
int Player::mag = 10;
int Player::intell = 10;

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

std::string Player::getArt() {
	return "  O\n\\_|_/\n  |\n / \\\x3";
}

std::string Player::getName() {
	return name;
}

int Player::getX() {
	return x;
}

int Player::getY() {
	return y;
}

int Player::getLevel() {
	return level;
}

int Player::getXP() {
	return xp;
}

int Player::getGold() {
	return gold;
}

int Player::getHealth() {
	return health;
}

int Player::getMaxHealth() {
	return maxHealth;
}

int Player::getMana() {
	return mana;
}

int Player::getMaxMana() {
	return maxMana;
}

int Player::getAtk() {
	return atk;
}

int Player::getDef() {
	return def;
}

int Player::getAgi() {
	return agi;
}

int Player::getMag() {
	return mag;
}

int Player::getIntell() {
	return intell;
}

void Player::setX(int var) {
	x = var;
}

void Player::setY(int var) {
	y = var;
}

void Player::setLevel(int var) {
	level = var;
}

void Player::setXP(int var) {
	xp = var;
}

void Player::setGold(int var) {
	gold = var;
}

void Player::setHealth(int var) {
	health = var;
}

void Player::setMaxHealth(int var) {
	maxHealth = var;
}

void Player::setMana(int var) {
	mana = var;
}

void Player::setMaxMana(int var) {
	maxMana = var;
}

void Player::setAtk(int var) {
	atk = var;
}

void Player::setDef(int var) {
	def = var;
}

void Player::setAgi(int var) {
	agi = var;
}

void Player::setMag(int var) {
	mag = var;
}

void Player::setIntell(int var) {
	intell = var;
}

