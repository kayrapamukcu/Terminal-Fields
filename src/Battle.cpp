#include <string>

#include "Battle.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Main.hpp"

Menu battleMenu = Menu(3, 30, 19, 4, 2, std::vector<std::string>{ "Attack", "Concentrate", "Items", "Special", "Flee" }); 
Enemy Battle::enemy("Placeholder", 10, 10, 10, 0);

void Battle::battleInit() {
	//display player info
	Screen::clearTerminal();
	Screen::clearTerminalColor();
	Screen::clearTerminalBuffer(true);
	Screen::updateTerminal(5, 6, &Main::player.getArt()[0], false, defaultColor);
	std::string playerInfo = Main::player.getName() + "\nHP:" + std::to_string(Main::player.getHealth()) + "/" + std::to_string(Main::player.getMaxHealth()) + "\nMP:" + std::to_string(Main::player.getMana()) + "/" + std::to_string(Main::player.getMaxMana()) + "\x3";
	Screen::updateTerminal(3, 12, &playerInfo[0], false, defaultColor);
	enemy = Enemy::getRandomEnemy();
	std::string battleText = enemy.name + "\nHP:" + std::to_string(enemy.health) + "/" + std::to_string(enemy.maxHealth) + "\x3";
	Screen::updateTerminal(Main::FIELD_WIDTH - 20, 12, &battleText[0], false, defaultColor);
	Main::ticker.changeSize(40, 40, 15, 50, 30);
	Main::ticker.addNews("You encountered " + enemy.name + "!");
	battleMenu.display();
}

void Battle::updateDisplays() {
	std::string playerInfo = Main::player.getName() + "\nHP:" + std::to_string(Main::player.getHealth()) + "/" + std::to_string(Main::player.getMaxHealth()) + "\nMP:" + std::to_string(Main::player.getMana()) + "/" + std::to_string(Main::player.getMaxMana()) + "\x3";
	Screen::updateTerminal(3, 12, &playerInfo[0], false, defaultColor);
	std::string battleText = enemy.name + "\nHP:" + std::to_string(enemy.health) + "/" + std::to_string(enemy.maxHealth) + "\x3";
	Screen::updateTerminal(Main::FIELD_WIDTH - 20, 12, &battleText[0], false, defaultColor);
}

void Battle::battleHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		battleMenu.handleMovement(1);
		Main::player.setHealth(Main::player.getHealth() - 1);
		break;
	case sf::Keyboard::Down:
		battleMenu.handleMovement(0);
		break;
	case sf::Keyboard::Return:
		if (battleMenu.cursorLocation == 0) {
			//attack
			int dmg = Main::player.getAtk() * (1 + (rand() % 10)/10.0f);
			enemy.health -= dmg;
			Main::ticker.addNews("You attacked " + enemy.name + " for " + std::to_string(dmg) + " damage!");
		}
		else if (battleMenu.cursorLocation == 1) {
			//concentrate
		}
		else if (battleMenu.cursorLocation == 2) {
			//items
		}
		else if (battleMenu.cursorLocation == 3) {
			//special
		}
		else if (battleMenu.cursorLocation == 4) {
			//flee
		}
		break;
	}
	Battle::updateDisplays();
}