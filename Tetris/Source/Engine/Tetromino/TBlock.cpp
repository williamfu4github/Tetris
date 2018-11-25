#include "Engine/Tetromino/TBlock.hpp"

using std::vector;

// NOTE: T,S,Z,J,L blocks have same wall kick, I,O blocks are different
// PRE: attempt must be in [0, 4]
Position TBlock::rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt) {
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

vector<Position> TBlock::tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase) {
    switch (blockPhase) {
        case TetrominoBlock::TetrominoPhase::UP:
            return vector<Position>{Position(0, 1), Position(-1, 0), Position(-1, 1), Position(-1, 2)};
        case TetrominoBlock::TetrominoPhase::RIGHT:
            return vector<Position>{Position(-1, 2), Position(0, 1), Position(-1, 1), Position(-2, 1)};
        case TetrominoBlock::TetrominoPhase::DOWN:
            return vector<Position>{Position(-2, 1), Position(-1, 2), Position(-1, 1), Position(-1, 0)};
        case TetrominoBlock::TetrominoPhase::LEFT:
            return vector<Position>{Position(-1, 0), Position(-2, 1), Position(-1, 1), Position(0, 1)};
    }
}

TBlock::TBlock():
    TetrominoBlock() {
}

TBlock::~TBlock() {
}

// POST: caller must free returned pointer
TetrominoBlock* TBlock::createClone() const {
    return new TBlock(*this);
}

TetrominoType TBlock::getBlockType() const {
    return TetrominoType::T;
}

vector<Position> TBlock::getTileRelativePositions() const {
    return TBlock::tileRelativePositions(blockPhase);
}

// PRE: attempt must be in [0, 4]
Position TBlock::getRotationWallKick(int attempt) const {
    return TBlock::rotationWallKick(blockPhase, attempt);
}
