#ifndef SBlock_hpp
#define SBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class SBlock : public TetrominoBlock {
private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);

public:
    SBlock();
    ~SBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileCanonicalPositions() const override;
private:
    std::vector<Position> getTileRelativePositions() const override;
    Position getRotationWallKick(int attempt) const override;
};

#endif
