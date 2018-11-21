#include "Engine/Tetromino/IBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position IBlock::rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attemptNumber) {
    vector<Position> wallKicks;
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            wallKicks = {Position(0, 0), Position(0, -2), Position(0, 1), Position(-1, -2), Position(2, 1)};
            break;
        case TetrominoBlock::TetrominoPhase::RIGHT:
            wallKicks = {Position(0, 0), Position(0, -1), Position(0, 2), Position(2, -1), Position(-1, 2)};
            break;
        case TetrominoBlock::TetrominoPhase::DOWN:
            wallKicks = {Position(0, 0), Position(0, 2), Position(0, -1), Position(1, 2), Position(-2, -1)};
            break;
        case TetrominoBlock::TetrominoPhase::LEFT:
            wallKicks = {Position(0, 0), Position(0, 1), Position(0, -2), Position(-2, 1), Position(1, -2)};
            break;
    }
    return wallKicks[attemptNumber];
}

vector<Position> IBlock::tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase) {
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            return vector<Position>{Position(-1, 0), Position(-1, 1), Position(-1, 2), Position(-1, 3)};
        case TetrominoBlock::TetrominoPhase::RIGHT:
            return vector<Position>{Position(0, 2), Position(-1, 2), Position(-2, 2), Position(-3, 2)};
        case TetrominoBlock::TetrominoPhase::DOWN:
            return vector<Position>{Position(-2, 3), Position(-2, 2), Position(-2, 1), Position(-2, 0)};
        case TetrominoBlock::TetrominoPhase::LEFT:
            return vector<Position>{Position(-3, 1), Position(-2, 1), Position(-1, 1), Position(0, 1)};
    }
}

IBlock::IBlock():
    TetrominoBlock() {
}

IBlock::~IBlock() {
}

// POST: caller must free returned pointer
TetrominoBlock* IBlock::createClone() const {
    return new IBlock(*this);
}

TetrominoType IBlock::getBlockType() const {
    return TetrominoType::I;
}

// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position IBlock::getRotationWallKick(int attemptNumber) const {
    return IBlock::rotationWallKick(blockPhase, attemptNumber);
}

vector<Position> IBlock::getTileRelativePositions() const {
    return IBlock::tileRelativePositions(blockPhase);
}
