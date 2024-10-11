#pragma once
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Menu {
public:
	int x;
	int y;
	int buttonWidth;
	int spaceBetweenButtons;
	int cursorOffset;
	std::vector<std::string> buttonNames;
	static sf::Color menuSelectedColor;
	Menu(int x, int y, int buttonWidth, int spaceBetweenButtons, int cursorOffset, std::vector<std::string>buttonNames);
	void display();
	void handleMovement(int direction);
	int cursorLocation = 0;
	int cursorLocationPrev = 0;
	int buttonCount = 0;
};

#endif