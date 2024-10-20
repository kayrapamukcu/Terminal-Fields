#pragma once
#include <SFML/Audio.hpp>

#ifndef SOUND_H
#define SOUND_H

class Sound {
public:
	static sf::Music music;
	static void stopMusic();
	static void soundManager();
	static void playSound(const char* soundPath);
	static void playMusic(const char* musicPath, sf::Music& music);
};
#endif