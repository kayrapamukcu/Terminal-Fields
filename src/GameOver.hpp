#pragma once
#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <SFML/Window/Keyboard.hpp>

class GameOver {
public:
    static void gameOverHandler(sf::Keyboard::Key key);
    static void gameOverInit();
    static void renderGameOver();
};

#endif