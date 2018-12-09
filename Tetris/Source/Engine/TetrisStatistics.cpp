#include "Engine/TetrisStatistics.hpp"

TetrisStatistics::TetrisStatistics() {
    lineCleared = 0;
}

TetrisStatistics::~TetrisStatistics() {
}

// NOTE: fixed-goal level system
int TetrisStatistics::getGameLevel() const {
    return (lineCleared / 10) + 1;
}
