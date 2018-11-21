#ifndef OBlock_hpp
#define OBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class OBlock : public TetrominoBlock {
public:
    OBlock();
    ~OBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
private:
    Position getRotationWallKick(int attemptNumber) const override;
    std::vector<Position> getTileRelativePositions() const override;
    
private:
    static Position rotationWallKick(int attemptNumber);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);
};

#endif
