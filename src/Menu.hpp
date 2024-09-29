#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Window/Keyboard.hpp>

class Menu {
public:
	static void menuInit();
	static void updateCursorLocation(int direction);
	static void menuHandler(sf::Keyboard::Key key);
	static int cursorLocation;
};

#endif