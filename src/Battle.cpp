#include "Battle.hpp"
#include "Main.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "EnemyList.hpp"

void Battle::battleHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		break;
	case sf::Keyboard::Down:
		break;
	case sf::Keyboard::Return:
		break;
	}
}

void Battle::battleInit(Player& player) {
	//display player info
	Screen::updateTerminal(5, 6, &player.getArt()[0], false, defaultColor);

	std::string playerInfo = player.name + "\nHP:" + std::to_string(player.maxHealth) + "/" + std::to_string(player.health) + "\nMP:" + std::to_string(player.maxMana) + "/" + std::to_string(player.mana) + "\x3";
	Screen::updateTerminal(3, 12, &playerInfo[0], false, defaultColor);

	Enemy enemy = enemyList[0];
	std::string battleText = enemy.name + "\nHP:" + std::to_string(enemy.maxHealth) + "/" + std::to_string(enemy.health) + "\x3";
	Screen::updateTerminal(Main::FIELD_WIDTH - 20, 12, &battleText[0], false, defaultColor);
}

