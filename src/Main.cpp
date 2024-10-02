#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <thread>

#include "Main.hpp"
#include "Menu.hpp"
#include "Sound.hpp"
#include "Screen.hpp"
#include "Overworld.hpp"
#include "Battle.hpp"
#include "NewsTicker.hpp"

//gameState 0 = menu
//gameState 1 = game
//gameState 2 = battle

bool Main::quit = false;
int Main::gameState = 0;

int Menu::cursorLocation = 0;
int movementCooldown = 200;

char Main::terminal[Main::FIELD_HEIGHT][Main::FIELD_WIDTH] = { 0 };
sf::Color Main::terminalColor[Main::FIELD_HEIGHT][Main::FIELD_WIDTH] = { defaultColor };

static NewsTicker ticker = NewsTicker(70, 6, 5, 2, 2);

int main() {
	sf::RenderWindow window(sf::VideoMode(Main::FIELD_WIDTH * Main::TILE_WIDTH, Main::FIELD_HEIGHT * Main::TILE_HEIGHT), "Terminal Fields");
	window.setVerticalSyncEnabled(Main::VSYNC);
	window.setActive(false);
	//vsync
	
	//threads
	//main thread = input thread

	std::thread renderThread(Screen::screenManager, std::ref(window));
	std::thread soundThread(Sound::soundManager);

	Menu::menuInit();

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
				if (Main::gameState == 0) {
					Menu::menuHandler(event.key.code);
				}
				else if (Main::gameState == 1) {
					Overworld::overworldHandler(event.key.code);
				}
				else if (Main::gameState == 2) {
					Battle::battleHandler(event.key.code);
				}
				break;
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