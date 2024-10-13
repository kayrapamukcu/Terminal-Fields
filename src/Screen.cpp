#include "Screen.hpp"
#include "Main.hpp"
#include <array>
#include <random>
#include <chrono>
#include <thread>
#include <iostream>

bool inTransition = false;
sf::Clock deltaClock;
sf::Time Screen::deltaTime;
sf::RenderWindow* Screen::windowRef = nullptr;

void Screen::renderBarStats(int x, int y, int health, int maxHealth, int mana, int maxMana, bool renderXPBar) {
	Screen::deleteTerminal(x, y, 8, 19, true);
	char barSize[20];
	for (int i = 0; i < 19; ++i) {
    	barSize[i] = -37;
	} //have to initialize the char array like this otherwise it doesn't work for whatever reason lol (extended ascii is weird)
	barSize[19] = '\x3';
	Screen::updateTerminal(x, y, "HP\x3", false, sf::Color::Red);
	Screen::updateTerminal(x, y+1, barSize, false, sf::Color(96,0,0));
	Screen::updateTerminal(x, y+3, "MP\x3", false, sf::Color::Blue);
	Screen::updateTerminal(x, y+4, barSize, false, sf::Color(0,0,96));
	int healthToBeFilled = 0;
	int manaToBeFilled = 0;
	float hpPerBlock = static_cast<float>(maxHealth) / 19.0f;
	float mpPerBlock = static_cast<float>(maxMana) / 19.0f;
	for (int i = 0; i < 19; i++) {
		if (health > (static_cast<float>(maxHealth) / 19.0f) * i) {
			healthToBeFilled++;
		} else {
			Screen::updateTerminalColor(x+i, y+1, 1, 1, sf::Color(96+static_cast<int>(159 * std::fmod(health, hpPerBlock) / hpPerBlock),0,0));
			break;
		}
	}
	for (int i = 0; i < 19; i++) {
		if (mana > (static_cast<float>(maxMana) / 19.0f) * i) {
			manaToBeFilled++;
		} else {
			Screen::updateTerminalColor(x+i, y+4, 1, 1, sf::Color(0,0,96+static_cast<int>(159 * std::fmod(mana, mpPerBlock) / hpPerBlock)));
			break;
		}
	}
	Screen::updateTerminalColor(x, y+1, 1, healthToBeFilled, sf::Color::Red);
	Screen::updateTerminalColor(x, y+4, 1, manaToBeFilled, sf::Color::Blue);

	if(renderXPBar) {
		Screen::updateTerminal(x, y+6, "XP\x3", false, sf::Color(96, 255, 0));
		Screen::updateTerminal(x, y+7, barSize, false, sf::Color(32, 96, 0));
		int xpToBeFilled = 0;
		float xpPerBlock = Player::xpToLevelUp / 19.0f;
		for (int i = 0; i < 19; i++) {
			if (Player::xp > (100.0f / 19.0f) * i) {
				xpToBeFilled++;
			} else {
				Screen::updateTerminalColor(x+i, y+7, 1, 1, sf::Color(32+static_cast<int>(54 * std::fmod(Player::xp, xpPerBlock) / xpPerBlock),96+static_cast<int>(159 * std::fmod(Player::xp, xpPerBlock) / xpPerBlock),0));
				break;
			}
		}
		Screen::updateTerminalColor(x, y+7, 1, xpToBeFilled, sf::Color(96, 255, 0));
	}

	//doing all this so the hp/mana text is right aligned
	std::string statStr = std::to_string(health);
	std::string maxStatStr = std::to_string(maxHealth);
	std::vector<char>statBar(3+statStr.length()+maxStatStr.length(), ' ');
	int ind = 0;
	for (ind = 0; ind < statStr.length(); ind++) {
		statBar[ind] = statStr[ind];
	}
	statBar[ind] = '/';
	ind ++;
	for (int i = 0; i < maxStatStr.length(); i++) {
		statBar[ind] = maxStatStr[i];
		ind++;
	}
	statBar[ind] = '\x3';
	Screen::updateTerminal(x+(19-ind), y+2, &statBar[0], false, sf::Color::Red);
	statStr = std::to_string(mana);
	maxStatStr = std::to_string(maxMana);
	statBar = std::vector<char>(3+statStr.length()+maxStatStr.length(), ' ');
	ind = 0;
	for (ind = 0; ind < statStr.length(); ind++) {
		statBar[ind] = statStr[ind];
	}
	statBar[ind] = '/';
	ind ++;
	for (int i = 0; i < maxStatStr.length(); i++) {
		statBar[ind] = maxStatStr[i];
		ind++;
	}
	statBar[ind] = '\x3';
	Screen::updateTerminal(x+(19-ind), y+5, &statBar[0], false, sf::Color::Blue);
	if (renderXPBar) {
		statStr = std::to_string(Player::xp);
		maxStatStr = std::to_string(Player::xpToLevelUp);
		statBar = std::vector<char>(3+statStr.length()+maxStatStr.length(), ' ');
		ind = 0;
		for (ind = 0; ind < statStr.length(); ind++) {
			statBar[ind] = statStr[ind];
		}
		statBar[ind] = '/';
		ind ++;
		for (int i = 0; i < maxStatStr.length(); i++) {
			statBar[ind] = maxStatStr[i];
			ind++;
		}
		statBar[ind] = '\x3';
		Screen::updateTerminal(x+(19-ind), y+8, &statBar[0], false, sf::Color(0, 255, 0));
	}
}

void Screen::clearTerminalBuffer(bool trueorfalse)
{
	for (int y = 0; y < Main::FIELD_HEIGHT; ++y)
	{
		for (int x = 0; x < Main::FIELD_WIDTH; ++x)
		{
			Main::terminalBuffer[y][x] = trueorfalse;
		}
	}
}

void Screen::clearTerminal()
{
	for (int y = 0; y < Main::FIELD_HEIGHT; ++y)
	{
		for (int x = 0; x < Main::FIELD_WIDTH; ++x)
		{
			Main::terminal[y][x] = ' ';
		}
	}
}

void Screen::clearTerminalColor()
{
	for (int y = 0; y < Main::FIELD_HEIGHT; ++y)
	{
		for (int x = 0; x < Main::FIELD_WIDTH; ++x)
		{
			Main::terminalColor[y][x] = defaultColor;
		}
	}
}

void Screen::deleteTerminal(int x, int y, int h, int w, bool clearColor)
{
	for (int i = y; i < y + h; ++i)
	{
		for (int j = x; j < x + w; ++j)
		{
			Main::terminal[i][j] = ' ';
			if (clearColor)
			{
				Main::terminalColor[i][j] = defaultColor;
			}
		}
	}
}

void Screen::updateTerminalColor(int x, int y, int h, int w, sf::Color color)
{
	for (int i = y; i < y + h; ++i)
	{
		for (int j = x; j < x + w; ++j)
		{
			Main::terminalColor[i][j] = color;
		}
	}
}

void Screen::updateTerminal(int x, int y, const char *text, bool clear, sf::Color color)
{
	if (clear)
	{
		Screen::clearTerminal();
	}
	int height = Main::FIELD_HEIGHT - y;
	int width = Main::FIELD_WIDTH - x;
	int currentLine = 0;
	int currentCol = 0;

	for (int i = 0; i < height * width; i++)
	{
		if (text[i] == '\n')
		{
			currentCol = -1;
			currentLine++;
		}
		else if (text[i] == '\x3')
		{
			break; // i'm sorry, there's probably a better solution but I just don't want to think about it right now
		}
		if (currentCol >= width)
		{
			currentCol = -1;
			currentLine++;
		}
		Main::terminal[y + currentLine][x + currentCol] = text[i];
		Main::terminalColor[y + currentLine][x + currentCol] = color;
		currentCol++;
	}
}

void Screen::updateTerminalArea(int x, int y, int w, int h, const char *text, bool clear, sf::Color color, bool changeColor)
{
	if (clear)
	{
		Screen::clearTerminal();
	}
	int height = h;
	int width = w;
	int currentLine = 0;
	int currentCol = 0;

	for (int i = 0; i < height * width; i++)
	{
		if (text[i] == '\n')
		{
			currentCol = -1;
			currentLine++;
		}
		else if (text[i] == '\x3')
		{
			break; // i'm sorry, there's probably a better solution but I just don't want to think about it right now
		}
		if (currentCol >= width)
		{
			currentCol = 0;
			currentLine++;
		}
		Main::terminal[y + currentLine][x + currentCol] = text[i];
		if (changeColor)
		{
			Main::terminalColor[y + currentLine][x + currentCol] = color;
		}
		currentCol++;
	}
}

void Screen::setCharInVertexArray(sf::VertexArray &terminal, int x, int y, char c, sf::Color color, const sf::Texture &fontTexture)
{
	int index = (y * Main::FIELD_WIDTH + x) * 4;
	int asciiVal;
	// Get texture coordinates for the character
	// Map ASCII to texture coordinates in the sprite sheet
	asciiVal = static_cast<int>(c);
	if (c < 0)
	{
		asciiVal += 256;
	}
	int xx = (asciiVal % 16) * Main::TILE_WIDTH;
	int yy = (asciiVal / 16) * Main::TILE_HEIGHT;
	sf::IntRect rect = sf::IntRect(xx, yy, Main::TILE_WIDTH, Main::TILE_HEIGHT - 1);
	// Set positions
	terminal[index].position = sf::Vector2f(x * Main::TILE_WIDTH, y * Main::TILE_HEIGHT);
	terminal[index + 1].position = sf::Vector2f((x + 1) * Main::TILE_WIDTH, y * Main::TILE_HEIGHT);
	terminal[index + 2].position = sf::Vector2f((x + 1) * Main::TILE_WIDTH, (y + 1) * Main::TILE_HEIGHT - 1);
	terminal[index + 3].position = sf::Vector2f(x * Main::TILE_WIDTH, (y + 1) * Main::TILE_HEIGHT - 1);
	// Set texture coordinates
	terminal[index].texCoords = sf::Vector2f(rect.left, rect.top);
	terminal[index + 1].texCoords = sf::Vector2f(rect.left + Main::TILE_WIDTH, rect.top);
	terminal[index + 2].texCoords = sf::Vector2f(rect.left + Main::TILE_WIDTH, rect.top + Main::TILE_HEIGHT - 1);
	terminal[index + 3].texCoords = sf::Vector2f(rect.left, rect.top + Main::TILE_HEIGHT - 1);
	// Set color
	terminal[index].color = color;
	terminal[index + 1].color = color;
	terminal[index + 2].color = color;
	terminal[index + 3].color = color;
}

void Screen::transition(int direction, float transitionTime, bool clearOrDraw)
{ // direction 0 = bottom to top, 1 = top to bottom, 2 = right to left, 3 = left to right, 4 = circling
	Main::renderTerminalBuffer = true;
	std::array<int, std::max(Main::FIELD_WIDTH, Main::FIELD_HEIGHT)> arr;
	for (int i = 0; i < std::max(Main::FIELD_WIDTH, Main::FIELD_HEIGHT); ++i)
	{
		arr[i] = -1 * (i % Main::TRANSITION_VARIETY);
	}
	int currentLine = 1;
	int xOffset = 0;
	int yOffset = 0;
	std::random_device rd;
	std::shuffle(arr.begin(), arr.end(), rd);
	sf::Clock clock;

	for (int i = 0; i < Main::TRANSITION_VARIETY; ++i) {
		if (direction == 3) {
			for (int i = xOffset; i < currentLine; i++) {
				for (int j = 0; j < Main::FIELD_HEIGHT; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						if (arr[j] + i >= 0 && arr[j] + i < Main::FIELD_WIDTH) {
							Main::terminalBuffer[j][i + arr[j]] = clearOrDraw;
							clock.restart();
						}
					}
					else {
						j--;
					}
				}
				currentLine++;
				if (currentLine > Main::FIELD_WIDTH + Main::TRANSITION_VARIETY) {
					break;
				}
				if (currentLine > Main::TRANSITION_VARIETY) {
					xOffset = currentLine - Main::TRANSITION_VARIETY;
				}
			}
		}
		else if (direction == 2) {
			for (int i = Main::FIELD_WIDTH - xOffset; i > Main::FIELD_WIDTH - currentLine; i--) {
				for (int j = 0; j < Main::FIELD_HEIGHT; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						if (i - arr[j] >= 0 && i - arr[j] < Main::FIELD_WIDTH) {
							Main::terminalBuffer[j][i - arr[j]] = clearOrDraw;
							clock.restart();
						}
					}
					else {
						j--;
					}
				}
				currentLine++;
				if (currentLine > Main::FIELD_WIDTH + Main::TRANSITION_VARIETY) {
					break;
				}
				if (currentLine > Main::TRANSITION_VARIETY) {
					xOffset = currentLine - Main::TRANSITION_VARIETY;
				}
			}
		}
		else if (direction == 1) {
			for (int i = yOffset; i < currentLine; i++) {
				for (int j = 0; j < Main::FIELD_WIDTH; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						if (arr[j] + i >= 0 && arr[j] + i < Main::FIELD_HEIGHT) {
							Main::terminalBuffer[i + arr[j]][j] = clearOrDraw;
							clock.restart();
						}
					}
					else {
						j--;
					}
				}
				currentLine++;
				if (currentLine > Main::FIELD_HEIGHT + Main::TRANSITION_VARIETY) {
					break;
				}
				if (currentLine > Main::TRANSITION_VARIETY) {
					yOffset = currentLine - Main::TRANSITION_VARIETY;
				}
			}
		}
		else if (direction == 0) {
			for (int i = Main::FIELD_HEIGHT - yOffset; i > Main::FIELD_HEIGHT - currentLine; i--) {
				for (int j = 0; j < Main::FIELD_WIDTH; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						if (i - arr[j] >= 0 && i - arr[j] < Main::FIELD_HEIGHT) {
							Main::terminalBuffer[i - arr[j]][j] = clearOrDraw;
							clock.restart();
						}
					}
					else {
						j--;
					}
				}
				currentLine++;
				if (currentLine > Main::FIELD_HEIGHT + Main::TRANSITION_VARIETY) {
					break;
				}
				if (currentLine > Main::TRANSITION_VARIETY) {
					yOffset = currentLine - Main::TRANSITION_VARIETY;
				}
			}
		}
		else if (direction == 4) {
			for (int i = 0; i < std::min(Main::FIELD_WIDTH, Main::FIELD_HEIGHT) / 2; i++) {
				for (int j = xOffset; j < Main::FIELD_WIDTH - xOffset; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						Main::terminalBuffer[i][j] = clearOrDraw;
						clock.restart();
					}
					else {
						j--;
					}
				}
				for (int j = yOffset; j < Main::FIELD_HEIGHT - yOffset; j++) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						Main::terminalBuffer[j][Main::FIELD_WIDTH - 1 - xOffset] = clearOrDraw;
						clock.restart();
					}
					else {
						j--;
					}
				}
				for (int j = Main::FIELD_WIDTH - xOffset - 1; j >= 0 + xOffset; j--) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						Main::terminalBuffer[Main::FIELD_HEIGHT - 1 - yOffset][j] = clearOrDraw;
						clock.restart();
					}
					else {
						j++;
					}
				}
				for (int j = Main::FIELD_HEIGHT - yOffset - 1; j >= 0 + yOffset; j--) {
					if (clock.getElapsedTime().asSeconds() >= transitionTime) {
						Main::terminalBuffer[j][i] = clearOrDraw;
						clock.restart();
					}
					else {
						j++;
					}
				}
				xOffset++;
				yOffset++;
			}
		}
	}
	Main::renderTerminalBuffer = false;
}

void Screen::screenManager(sf::RenderWindow &window)
{
	// window.setVerticalSyncEnabled(Main::VSYNC); //vsync
	windowRef = &window;
	sf::Texture fontTexture;
	if (!fontTexture.loadFromFile("assets/img/raster_font.png"))
	{
		return;
	}

	while (window.isOpen())
	{
		sf::VertexArray terminalDraw(sf::Quads, Main::FIELD_WIDTH * Main::FIELD_HEIGHT * 4); // 4 vertices per character (quad)
		window.clear();
		Main::ticker.printNews();
		if (Main::renderTerminalBuffer)
		{
			for (int i = 0; i < Main::FIELD_HEIGHT; ++i)
			{
				for (int j = 0; j < Main::FIELD_WIDTH; ++j)
				{
					if (Main::terminal[i][j] == '\n')
					{
						continue;
					}
					if (Main::terminalBuffer[i][j])
					{
						Screen::setCharInVertexArray(terminalDraw, j, i, Main::terminal[i][j], Main::terminalColor[i][j], fontTexture);
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < Main::FIELD_HEIGHT; ++i)
			{
				for (int j = 0; j < Main::FIELD_WIDTH; ++j)
				{
					if (Main::terminal[i][j] == '\n')
					{
						continue;
					}
					Screen::setCharInVertexArray(terminalDraw, j, i, Main::terminal[i][j], Main::terminalColor[i][j], fontTexture);
				}
			}
		}
		window.draw(terminalDraw, &fontTexture);
		window.display();
		Screen::deltaTime = deltaClock.restart();
	}
}