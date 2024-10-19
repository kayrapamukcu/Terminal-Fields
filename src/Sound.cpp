#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Main.hpp"
#include "Sound.hpp"

sf::Music Sound::music;

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

void Sound::soundManager() {
	music.setPitch(1.0f);
	music.setVolume(100.0f);
	int currentState = -1;
	while (!Main::quit) {
		if (Main::gameState == 0) {
			if (currentState != 0) {
				music.stop();
				Sound::playMusic("assets/mus/mus_menu.ogg", music);
				currentState = 0;
			}
		}
		else if (Main::gameState == 1) {
			if (currentState != 1) {
				music.stop();
				Sound::playMusic("assets/mus/mus_overworld.ogg", music);
				currentState = 1;
			}
		}
		else if (Main::gameState == 2) {
			if (currentState != 2) {
				music.stop();
				Sound::playMusic("assets/mus/mus_battle.ogg", music);
				currentState = 2;
			}
		} else if (Main::gameState == 3) {
			if (currentState != 3) {
				music.stop();
				Sound::playMusic("assets/mus/mus_gameover.ogg", music);
				currentState = 3;
			}
		}
		else {
			music.stop();
		}
		sf::sleep(sf::milliseconds(50));
		}
	music.stop();
	}

void Sound::playSound(const char* soundPath)
{
	sf::SoundBuffer buffer;
	sf::Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	while (sound.getStatus() == sf::Sound::Playing) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	sound.stop();
}


