#include "Engine/Tetromino/OBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attempt must be in [0, 4]
Position OBlock::rotationWallKick(int attempt) {
    vector<Position> wallKicks{Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0), Position(0, 0)};
    return wallKicks[attempt];
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

vector<Position> OBlock::getTileCanonicalPositions() const {
    return OBlock::tileRelativePositions(TetrominoBlock::tetrominoInitialPhase);
}

vector<Position> OBlock::getTileRelativePositions() const {
    return OBlock::tileRelativePositions(blockPhase);
}

// PRE: attempt must be in [0, 4]
Position OBlock::getRotationWallKick(int attempt) const {
    return OBlock::rotationWallKick(attempt);
}
