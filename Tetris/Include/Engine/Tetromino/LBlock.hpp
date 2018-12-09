#ifndef LBlock_hpp
#define LBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class LBlock : public TetrominoBlock {
private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);

public:
    LBlock();
    ~LBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileCanonicalPositions() const override;
private:
    std::vector<Position> getTileRelativePositions() const override;
    Position getRotationWallKick(int attempt) const override;
};

#endif
