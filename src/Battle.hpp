#pragma once

#ifndef BATTLE_H
#define BATTLE_H

#include <SFML/Window/Keyboard.hpp>
#include "Player.hpp"
#include "Menu.hpp"
#include "Enemy.hpp"

class Battle {
public:
	static void battleHandler(sf::Keyboard::Key key);
	static void battleInit();
	static void updateDisplays();
private:
	static Enemy enemy;
};

#endif