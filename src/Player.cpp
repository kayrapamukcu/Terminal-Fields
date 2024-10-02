#include "Player.hpp"
#include "Main.hpp"
#include <string>

void Player::updateLocation() {
	if(Main::terminal[oldY][oldX] != '#') {
		Main::terminal[oldY][oldX] = ' ';
	}
	Main::terminal[y][x] = 'P';
	Main::terminalColor[oldY][oldX] = defaultColor;
	Main::terminalColor[y][x] = sf::Color::Green;
	oldX = x;
	oldY = y;
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

