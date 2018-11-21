#include "Engine/Tetromino/LBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position LBlock::rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attemptNumber) {
    vector<Position> wallKicks;
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            wallKicks = {Position(0, 0), Position(0, -1), Position(1, -1), Position(-2, 0), Position(-2, -1)};
            break;
        case TetrominoBlock::TetrominoPhase::RIGHT:
            wallKicks = {Position(0, 0), Position(0, 1), Position(-1, 1), Position(2, 0), Position(2, 1)};
            break;
        case TetrominoBlock::TetrominoPhase::DOWN:
            wallKicks = {Position(0, 0), Position(0, 1), Position(1, 1), Position(-2, 0), Position(-2, 1)};
            break;
        case TetrominoBlock::TetrominoPhase::LEFT:
            wallKicks = {Position(0, 0), Position(0, -1), Position(-1, -1), Position(2, 0), Position(2, -1)};
            break;
    }
    return wallKicks[attemptNumber];
}

vector<Position> LBlock::tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase) {
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            return vector<Position>{Position(0, 2), Position(-1, 0), Position(-1, 1), Position(-1, 2)};
        case TetrominoBlock::TetrominoPhase::RIGHT:
            return vector<Position>{Position(-2, 2), Position(0, 1), Position(-1, 1), Position(-2, 1)};
        case TetrominoBlock::TetrominoPhase::DOWN:
            return vector<Position>{Position(-2, 0), Position(-1, 2), Position(-1, 1), Position(-1, 0)};
        case TetrominoBlock::TetrominoPhase::LEFT:
            return vector<Position>{Position(0, 0), Position(-2, 1), Position(-1, 1), Position(0, 1)};
    }
}

LBlock::LBlock():
    TetrominoBlock() {
}

LBlock::~LBlock() {
}

// POST: caller must free returned pointer
TetrominoBlock* LBlock::createClone() const {
    return new LBlock(*this);
}

TetrominoType LBlock::getBlockType() const {
    return TetrominoType::L;
}

// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position LBlock::getRotationWallKick(int attemptNumber) const {
    return LBlock::rotationWallKick(blockPhase, attemptNumber);
}

vector<Position> LBlock::getTileRelativePositions() const {
    return LBlock::tileRelativePositions(blockPhase);
}
