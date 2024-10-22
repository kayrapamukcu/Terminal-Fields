#include <cmath>
#include <random>
#include <string>

#include "../Enemy.hpp"

// TODO: IMPLEMENT A DAMAGE DEAL FUNCTION
// todo: make the enemies actually have interesting attacks (currently ai filled out a lot of it)

class FreakyFrog : public Enemy {
   public:
    FreakyFrog() : Enemy("Freaky Frog", 20, 10, 3, 1, 15, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 5) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("Freaky Frog jumps at you, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-5, false);
            } else {
                int addedMana = (2 + dist(gen) % 5);
                Main::ticker.addNews("Freaky Frog concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Freaky Frog slashes with its tongue, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class Werewolf : public Enemy {
   public:
    Werewolf() : Enemy("Werewolf", 60, 25, 5, 2, 50, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        dmg = 0;
        if (dist(gen) / 10 * (sqrt(maxHealth / (health + maxHealth / 20))) > 10) {
            if (mana >= 12) {
                int heal = 6 + dist(gen) % 16;
                Battle::manaControl(-12, false);
                Main::ticker.addNews("Werewolf howls, healing itself for " + std::to_string(heal) + " HP!");
            } else {
                int addedMana = (4 + dist(gen) % 10);
                Main::ticker.addNews("Werewolf desperately concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            if (dist(gen) < 20) {
                if (mana >= 6) {
                    Battle::manaControl(-6, false);
                    dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                    Main::ticker.addNews("Werewolf slashes at you, dealing " + std::to_string(dmg) + " damage!");
                    Battle::healthControl(-dmg, true);
                } else {
                    int addedMana = (2 + dist(gen) % 5);
                    Main::ticker.addNews("Werewolf concentrates for " + std::to_string(addedMana) + " MP!");
                    Battle::manaControl(addedMana, false);
                }
            } else {
                dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
                Main::ticker.addNews("Werewolf hits you, dealing " + std::to_string(dmg) + " damage!");
                Battle::healthControl(-dmg, true);
            }
        }
    };
};

class LivingScarecrow : public Enemy {
   public:
    LivingScarecrow() : Enemy("Living Scarecrow", 40, 15, 4, 0, 20, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 6) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("Living Scarecrow throws a pumpkin at you, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-6, false);
            } else {
                int addedMana = (2 + dist(gen) % 5);
                Main::ticker.addNews("Living Scarecrow concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Living Scarecrow swings its scythe, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class MassiveBat : public Enemy {
   public:
    MassiveBat() : Enemy("Massive Bat", 30, 20, 4, 1, 20, 3) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 8) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("Massive Bat screeches, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-8, false);
            } else {
                int addedMana = (2 + dist(gen) % 5);
                Main::ticker.addNews("Massive Bat concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Massive Bat bites you, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class RockGolem : public Enemy {
   public:
    RockGolem() : Enemy("Rock Golem", 100, 10, 1, 10, 30, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 10) {
                Main::ticker.addNews("Rock Golem raises defense runes around itself...");
                Main::ticker.addNews("Rock Golem's defense increased for 5 turns!");  // TODO: implement. add status effect(and remove this ticker from here its temporary)
                Battle::manaControl(-10, false);
            } else {
                int addedMana = 10;
                Main::ticker.addNews("Rock Golem concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Rock Golem punches you, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class PossessedTractor : public Enemy {
   public:
    PossessedTractor() : Enemy("Possessed Tractor", 50, 0, 2, 10, 15, 0) {}  // no mana, only physical attacks
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
        Main::ticker.addNews("Possessed Tractor rams you, dealing " + std::to_string(dmg) + " damage!");
        Battle::healthControl(-dmg, true);
    }
};

class CarnivorousPlant : public Enemy {
   public:
    CarnivorousPlant() : Enemy("Carnivorous Plant", 40, 5, 3, 5, 20, 0) {}  // poisonous pollen giving you the poisonous status effect, maybe a suffocating mana attack?
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 6) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("Carnivorous Plant releases poisonous pollen, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-6, false);
            } else {
                int addedMana = (2 + dist(gen) % 5);
                Main::ticker.addNews("Carnivorous Plant concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Carnivorous Plant bites you, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class CursedCow : public Enemy {
   public:
    CursedCow() : Enemy("Cursed Cow", 50, 50, 2, 3, 20, 0) {}  // poisonous milk
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 6) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("Cursed Cow spits poisonous milk at you, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-6, false);
            } else {
                int addedMana = (2 + dist(gen) % 5);
                Main::ticker.addNews("Cursed Cow concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("Cursed Cow kicks you, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};

class EnragedRam : public Enemy {
   public:
    EnragedRam() : Enemy("Enraged Ram", 35, 10, 4, 3, 25, 0) {}
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
        Main::ticker.addNews("Enraged Ram charges at you, dealing " + std::to_string(dmg) + " damage!");
        Battle::healthControl(-dmg, true);
    }
};

class TheSerpent : public Enemy {  // boss
   public:
    TheSerpent() : Enemy("The Serpent", 150, 50, 6, 5, 500, 0) {}
    // You find yourself unable to do magic moves as you find yourself frozen in fear. (serpent magic move)
    std::string getArt() override {
        return "  O\n\\_|_/\n  |\n / \\\x3";
    }
    void behavior() override {
        std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<> dist(0, 100);
        if (dist(gen) < 20) {
            if (mana >= 10) {
                dmg = 1 + capNumber(atk * 2 - Player::def, 1, 100) * (1 + dist(gen) % 3);
                Main::ticker.addNews("The Serpent freezes you in fear, dealing " + std::to_string(dmg) + " damage!");
                Battle::manaControl(-10, false);
            } else {
                int addedMana = (4 + dist(gen) % 10);
                Main::ticker.addNews("The Serpent concentrates for " + std::to_string(addedMana) + " MP!");
                Battle::manaControl(addedMana, false);
            }
        } else {
            dmg = capNumber(atk - Player::def, 1, 100) * (1 + dist(gen) % 2);
            Main::ticker.addNews("The Serpent bites you, dealing " + std::to_string(dmg) + " damage!");
        }
        Battle::healthControl(-dmg, true);
    }
};