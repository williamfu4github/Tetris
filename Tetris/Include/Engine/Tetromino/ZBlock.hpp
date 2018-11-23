#ifndef ZBlock_hpp
#define ZBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class ZBlock : public TetrominoBlock {
public:
    ZBlock();
    ~ZBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileRelativePositions() const override;
private:
    Position getRotationWallKick(int attemptNumber) const override;

private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attemptNumber);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);
};

#endif
