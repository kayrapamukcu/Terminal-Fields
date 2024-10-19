#include <string>
#include <random>

#include "Battle.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Enemy.hpp"
#include "Menu.hpp"
#include "Main.hpp"
#include "Overworld.hpp"
#include "Sound.hpp"
#include "GameOver.hpp"

#include <iostream>
#include <functional>

Menu battleMenu = Menu(3, 30, 19, 4, 2, std::vector<std::string>{ "Attack", "Concentrate", "Items", "Special", "Flee" }); 

std::unique_ptr<Enemy> enemy;
int x = 0;
int y = 0;

std::unique_ptr<Enemy> generateRandomEnemy() {
    std::vector<std::function<std::unique_ptr<Enemy>()>> monsterList = {
        []() { return std::make_unique<Frog>(); },
        []() { return std::make_unique<Sik>(); }
    };
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, monsterList.size() - 1);
    return monsterList[dist(gen)]();
}

void Battle::updateDisplays() {
	Screen::updateTerminal(3, 12, &(Player::name + "\x3")[0], false, defaultColor);
	Screen::renderBarStats(3, 14, Player::health, Player::maxHealth, Player::mana, Player::maxMana, false);
	Screen::updateTerminal(Main::FIELD_WIDTH - 20, 12, &(enemy->name + "\x3")[0], false, defaultColor);
	Screen::renderBarStats(Main::FIELD_WIDTH - 20, 14, enemy->health, enemy->maxHealth, enemy->mana, enemy->maxMana, false);
}

void Battle::battleInit(int monsterX, int monsterY) {
	//display player info
	Screen::clearTerminal();
	Screen::clearTerminalColor();
	Screen::clearTerminalBuffer(true);
	Screen::updateTerminal(5, 6, &Player::getArt()[0], false, defaultColor);
	enemy = generateRandomEnemy();
	enemy->attack();
	x = monsterX;
	y = monsterY;
	Main::ticker.changeSize(74, 20, 15, 24, 30);
	Main::ticker.addNews("You encountered " + enemy->name + "!");
	battleMenu.display();
	updateDisplays();
}

void Battle::pause(int duration, bool skippable) {
	battleMenu.handleMovement(-2);
	sf::Clock clock;
	while (clock.getElapsedTime().asMilliseconds() < duration) {
		sf::Event event;
		while (Screen::windowRef->pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				if (skippable) {
					if (event.key.code == sf::Keyboard::Z) {
						battleMenu.handleMovement(-1);
						return;
					}
				}
			}
		}
	}
	battleMenu.handleMovement(-1);
}

void Battle::battleHandler(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Up:
		battleMenu.handleMovement(1);
		break;
	case sf::Keyboard::Down:
		battleMenu.handleMovement(0);
		break;
	case sf::Keyboard::Return:
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(1, 100);
		if (battleMenu.cursorLocation == 0) {
			//attack

			int dmg;
			
			if (dist(gen) <= Player::critChance) {
				dmg = Player::atk * Player::critMult * (1 + (rand() % 10)/10.0f);
				Main::ticker.addNews("(CRIT) You attacked " + enemy->name + " for " + std::to_string(dmg) + " damage!");
			}
			else {
				dmg = Player::atk * (1 + (rand() % 10)/10.0f);
				Main::ticker.addNews("You attacked " + enemy->name + " for " + std::to_string(dmg) + " damage!");
			}
			enemy->health -= dmg;
		}
		else if (battleMenu.cursorLocation == 1) {
			//concentrate

			int manaGain;
			
			Main::ticker.addNews("You try concentrating with all your might...");
			pause(1000, true);
			if (dist(gen) <= 50) {
				Main::ticker.addNews("However, your mind wanders...");
				manaGain = (Player::intell * (1 + (rand() % 40))) / 20;
			}
			else if (dist(gen) <= 75) {
				Main::ticker.addNews("You concentrate well enough, but you can't get rid of that stray thought..");
				manaGain = (Player::intell * (1 + (rand() % 40))) / 12;

			} else {
				Main::ticker.addNews("You feel a surge of power!");
				manaGain = (Player::intell * (1 + (rand() % 40))) / 6;
			}
			pause(1000, true);
			Player::mana += manaGain;
			Main::ticker.addNews("You gained " + std::to_string(manaGain) + " mana!");
		}
		else if (battleMenu.cursorLocation == 2) {
			//items
			Main::ticker.addNews("You have no items!");
		}
		else if (battleMenu.cursorLocation == 3) {
			//special
		}
		else if (battleMenu.cursorLocation == 4) {
			//flee
			Main::ticker.addNews("You try to run away...");
			pause(1000, false);
			if (dist(gen) <= 50) {
				Main::ticker.addNews("But you trip and fall!");
				pause(1000, true);
			}
			else {
				Main::ticker.addNews("You managed to escape!");
				pause(1000, true);
				Main::gameState = 1;
				Overworld::overworldInitLater();
				Overworld::MonsterKey k = { Overworld::overworldX, Overworld::overworldY, x, y };
   				Overworld::monsterKilledMap[k] = true;
				Overworld::monsterCountArray[(Overworld::overworldX+1) + (Overworld::overworldY+1)*3]--;
				break;
			}
		}
		//enemy turn
		if(enemy->health < 0) {
			enemy->health = 0;
		}
		Battle::updateDisplays();
		pause(750, false);
		if (enemy->health > 0) {
			int dmg = enemy->atk * (1 + (rand() % 10)/10.0f);
			Main::ticker.addNews(enemy->name + " attacked you for " + std::to_string(dmg) + " damage!");
			Player::health -= dmg;
		} else {
			Main::ticker.addNews("You defeated " + enemy->name + "!");
			Player::xp += 10;
			Player::processXP();
			Main::ticker.addNews("You gained 10 XP!");

			Overworld::MonsterKey k = { Overworld::overworldX, Overworld::overworldY, x, y };
   			Overworld::monsterKilledMap[k] = true;
			Overworld::monsterCountArray[(Overworld::overworldX+1) + (Overworld::overworldY+1)*3]--;

			pause(2000, true);
			Main::gameState = 1;
			Overworld::overworldInitLater();
		}
		
		if(Player::health > Player::maxHealth) {
			Player::health = Player::maxHealth;
		}
		else if (Player::health < 0) {
			Player::health = 0;
			Main::ticker.addNews("You died!");
			Battle::updateDisplays();
			Sound::stopMusic();
			pause(500, false);
			Screen::fadeTerminal(1.5f);
			Main::gameState = 3;
			pause(2000, false);
			GameOver::gameOverInit();
		}

		if (Main::gameState == 2) Battle::updateDisplays();
		break;	
	}
}