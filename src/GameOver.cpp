#include "GameOver.hpp"
#include "Menu.hpp"
#include "Main.hpp"
#include "MainMenu.hpp"
#include "Screen.hpp"

#include <vector>
#include <string>

Menu gameOverMenu = Menu(35, 30, 30, 4, 2, std::vector<std::string>{ "Return to Main Menu", "Load Last Save", "Quit" });
bool init = false;

void GameOver::renderGameOver() {
    sf::Clock clock;
    sf::Clock clock2;
    int index = 0.5*9.8*2*2*2.2;
    while (clock2.getElapsedTime().asSeconds() < 2.0f) {
        if (clock.getElapsedTime().asSeconds() > 0.01f) {
            index = 0.5*9.8*(4-clock2.getElapsedTime().asSeconds()*clock2.getElapsedTime().asSeconds())*2.2;
            clock.restart();
            Screen::updateTerminal(8, index+1, "   _____              __  __   ______ \n  / ____|     /\\     |  \\/  | |  ____|\n | |  __     /  \\    | \\  / | | |__   \n | | |_ |   / /\\ \\   | |\\/| | |  __|  \n | |__| |  / ____ \\  | |  | | | |____ \n  \\_____| /_/    \\_\\ |_|  |_| |______|\x3", true, defaultColor);
        }
    }
    index = 0.5*9.8*2*2*2.2;
    clock.restart();
    clock2.restart();
    while (clock2.getElapsedTime().asSeconds() < 2.0f) {
        if (clock.getElapsedTime().asSeconds() > 0.01f) {
            index = 0.5*9.8*(4-clock2.getElapsedTime().asSeconds()*clock2.getElapsedTime().asSeconds())*2.2;
            clock.restart();
            Screen::updateTerminal(8, 1, "   _____              __  __   ______ \n  / ____|     /\\     |  \\/  | |  ____|\n | |  __     /  \\    | \\  / | | |__   \n | | |_ |   / /\\ \\   | |\\/| | |  __|  \n | |__| |  / ____ \\  | |  | | | |____ \n  \\_____| /_/    \\_\\ |_|  |_| |______|\x3", true, defaultColor);
            Screen::updateTerminal(52, index+1, "   ____   __      __  ______   _____  \n  / __ \\  \\ \\    / / |  ____| |  __ \\ \n | |  | |  \\ \\  / /  | |__    | |__) |\n | |  | |   \\ \\/ /   |  __|   |  _  / \n | |__| |    \\  /    | |____  | | \\ \\ \n  \\____/      \\/     |______| |_|  \\_\\ \x3", false, defaultColor);
        }
    }
    init = true;
}
void GameOver::gameOverInit() {
    Screen::clearTerminal();
    Screen::clearTerminalColor();
    renderGameOver();
    Main::ticker.addNews("You died! NOOB");
    gameOverMenu.display();
}

void GameOver::gameOverHandler(sf::Keyboard::Key key) {
    if (!init) {
        return;
    }
    switch (key) {
    case sf::Keyboard::Up:
        gameOverMenu.handleMovement(1);
        break;
    case sf::Keyboard::Down:
        gameOverMenu.handleMovement(0);
        break;
    case sf::Keyboard::Return:
        if (gameOverMenu.cursorLocation == 0) {
            Main::gameState = 0;
            MainMenu::mainMenuInit();
        }
        else if (gameOverMenu.cursorLocation == 1) {
            //load last save
        }
        else if (gameOverMenu.cursorLocation == 2) {
            Main::quit = true;
        }
        break;
    }
}