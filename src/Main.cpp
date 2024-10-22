#include "Main.hpp"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <thread>

#include "Battle.hpp"
#include "GameOver.hpp"
#include "MainMenu.hpp"
#include "NewsTicker.hpp"
#include "Overworld.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Sound.hpp"

bool Main::renderTerminalBuffer = false;
bool Main::quit = false;
int Main::gameState = 0;

char Main::terminal[Main::FIELD_HEIGHT][Main::FIELD_WIDTH] = {0};
bool Main::terminalBuffer[Main::FIELD_HEIGHT][Main::FIELD_WIDTH] = {true};
sf::Color Main::terminalColor[Main::FIELD_HEIGHT][Main::FIELD_WIDTH] = {defaultColor};

static NewsTicker ticker = NewsTicker(70, 6, 5, 2, 2);

int main() {
    sf::RenderWindow window(sf::VideoMode(Main::FIELD_WIDTH * Main::TILE_WIDTH, Main::FIELD_HEIGHT * Main::TILE_HEIGHT), "Terminal Fields");
    window.setVerticalSyncEnabled(Main::VSYNC);
    window.setActive(false);
    // threads
    // main thread = input thread

    Sound::soundInit();
    std::thread renderThread(Screen::screenManager, std::ref(window));
    std::thread soundThread(Sound::soundManager);

    MainMenu::mainMenuInit();
    Screen::clearTerminalBuffer(true);

    // How to not code a game loop
    // I'm not going to redo this stuff, sorry. This is my first project with C++ I'll cut myself some slack.

    while (window.isOpen() && !Main::quit) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    Main::quit = true;
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        Main::quit = true;
                        window.close();
                    }
                    if (!Main::renderTerminalBuffer) {
                        if (Main::gameState == 0) {
                            MainMenu::mainMenuHandler(event.key.code);
                        } else if (Main::gameState == 1) {
                            Overworld::overworldHandler(event.key.code);
                        } else if (Main::gameState == 2) {
                            Battle::battleHandler(event.key.code);
                        } else if (Main::gameState == 3) {
                            GameOver::gameOverHandler(event.key.code);
                        }
                        break;
                    }
                case sf::Event::TextEntered:
                    break;
                default:

                    break;
            }
        }
        sf::sleep(sf::milliseconds(20));
    }
    window.close();
    if (Main::quit) {
        if (soundThread.joinable()) {
            soundThread.join();
        }
        if (renderThread.joinable()) {
            renderThread.join();
        }
    }
    return 0;
}