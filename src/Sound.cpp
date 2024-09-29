#include <SFML/Audio.hpp>
#include <iostream>
#include <chrono>
#include <thread>

#include "Main.hpp"
#include "Sound.hpp"

void Sound::playMusic(const char* musicPath, sf::Music& music) {
	if (!music.openFromFile(musicPath)) {
		std::cout << "Error: Could not load music file: " << musicPath << std::endl;
		return;
	}
	music.setLoop(true);
	music.play();
}

void Sound::soundManager() {
	sf::Music music;
	Sound::playMusic("assets/mus/mus_menu.ogg", music);
	music.setPitch(0.8f);
	music.setVolume(100.0f);
	while (!Main::quit) {
		if (Main::gameState == 0) {
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
	if (!buffer.loadFromFile(soundPath)) {
		std::cout << "Error: Could not load sound file: " << soundPath << std::endl;
		return;
	}
	sound.setBuffer(buffer);
	sound.play();
	while (sound.getStatus() == sf::Sound::Playing) {
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
	sound.stop();
}


