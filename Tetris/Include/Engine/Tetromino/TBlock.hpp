#ifndef TBlock_hpp
#define TBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class TBlock : public TetrominoBlock {
public:
    TBlock();
    ~TBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileRelativePositions() const override;
private:
    Position getRotationWallKick(int attempt) const override;

private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);
};

#endif
