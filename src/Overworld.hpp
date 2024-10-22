#ifndef OVERWORLD_H
#define OVERWORLD_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

#include "Player.hpp"

class Overworld {
   public:
    static float obstacleChance;
    static float enemyChance;
    static float chestChance;
    static int overworldX;
    static int overworldY;
    static int gameSeed;
    static int monsterCountArray[9];
    static int chestCountArray[9];
    static int currentZone;
    static int selectedMenu;
    static void overworldPopulate(float obstacleChance, float enemyChance, float chestChance);
    static void overworldHandler(sf::Keyboard::Key key);
    static void overworldInit(std::string playerName, int seed);
    static void overworldInitLater();
    static void overworldChangeScreen(int direction);
    static bool checkCollision(int direction);
    static void updateStats();
    static void updateMinimap();
    static void overworldMapCalculator(float obstacleChance, float enemyChance, float chestChance);
    static int getScreenSeed(int gameSeed, int overworldX, int overworldY);
    static bool isMonsterKilled(int overworldX, int overworldY, int x, int y);
    static void processRightMenu(bool change);

    struct MonsterKey {
        int overworldX, overworldY, x, y;

        bool operator==(const MonsterKey& other) const {
            return overworldX == other.overworldX && overworldY == other.overworldY && x == other.x && y == other.y;
        }
    };
    struct MonsterKeyHash {
        std::size_t operator()(const MonsterKey& key) const {
            return std::hash<int>()(key.overworldX) ^ std::hash<int>()(key.overworldY) ^ std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
        }
    };
    static std::unordered_map<MonsterKey, bool, MonsterKeyHash> monsterKilledMap;
};

#endif