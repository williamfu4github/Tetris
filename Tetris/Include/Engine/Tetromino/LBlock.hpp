#ifndef LBlock_hpp
#define LBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class LBlock : public TetrominoBlock {
public:
    LBlock();
    ~LBlock() override;
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
