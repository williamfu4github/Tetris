#include "Engine/TetrisLevel.hpp"

#include <algorithm>

// TODO change the placeholder
const int TetrisLevel::levelMax = 5;

int TetrisLevel::lineValue(int numberOfLines) {
    switch (numberOfLines) {
        case 1:
            return 1;
        case 2:
            return 3;
        case 3:
            return 5;
        case 4:
            return 8;
        default:
            return 0;
    }
}

// NOTE: variable goal level-up system
int TetrisLevel::levelLineValueTarget(int gameLevel) {
    return (gameLevel * 5);
}

TetrisLevel::TetrisLevel():
    gameLevel(1) {
    lineValueToNext = TetrisLevel::levelLineValueTarget(1);
}

TetrisLevel::~TetrisLevel() {
}

void TetrisLevel::addClearedLines(int numberOfLines) {
    int newValue = TetrisLevel::lineValue(numberOfLines);
    while (newValue > 0) {
        if (newValue >= lineValueToNext) {
            newValue -= lineValueToNext;
            gameLevel ++;
            lineValueToNext = TetrisLevel::levelLineValueTarget(gameLevel);
        }
        else {
            lineValueToNext -= newValue;
            newValue = 0;
        }
    }
    gameLevel = std::min(gameLevel, TetrisLevel::levelMax);
}

int TetrisLevel::getGameLevel() const {
    return gameLevel;
}
