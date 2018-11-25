#ifndef OBlock_hpp
#define OBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class OBlock : public TetrominoBlock {
public:
    OBlock();
    ~OBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileRelativePositions() const override;
private:
    Position getRotationWallKick(int attempt) const override;
    
private:
    static Position rotationWallKick(int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);
};

#endif
