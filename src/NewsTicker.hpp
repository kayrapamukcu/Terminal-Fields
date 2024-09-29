#ifndef NEWSTICKER_H
#define NEWSTICKER_H

#include <vector>
#include <string>

class NewsTicker {
public:
	static std::vector<std::string> news;
	static void addNews(std::string newsItem);
	static void printNews();
	static void changeSize(int width, int height, int count, int x, int y);
	static int width;
	static int height;
	static int count;
	static int x;
	static int y;
	NewsTicker(int width, int height, int count, int x, int y);
};

#endif