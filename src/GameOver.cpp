#include "GameOver.hpp"

#include <string>

#include "Main.hpp"
#include "MainMenu.hpp"
#include "Menu.hpp"
#include "Screen.hpp"
#include "NewsTicker.hpp"

Menu gameOverMenu = Menu(35, 30, 30, 4, 2, std::vector<std::string>{"Return to Main Menu", "Load Last Save", "Quit"});

void GameOver::renderGameOver() {
    sf::Clock clock;
    sf::Clock clock2;
    int index = 0.5 * 9.8 * 2 * 2 * 2.2;
    while (clock2.getElapsedTime().asSeconds() < 2.0f) {
        if (clock.getElapsedTime().asSeconds() > 0.01f) {
            index = 0.5 * 9.8 * (4 - clock2.getElapsedTime().asSeconds() * clock2.getElapsedTime().asSeconds()) * 2.2;
            clock.restart();
            Screen::updateTerminal(8, index + 1, "   _____              __  __   ______ \n  / ____|     /\\     |  \\/  | |  ____|\n | |  __     /  \\    | \\  / | | |__   \n | | |_ |   / /\\ \\   | |\\/| | |  __|  \n | |__| |  / ____ \\  | |  | | | |____ \n  \\_____| /_/    \\_\\ |_|  |_| |______|\x3", true, defaultColor);
        }
    }
    index = 0.5 * 9.8 * 2 * 2 * 2.2;
    clock.restart();
    clock2.restart();
    while (clock2.getElapsedTime().asSeconds() < 2.0f) {
        if (clock.getElapsedTime().asSeconds() > 0.01f) {
            index = 0.5 * 9.8 * (4 - clock2.getElapsedTime().asSeconds() * clock2.getElapsedTime().asSeconds()) * 2.2;
            clock.restart();
            Screen::updateTerminal(8, 1, "   _____              __  __   ______ \n  / ____|     /\\     |  \\/  | |  ____|\n | |  __     /  \\    | \\  / | | |__   \n | | |_ |   / /\\ \\   | |\\/| | |  __|  \n | |__| |  / ____ \\  | |  | | | |____ \n  \\_____| /_/    \\_\\ |_|  |_| |______|\x3", true, defaultColor);
            Screen::updateTerminal(52, index + 1, "   ____   __      __  ______   _____  \n  / __ \\  \\ \\    / / |  ____| |  __ \\ \n | |  | |  \\ \\  / /  | |__    | |__) |\n | |  | |   \\ \\/ /   |  __|   |  _  / \n | |__| |    \\  /    | |____  | | \\ \\ \n  \\____/      \\/     |______| |_|  \\_\\ \x3", false, defaultColor);
        }
    }
}
void GameOver::gameOverInit() {
    NewsTicker::renderTicker = false;
    Screen::clearTerminal();
    Screen::clearTerminalColor();
    gameOverMenu.handleMovement(-2);
    renderGameOver();
    Main::ticker.addNews("You died! NOOB");
    gameOverMenu.display();
}

void GameOver::gameOverHandler(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Up:
            gameOverMenu.handleMovement(1);
            break;
        case sf::Keyboard::Down:
            gameOverMenu.handleMovement(0);
            break;
        case sf::Keyboard::Z:
            if (gameOverMenu.cursorLocation == 0) {
                Main::gameState = 0;
                MainMenu::mainMenuInit();
            } else if (gameOverMenu.cursorLocation == 1) {
                // load last save
            } else if (gameOverMenu.cursorLocation == 2) {
                Main::quit = true;
            }
            break;
    }
}