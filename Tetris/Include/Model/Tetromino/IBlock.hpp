#ifndef IBlock_hpp
#define IBlock_hpp

#include "Model/Tetromino/TetrominoBlock.hpp"

class IBlock : public TetrominoBlock {
public:
    IBlock();
    ~IBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
private:
    Position getRotationWallKick(int attemptNumber) const override;
    std::vector<Position> getTileRelativePositions() const override;
    
private:
    static Position rotationWallKick(TetrominoBlock::TetrominoPhase blockPhase, int attemptNumber);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);
};

#endif
