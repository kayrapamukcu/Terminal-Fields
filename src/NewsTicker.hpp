#ifndef NEWSTICKER_H
#define NEWSTICKER_H

#include <string>
#include <vector>

class NewsTicker {
   public:
    static std::vector<std::string> news;
    static void addNews(std::string newsItem);
    static void printNews();
    static void changeSize(int width, int height, int count, int x, int y);
    NewsTicker(int width, int height, int count, int x, int y);
    static bool renderTicker;
   private:
    static float timeOfNews[4];
    static int width;
    static int height;
    static int count;
    static int x;
    static int y;
};

#endif