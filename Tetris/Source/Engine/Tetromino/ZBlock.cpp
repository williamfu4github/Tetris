#include "Engine/Tetromino/ZBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attempt must be in [0, 4]
Position ZBlock::rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt) {
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
    return wallKicks[attempt];
}

vector<Position> ZBlock::tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase) {
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            return vector<Position>{Position(0, 0), Position(0, 1), Position(-1, 1), Position(-1, 2)};
        case TetrominoBlock::TetrominoPhase::RIGHT:
            return vector<Position>{Position(0, 2), Position(-1, 2), Position(-1, 1), Position(-2, 1)};
        case TetrominoBlock::TetrominoPhase::DOWN:
            return vector<Position>{Position(-2, 2), Position(-2, 1), Position(-1, 1), Position(-1, 0)};
        case TetrominoBlock::TetrominoPhase::LEFT:
            return vector<Position>{Position(-2, 0), Position(-1, 0), Position(-1, 1), Position(0, 1)};
    }
}

ZBlock::ZBlock():
    TetrominoBlock() {
}

ZBlock::~ZBlock() {
}

// POST: caller must free returned pointer
TetrominoBlock* ZBlock::createClone() const {
    return new ZBlock(*this);
}

TetrominoType ZBlock::getBlockType() const {
    return TetrominoType::Z;
}

vector<Position> ZBlock::getTileCanonicalPositions() const {
    return ZBlock::tileRelativePositions(TetrominoBlock::tetrominoInitialPhase);
}

vector<Position> ZBlock::getTileRelativePositions() const {
    return ZBlock::tileRelativePositions(blockPhase);
}

// PRE: attempt must be in [0, 4]
Position ZBlock::getRotationWallKick(int attempt) const {
    return ZBlock::rotationWallKick(blockPhase, attempt);
}
