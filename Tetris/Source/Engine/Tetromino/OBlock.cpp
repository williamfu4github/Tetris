#include "Engine/Tetromino/OBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position OBlock::rotationWallKick(int attemptNumber) {
    vector<Position> wallKicks{Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0)};
    return wallKicks[attemptNumber];
}

vector<Position> OBlock::tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase) {
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            return vector<Position>{Position(0, 1), Position(0, 2), Position(-1, 1), Position(-1, 2)};
        case TetrominoBlock::TetrominoPhase::RIGHT:
            return vector<Position>{Position(0, 2), Position(-1, 2), Position(0, 1), Position(-1, 1)};
        case TetrominoBlock::TetrominoPhase::DOWN:
            return vector<Position>{Position(-1, 2), Position(-1, 1), Position(0, 2), Position(0, 1)};
        case TetrominoBlock::TetrominoPhase::LEFT:
            return vector<Position>{Position(0, 2), Position(-1, 2), Position(0, 1), Position(-1, 1)};
    }
}

OBlock::OBlock():
    TetrominoBlock() {
}

OBlock::~OBlock() {
}

// POST: caller must free returned pointer
TetrominoBlock* OBlock::createClone() const {
    return new OBlock(*this);
}

TetrominoType OBlock::getBlockType() const {
    return TetrominoType::O;
}

// PRE: attemptNumber must be in [0, rotationAttemptMax)
Position OBlock::getRotationWallKick(int attemptNumber) const {
    return OBlock::rotationWallKick(attemptNumber);
}

vector<Position> OBlock::getTileRelativePositions() const {
    return OBlock::tileRelativePositions(blockPhase);
}
