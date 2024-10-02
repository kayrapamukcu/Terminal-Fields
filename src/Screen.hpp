#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>
#include "Main.hpp"

class Screen {
public:
	static void clearTerminal();
	static void clearTerminalColor();
	static void deleteTerminal(int x, int y, int h, int w); //delete certain area of terminal
	static void updateTerminal(int x, int y, const char* text, bool clear, sf::Color color);
	static void updateTerminalArea(int x, int y, int w, int h, const char* text, bool clear, sf::Color color, bool changeColor);
	static void updateTerminalColor(int x, int y, int h, int w, sf::Color color);
	static void setCharInVertexArray(sf::VertexArray& terminal, int x, int y, char c, sf::Color color, const sf::Texture& fontTexture);
	static void screenManager(sf::RenderWindow& window);
	static void transition(int direction, float transitionTime);
	static sf::Time deltaTime;
};

#endif