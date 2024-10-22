#pragma once
#ifndef SCREEN_H
#define SCREEN_H
#include <SFML/Graphics.hpp>

class Screen {
   public:
    static void clearTerminal();
    static void clearTerminalBuffer(bool trueorfalse);
    static void clearTerminalColor();
    static void fadeTerminal(float transitionSpeed);
    static void deleteTerminal(int x, int y, int h, int w, bool clearColor);  // delete certain area of terminal
    static void updateTerminal(int x, int y, const char* text, bool clear, sf::Color color);
    static void updateTerminalArea(int x, int y, int w, int h, const char* text, bool clear, sf::Color color, bool changeColor);
    static void updateTerminalColor(int x, int y, int h, int w, sf::Color color);
    static void setCharInVertexArray(sf::VertexArray& terminal, int x, int y, char c, sf::Color color, const sf::Texture& fontTexture);
    static void screenManager(sf::RenderWindow& window);
    static void transition(int direction, float transitionTime, bool clearOrDraw);
    static void renderBarStats(int x, int y, int health, int maxHealth, int mana, int maxMana, bool renderXPBar);
    static sf::Clock deltaClock;
    static sf::Time deltaTime;
    static sf::RenderWindow* windowRef;
};

#endif