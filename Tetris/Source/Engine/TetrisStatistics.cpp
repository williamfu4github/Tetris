#include "Engine/TetrisStatistics.hpp"

#include "Engine/TetrisLevel.hpp"

TetrisStatistics::TetrisStatistics():
    totalLineCleared(0) {
    gameLevel = new TetrisLevel;
}

TetrisStatistics::~TetrisStatistics() {
    delete gameLevel;
}

void TetrisStatistics::addClearedLines(int numberOfLines) {
    gameLevel->addClearedLines(numberOfLines);
    totalLineCleared += numberOfLines;
}

int TetrisStatistics::getGameLevel() const {
    return gameLevel->getGameLevel();
}
