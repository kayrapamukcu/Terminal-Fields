#include "Main.hpp"
#include "MainMenu.hpp"
#include "Screen.hpp"
#include "Overworld.hpp"
#include "Menu.hpp"
#include <string>

Menu menu(40, 24, 19, 4, 2, new std::string[4]{ "Start Game", "Load Game", "Options", "Exit" });

void MainMenu::mainMenuInit() {
	Screen::updateTerminal(12, 3, " $$$$$$$$\\                                   $$\\                     $$\\ \n \\__$$  __|                                  \\__|                    $$ |\n    $$ |    $$$$$$\\   $$$$$$\\  $$$$$$\\$$$$\\  $$\\ $$$$$$$\\   $$$$$$\\  $$ |\n    $$ |   $$  __$$\\ $$  __$$\\ $$  _$$  _$$\\ $$ |$$  __$$\\  \\____$$\\ $$ |\n    $$ |   $$$$$$$$ |$$ |  \\__|$$ / $$ / $$ |$$ |$$ |  $$ | $$$$$$$ |$$ |\n    $$ |   $$   ____|$$ |      $$ | $$ | $$ |$$ |$$ |  $$ |$$  __$$ |$$ |\n    $$ |   \\$$$$$$$\\ $$ |      $$ | $$ | $$ |$$ |$$ |  $$ |\\$$$$$$$ |$$ |\n    \\__|    \\_______|\\__|      \\__| \\__| \\__|\\__|\\__|  \\__| \\_______|\\__|\n\n               /$$$$$$$$ /$$           /$$       /$$           \n              | $$_____/|__/          | $$      | $$           \n              | $$       /$$  /$$$$$$ | $$  /$$$$$$$  /$$$$$$$ \n              | $$$$$   | $$ /$$__  $$| $$ /$$__  $$ /$$_____/ \n              | $$__/   | $$| $$$$$$$$| $$| $$  | $$|  $$$$$$  \n              | $$      | $$| $$_____/| $$| $$  | $$ \\____  $$\n              | $$      | $$|  $$$$$$$| $$|  $$$$$$$ /$$$$$$$/ \n              |__/      |__/ \\_______/|__/ \\_______/|_______/ \x3", true, defaultColor);
	menu.display();
	Main::ticker.changeSize(70, 2, 3, 2, Main::FIELD_HEIGHT - 2);
	Main::ticker.addNews("Welcome to Terminal Fields! Version: " + std::string(Main::GAME_VERSION));
}

void MainMenu::mainMenuHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		menu.handleMovement(1);
		break;
	case sf::Keyboard::Down:
		menu.handleMovement(0);
		break;
	case sf::Keyboard::Return:
		switch (menu.cursorLocation) {
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