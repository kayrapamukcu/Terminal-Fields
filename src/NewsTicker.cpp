#include <vector>
#include "NewsTicker.hpp"
#include "Screen.hpp"
#include <string>
//#include <iostream>
int NewsTicker::width = 1;
int NewsTicker::height = 1;
int NewsTicker::count = 1;
int NewsTicker::x = 1;
int NewsTicker::y = 1;
std::vector<std::string> NewsTicker::news;
float timeOfNews[4] = { 1.5f };

void NewsTicker::addNews(std::string newsItem) { 
	news.push_back(newsItem);
	if (news.size() > count) {
		news.erase(news.begin());
	}
	timeOfNews[3] = timeOfNews[2];
	timeOfNews[2] = timeOfNews[1];
	timeOfNews[1] = timeOfNews[0];
	timeOfNews[0] = 1.5f;
}

void NewsTicker::printNews() {
	std::string totalText = "";
	Screen::deleteTerminal(x, y, height, width);
	int newLines = 0;
	int newLinesPrev = 0;
	for (int i = news.size(); i > 0; i--) {
		newLines++;
		if (news[i - 1].size() > width) {
			newLines += news[i - 1].size() / width;
		}
		if (newLines >= height) {
			break;
		}
		totalText += news[i - 1] + "\n";
		if (i > static_cast<int>(news.size()) - 4) {
			Screen::updateTerminalColor(x, y + newLinesPrev, newLines - newLinesPrev, width, sf::Color(170 + static_cast<int>(40 * timeOfNews[news.size() - i]), 170 + static_cast<int>(40 * timeOfNews[news.size() - i]), 170 - static_cast<int>(80 * timeOfNews[news.size() - i])));
		}
		newLinesPrev = newLines;
	}
	totalText += "\x3";
	//std::cout << totalText;
	Screen::updateTerminalArea(x, y, width, height, &totalText[0], false, defaultColor, false);
	for (int i = 0; i < 4; i++) {
		if (timeOfNews[i] > 0) {
			timeOfNews[i] -= Screen::deltaTime.asSeconds();
		}
	}
}

void NewsTicker::changeSize(int w, int h, int c, int xC, int yC) {
	width = w;
	height = h;
	count = c;
	x = xC;
	y = yC;
}

NewsTicker::NewsTicker(int width, int height, int count, int x, int y) {
	this->width = width;
	this->height = height;
	this->count = count;
	this->x = x;
	this->y = y;
}

