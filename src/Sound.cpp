#include "Sound.hpp"

#include <SFML/Audio.hpp>
#include <chrono>
#include <iostream>
#include <thread>

#include "Main.hpp"

sf::Music Sound::music;
sf::Music Sound::music2;
int currentState = -1;

void Sound::playMusic(const char* musicPath, sf::Music& music) {
    if (!music.openFromFile(musicPath)) {
        std::cout << "Error: Could not load music file: " << musicPath << std::endl;
        return;
    }
    music.setLoop(true);
    music.play();
}

void Sound::stopMusic() {
    music.stop();
}

void Sound::soundInit() {
    music.setPitch(1.0f);
    music.setVolume(80.0f);
    music2.setPitch(1.0f);
    music2.setVolume(80.0f);
}

void Sound::soundManager() {
    while (!Main::quit) {
        if (Main::gameState == 0) {
            if (currentState != 0) {
                music.stop();
                music2.stop();
                Sound::playMusic("assets/mus/mus_menu.ogg", music);
                currentState = 0;
            }
        } else if (Main::gameState == 1) {
            if (currentState != 1) {
                music.stop();
                if (music2.getStatus() != sf::Music::Playing && music2.getStatus() != sf::Music::Paused) {
                    Sound::playMusic("assets/mus/mus_overworld.ogg", music2);
                } else {
                    music2.play();
                }
                currentState = 1;
            }
        } else if (Main::gameState == 2) {
            if (currentState != 2) {
                music.stop();
                music2.pause();
                Sound::playMusic("assets/mus/mus_battle.ogg", music);
                currentState = 2;
            }
        } else if (Main::gameState == 3) {
            if (currentState != 3) {
                music.stop();
                Sound::playMusic("assets/mus/mus_gameover.ogg", music);
                currentState = 3;
            }
        } else {
            music.stop();
        }
        sf::sleep(sf::milliseconds(50));
    }
    music.stop();
}

void Sound::playSound(const char* soundPath) {
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();
    while (sound.getStatus() == sf::Sound::Playing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    sound.stop();
}
