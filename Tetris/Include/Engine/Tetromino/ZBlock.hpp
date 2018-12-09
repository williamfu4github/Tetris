#ifndef ZBlock_hpp
#define ZBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class ZBlock : public TetrominoBlock {
private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);

public:
    ZBlock();
    ~ZBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileCanonicalPositions() const override;
private:
    std::vector<Position> getTileRelativePositions() const override;
    Position getRotationWallKick(int attempt) const override;
};

#endif
