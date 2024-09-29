#pragma once
#include <SFML/Window/Keyboard.hpp>
#include "Player.hpp"

#ifndef BATTLE_H
#define BATTLE_H

class Battle {
public:
	static void battleHandler(sf::Keyboard::Key key);
	static void battleInit(Player& player);
};

#endif