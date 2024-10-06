#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>

class Menu {
public:
	int x;
	int y;
	int buttonWidth;
	int spaceBetweenButtons;
	int cursorOffset;
	std::string* buttonNames;
	static sf::Color menuSelectedColor;
	Menu(int x, int y, int buttonWidth, int spaceBetweenButtons, int cursorOffset, std::string* buttonNames);
	void display();
	void handleMovement(int direction);
	int cursorLocation;
	int cursorLocationPrev;
};

#endif