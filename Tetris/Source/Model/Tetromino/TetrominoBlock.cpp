#include "Model/Tetromino/TetrominoBlock.hpp"

using std::vector;

const int TetrominoBlock::rotationAttemptMax = 5;

TetrominoBlock::~TetrominoBlock() {
}

void TetrominoBlock::setBlockPosition(Position newPosition) {
    blockPosition = newPosition;
}

void TetrominoBlock::shiftLeft() {
    blockPosition.column --;
}

void TetrominoBlock::shiftRight() {
    blockPosition.column ++;
}

void TetrominoBlock::shiftDown() {
    blockPosition.row --;
}

void TetrominoBlock::shiftUp() {
    blockPosition.row ++;
}

// PRE: attemptNumber must be in [0, rotationAttemptMax)
void TetrominoBlock::rotateClockwise(int attemptNumber) {
    Position wallKick = this->getRotationWallKick(attemptNumber);
    blockPosition.row += wallKick.row;
    blockPosition.column += wallKick.column;
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            blockPhase = TetrominoBlock::TetrominoPhase::RIGHT;
            break;
        case TetrominoBlock::TetrominoPhase::RIGHT:
            blockPhase = TetrominoBlock::TetrominoPhase::DOWN;
            break;
        case TetrominoBlock::TetrominoPhase::DOWN:
            blockPhase = TetrominoBlock::TetrominoPhase::LEFT;
            break;
        case TetrominoBlock::TetrominoPhase::LEFT:
            blockPhase = TetrominoBlock::TetrominoPhase::UP;
            break;
    }
}

// PRE: attemptNumber must be in [0, rotationAttemptMax)
void TetrominoBlock::rotateCounterClockwise(int attemptNumber) {
    Position wallKick = this->getRotationWallKick(attemptNumber);
    blockPosition.row -= wallKick.row;
    blockPosition.column -= wallKick.column;
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            blockPhase = TetrominoBlock::TetrominoPhase::LEFT;
            break;
        case TetrominoBlock::TetrominoPhase::RIGHT:
            blockPhase = TetrominoBlock::TetrominoPhase::UP;
            break;
        case TetrominoBlock::TetrominoPhase::DOWN:
            blockPhase = TetrominoBlock::TetrominoPhase::RIGHT;
            break;
        case TetrominoBlock::TetrominoPhase::LEFT:
            blockPhase = TetrominoBlock::TetrominoPhase::DOWN;
            break;
    }
}

vector<Position> TetrominoBlock::getTilePositions() const {
    vector<Position> tilePositions = this->getTileRelativePositions();
    for (Position& position : tilePositions) {
        position.row += blockPosition.row;
        position.column += blockPosition.column;
    }
    return tilePositions;
}

TetrominoBlock::TetrominoBlock():
    blockPosition(0, 0),
    blockPhase(TetrominoBlock::TetrominoPhase::UP) {
}