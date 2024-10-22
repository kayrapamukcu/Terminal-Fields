#include "Battle.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <string>

#include "Enemy.hpp"
#include "GameOver.hpp"
#include "Main.hpp"
#include "Menu.hpp"
#include "Overworld.hpp"
#include "Player.hpp"
#include "Screen.hpp"
#include "Sound.hpp"
#include "enemies/Zone1Enemies.cpp"

Menu Battle::battleMenu = Menu(3, 30, 19, 4, 2, std::vector<std::string>{"Attack", "Concentrate", "Items", "Special", "Flee"});
Menu Battle::specialMenu = Menu(3, 30, 19, 4, 2, std::vector<std::string>{"Heal", "Special 2", "Special 3", "Special 4", "Special 5"});

bool Battle::inSubMenu = false;
std::unique_ptr<Enemy> enemy;
int Battle::x = 0;
int Battle::y = 0;

std::unique_ptr<Enemy> generateRandomEnemy() {
    std::vector<std::function<std::unique_ptr<Enemy>()>> monsterList;
    if (Overworld::currentZone == 1) {
        monsterList = {
            []() { return std::make_unique<FreakyFrog>(); },
            []() { return std::make_unique<Werewolf>(); },
            []() { return std::make_unique<LivingScarecrow>(); },
            []() { return std::make_unique<MassiveBat>(); },
            []() { return std::make_unique<RockGolem>(); },
            []() { return std::make_unique<PossessedTractor>(); },
            []() { return std::make_unique<CarnivorousPlant>(); },
            []() { return std::make_unique<CursedCow>(); },
            []() { return std::make_unique<EnragedRam>(); }
            // boss: TheSerpent
        };
    }  // else if (Overworld::currentZone == 2) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, monsterList.size() - 1);
    return monsterList[dist(gen)]();
}

void Battle::manaControl(int val, bool isForPlayer) {
    if (isForPlayer) {
        Player::mana += val;
        if (Player::mana < 0) {
            Player::mana = 0;
        }
        if (Player::mana > Player::maxMana) {
            Player::mana = Player::maxMana;
        }
    } else {
        enemy->mana += val;
        if (enemy->mana < 0) {
            enemy->mana = 0;
        }
        if (enemy->mana > enemy->maxMana) {
            enemy->mana = enemy->maxMana;
        }
    }
}

void Battle::healthControl(int val, bool isForPlayer) {
    if (isForPlayer) {
        Player::health += val;
        if (Player::health < 0) {
            Player::health = 0;
        }
        if (Player::health > Player::maxHealth) {
            Player::health = Player::maxHealth;
        }
    } else {
        enemy->health += val;
        if (enemy->health < 0) {
            enemy->health = 0;
        }
        if (enemy->health > enemy->maxHealth) {
            enemy->health = enemy->maxHealth;
        }
    }
}

void Battle::updateDisplays() {
    Screen::updateTerminal(3, 12, &(Player::name + "\x3")[0], false, defaultColor);
    Screen::renderBarStats(3, 14, Player::health, Player::maxHealth, Player::mana, Player::maxMana, false);
    Screen::updateTerminal(Main::FIELD_WIDTH - 21, 12, &(enemy->name + "\x3")[0], false, defaultColor);
    Screen::renderBarStats(Main::FIELD_WIDTH - 21, 14, enemy->health, enemy->maxHealth, enemy->mana, enemy->maxMana, false);
}

void Battle::battleInit(int monsterX, int monsterY) {
    Screen::clearTerminal();
    Screen::clearTerminalColor();
    Screen::clearTerminalBuffer(true);
    Screen::updateTerminal(5, 6, &Player::getArt()[0], false, defaultColor);
    enemy = generateRandomEnemy();
    Screen::updateTerminal(Main::FIELD_WIDTH - 19, 6, &enemy->getArt()[0], false, defaultColor);
    x = monsterX;
    y = monsterY;
    Main::ticker.changeSize(74, 20, 15, 24, 30);
    Main::ticker.addNews("You encountered " + enemy->name + "!");
    battleMenu.display();
    updateDisplays();
    optionInfo();
}

void Battle::pause(int duration, bool skippable) {
    battleMenu.handleMovement(-2);
    sf::Clock clock;
    while (clock.getElapsedTime().asMilliseconds() < duration) {
        sf::Event event;
        while (Screen::windowRef->pollEvent(event)) {
            if (event.type == sf::Event::KeyPressed) {
                if (skippable) {
                    if (event.key.code == sf::Keyboard::X) {
                        battleMenu.handleMovement(-1);
                        return;
                    }
                }
            }
        }
    }
    battleMenu.handleMovement(-1);
}

void Battle::playerDeath() {
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

void Battle::enemyTurn() {
    // enemy turn
    Battle::updateDisplays();
    pause(375, false);
    if (enemy->health > 0) {
        enemy->behavior();
    } else {
        Main::ticker.addNews("You defeated " + enemy->name + "!");
        Player::xp += enemy->xpDrop;
        Main::ticker.addNews("You gained " + std::to_string(enemy->xpDrop) + "XP!");
        Player::processXP();

        Overworld::MonsterKey k = {Overworld::overworldX, Overworld::overworldY, x, y};
        Overworld::monsterKilledMap[k] = true;
        Overworld::monsterCountArray[(Overworld::overworldX + 1) + (Overworld::overworldY + 1) * 3]--;

        pause(2000, true);
        Main::gameState = 1;
        Overworld::overworldInitLater();
    }
    if (Player::health <= 0) {
        playerDeath();
    }
    if (Main::gameState == 2) Battle::updateDisplays();
}

void Battle::optionInfo() {
    std::string selectedThing;
    std::string selectedThingInfo;
    std::string dependsOn;
    std::string cost;
    bool costRender = false;
    if (!inSubMenu) {
        costRender = false;
        switch (battleMenu.cursorLocation) {
            case 0:
                selectedThing = "Attack";
                selectedThingInfo = "Attack the enemy with your weapon.";
                dependsOn = "Strength";
                break;
            case 1:
                selectedThing = "Concentrate";
                selectedThingInfo = "Concentrate to gain mana.";
                dependsOn = "Intelligence";
                break;
            case 2:
                selectedThing = "Items";
                selectedThingInfo = "Use an item.";
                dependsOn = "None";
                break;
            case 3:
                selectedThing = "Special";
                selectedThingInfo = "Use a special ability.";
                dependsOn = "Magic, Intelligence";
                break;
            case 4:
                selectedThing = "Flee";
                selectedThingInfo = "Try to escape from battle.";
                dependsOn = "Agility";
                break;
        }
    } else {
        costRender = true;
        switch (specialMenu.cursorLocation) {
            case 0:
                selectedThing = "Heal";
                selectedThingInfo = "Heal yourself.";
                dependsOn = "Magic, Intelligence";
                cost = "5 Mana";
                break;
            case 1:
                selectedThing = "Special 2";
                selectedThingInfo = "Special ability 2.";
                dependsOn = "Magic, Intelligence";
                cost = "5 Mana";
                break;
            case 2:
                selectedThing = "Special 3";
                selectedThingInfo = "Special ability 3.";
                dependsOn = "Magic, Intelligence";
                cost = "5 Mana";
                break;
            case 3:
                selectedThing = "Special 4";
                selectedThingInfo = "Special ability 4.";
                dependsOn = "Magic, Intelligence";
                cost = "5 Mana";
                break;
            case 4:
                selectedThing = "Special 5";
                selectedThingInfo = "Special ability 5.";
                dependsOn = "Magic, Intelligence";
                cost = "5 Mana";
                break;
        }
    }
    Screen::deleteTerminal(3, 22, 7, 50, true);
    Screen::updateTerminal(3, 22, "Selected: \x3", false, defaultColor);
    Screen::updateTerminalColor(3, 22, 1, 9, sf::Color::Green);
    Screen::updateTerminal(3, 23, (selectedThing + "\x3").c_str(), false, defaultColor);
    Screen::updateTerminal(3, 25, (selectedThingInfo + "\x3").c_str(), false, defaultColor);
    if (costRender) {
        Screen::updateTerminal(3, 27, ("Cost: " + cost + "\x3").c_str(), false, defaultColor);
    }
    Screen::updateTerminal(3, 28, ("Depends on: " + dependsOn + "\x3").c_str(), false, defaultColor);
}

void Battle::battleHandler(sf::Keyboard::Key key) {
    optionInfo();
    // i know, this is coded really badly, but so is the entire game, and i'm not going to fix that
    if (inSubMenu) {
        battleMenu.handleMovement(-2);
        switch (key) {
            case sf::Keyboard::Up:
                specialMenu.handleMovement(1);
                optionInfo();
                break;
            case sf::Keyboard::Down:
                specialMenu.handleMovement(0);
                optionInfo();
                break;
            case sf::Keyboard::Z:
                if (specialMenu.cursorLocation == 0) {
                    // special 1
                    int heal = (pow(Player::intell, 1.8) * (1 + (rand() % 20))) / 4;
                    healthControl(heal, true);
                    Player::mana -= 5;
                    Main::ticker.addNews("You healed yourself for " + std::to_string(heal) + " HP!");
                } else if (specialMenu.cursorLocation == 1) {
                    // special 2
                    Main::ticker.addNews("Special 2!");
                } else if (specialMenu.cursorLocation == 2) {
                    // special 3
                    Main::ticker.addNews("Special 3!");
                } else if (specialMenu.cursorLocation == 3) {
                    // special 4
                    Main::ticker.addNews("Special 4!");
                } else if (specialMenu.cursorLocation == 4) {
                    // special 5
                    Main::ticker.addNews("Special 5!");
                }
                Screen::deleteTerminal(0, 30, 20, 2, true);
                inSubMenu = false;
                enemyTurn();
                return;
            case sf::Keyboard::X:
                Screen::deleteTerminal(0, 30, 20, 2, true);
                battleMenu.cursorLocation = 3;
                battleMenu.display();
                inSubMenu = false;
                return;
        }
        specialMenu.display();
        return;
    }
    switch (key) {
        case sf::Keyboard::Up:
            battleMenu.handleMovement(1);
            optionInfo();
            break;
        case sf::Keyboard::Down:
            battleMenu.handleMovement(0);
            optionInfo();
            break;
        case sf::Keyboard::Z:
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> dist(1, 100);
            if (battleMenu.cursorLocation == 0) {  // attack
                int dmg;
                if (dist(gen) <= Player::critChance) {
                    dmg = Player::atk * Player::critMult * (1 + (rand() % 10) / 10.0f);
                    Main::ticker.addNews("(CRIT) You attacked " + enemy->name + " for " + std::to_string(dmg) + " damage!");
                } else {
                    dmg = Player::atk * (1 + (rand() % 10) / 10.0f);
                    Main::ticker.addNews("You attacked " + enemy->name + " for " + std::to_string(dmg) + " damage!");
                }
                healthControl(-dmg, false);
            } else if (battleMenu.cursorLocation == 1) {  // concentrate
                int manaGain;
                Main::ticker.addNews("You try concentrating with all your might...");
                pause(500, true);
                if (dist(gen) <= 50) {
                    Main::ticker.addNews("However, your mind wanders...");
                    manaGain = (Player::intell * (1 + (rand() % 40))) / 20;
                } else if (dist(gen) <= 75) {
                    Main::ticker.addNews("You concentrate well enough, but you can't get rid of that stray thought..");
                    manaGain = (Player::intell * (1 + (rand() % 40))) / 12;

                } else {
                    Main::ticker.addNews("You feel a surge of power!");
                    manaGain = (Player::intell * (1 + (rand() % 40))) / 6;
                }
                pause(1000, true);
                manaControl(manaGain, true);
                Main::ticker.addNews("You gained " + std::to_string(manaGain) + " mana!");
            } else if (battleMenu.cursorLocation == 2) {
                // items
                Main::ticker.addNews("You have no items!");
            } else if (battleMenu.cursorLocation == 3) {
                // special
                inSubMenu = true;
                battleHandler(sf::Keyboard::Unknown);
                break;
            } else if (battleMenu.cursorLocation == 4) {
                // flee
                Main::ticker.addNews("You try to run away...");
                pause(500, true);
                if (dist(gen) <= 0) {
                    Main::ticker.addNews("But you trip and fall!");
                    pause(1000, true);
                } else {
                    Main::ticker.addNews("You managed to escape!");
                    pause(1000, true);

                    Overworld::MonsterKey k = {Overworld::overworldX, Overworld::overworldY, x, y};
                    Overworld::monsterKilledMap[k] = true;
                    Overworld::monsterCountArray[(Overworld::overworldX + 1) + (Overworld::overworldY + 1) * 3]--;

                    Main::gameState = 1;
                    Overworld::overworldInitLater();
                    break;
                }
            }
            enemyTurn();
            break;
    }
}