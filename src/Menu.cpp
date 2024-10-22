#include "Menu.hpp"

#include <string>
#include <vector>

#include "Screen.hpp"

void Menu::display() {
    // do stuff
    Screen::updateTerminal(x - cursorOffset, y + 1 + cursorLocationPrev * spaceBetweenButtons, " \x3", false, defaultColor);
    Screen::updateTerminalColor(x, y + cursorLocation * spaceBetweenButtons, 3, buttonWidth + 2, defaultColor);
    std::string buttonName;

    for (int i = 0; i < buttonCount; i++) {
        std::string line = "";
        for (int j = 0; j < buttonWidth; j++) {
            line += "-";
        }
        line += "\x3";
        int buttonStringLength = buttonNames[i].length();
        if (buttonStringLength < buttonWidth) {
            int difference = buttonWidth - buttonStringLength - 2;
            int leftPadding = difference / 2;
            int rightPadding = difference - leftPadding;
            buttonName = "#" + std::string(leftPadding, ' ') + buttonNames[i] + std::string(rightPadding, ' ') + "#" + "\x3";
            ;
        }
        Screen::updateTerminal(x, y + i * spaceBetweenButtons, line.c_str(), false, defaultColor);
        Screen::updateTerminal(x, y + i * spaceBetweenButtons + 1, buttonName.c_str(), false, defaultColor);
        Screen::updateTerminal(x, y + i * spaceBetweenButtons + 2, line.c_str(), false, defaultColor);
    }
    if (cursorLocation != -1) {
        Screen::updateTerminalColor(x - cursorOffset, y + cursorLocation * spaceBetweenButtons, 3, buttonWidth + cursorOffset, menuSelectedColor);
        Screen::updateTerminal(x - cursorOffset, y + 1 + cursorLocation * spaceBetweenButtons, "*\x3", false, menuSelectedColor);
        cursorLocationPrev = cursorLocation;
    }
}

void Menu::handleMovement(int direction) {
    if (direction == 0) {
        cursorLocation++;
        if (cursorLocation >= buttonCount) {
            cursorLocation = 0;
        }
    } else if (direction == 1) {
        cursorLocation--;
        if (cursorLocation < 0) {
            cursorLocation = buttonCount - 1;
        }
    } else if (direction == -1) {
        cursorLocation = 0;
    } else if (direction == -2) {
        cursorLocationPrev = cursorLocation;
        cursorLocation = -1;
    }
    display();
}

Menu::Menu(int x, int y, int buttonWidth, int spaceBetweenButtons, int cursorOffset, std::vector<std::string> buttonNames) {
    this->x = x;
    this->y = y;
    this->buttonWidth = buttonWidth;
    this->spaceBetweenButtons = spaceBetweenButtons;
    this->cursorOffset = cursorOffset;
    this->buttonNames = buttonNames;
    this->buttonCount = buttonNames.size();
    cursorLocation = 0;
}