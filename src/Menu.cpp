#include "Main.hpp"
#include "Menu.hpp"
#include "Screen.hpp"
#include "Overworld.hpp"
#include <string>

void Menu::menuInit() {
	Screen::updateTerminal(12, 3, " $$$$$$$$\\                                   $$\\                     $$\\ \n \\__$$  __|                                  \\__|                    $$ |\n    $$ |    $$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\  $$\\ $$$$$$$\\   $$$$$$\\  $$ |\n    $$ |   $$  __$$\\ $$  __$$\\ $$  _$$  _$$\\ $$ |$$  __$$\\  \\____$$\\ $$ |\n    $$ |   $$$$$$$$ |$$ |  \\__|$$ / $$ / $$ |$$ |$$ |  $$ | $$$$$$$ |$$ |\n    $$ |   $$   ____|$$ |      $$ | $$ | $$ |$$ |$$ |  $$ |$$  __$$ |$$ |\n    $$ |   \\$$$$$$$\\ $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |\\$$$$$$$ |$$ |\n    \\__|    \\_______|\\__|      \\__| \\__| \\__|\\__|\\__|  \\__| \\_______|\\__|\n\n               /$$$$$$$$ /$$           /$$       /$$           \n              | $$_____/|__/          | $$      | $$           \n              | $$       /$$  /$$$$$$ | $$  /$$$$$$$  /$$$$$$$ \n              | $$$$$   | $$ /$$__  $$| $$ /$$__  $$ /$$_____/ \n              | $$__/   | $$| $$$$$$$$| $$| $$  | $$|  $$$$$$  \n              | $$      | $$| $$_____/| $$| $$  | $$ \\____  $$\n              | $$      | $$|  $$$$$$$| $$|  $$$$$$$ /$$$$$$$/ \n              |__/      |__/ \\_______/|__/ \\_______/|_______/ \x3", true, defaultColor);
	//do other things
	Screen::updateTerminal(40, 24, "------------------- \n# Start Game      #\n-------------------\n\n\-------------------\n# Load Game       #\n-------------------\n\n-------------------\n# Options         #\n-------------------\n\n-------------------\n# Exit            #\n-------------------\x3", false, defaultColor);
	updateCursorLocation(-1);
	Main::ticker.changeSize(70, 2, 3, 2, Main::FIELD_HEIGHT - 2);
	Main::ticker.addNews("Welcome to Terminal Fields! Version: " + std::string(Main::GAME_VERSION));
}

void Menu::updateCursorLocation(int direction) {
	const sf::Color menuSelectedColor(249, 241, 165);
	Screen::deleteTerminal(38, 25 + Menu::cursorLocation * 4, 1, 1);
	Screen::updateTerminalColor(38, 24 + Menu::cursorLocation * 4, 3, 21, defaultColor);
	if (direction == 0) {
		Menu::cursorLocation++;
		if (Menu::cursorLocation > 3) {
			Menu::cursorLocation = 0;
		}
	}
	else if (direction == 1) {
		Menu::cursorLocation--;
		if (Menu::cursorLocation < 0) {
			Menu::cursorLocation = 3;
		}
	}
	else if (direction == -1){
		Menu::cursorLocation = 0;
	}
	Screen::updateTerminalColor(38, 24 + Menu::cursorLocation * 4, 3, 21, menuSelectedColor);
	Screen::updateTerminal(38, 25 + Menu::cursorLocation * 4, "*\x3", false, menuSelectedColor);
}

void Menu::menuHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		Menu::updateCursorLocation(1);
		break;
	case sf::Keyboard::Down:
		Menu::updateCursorLocation(0);
		break;
	case sf::Keyboard::Return:
		switch (Menu::cursorLocation) {
		case 0:
			Main::gameState = 1;
			Overworld::overworldInit();
			break;
		case 1:
			//load game

			break;
		case 2:
			//options
			break;
		case 3:
			Main::quit = true;
			break;
		}
		break;
	}
}