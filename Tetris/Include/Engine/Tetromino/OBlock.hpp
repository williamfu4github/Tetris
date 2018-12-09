#ifndef OBlock_hpp
#define OBlock_hpp

#include "Engine/Tetromino/TetrominoBlock.hpp"

class OBlock : public TetrominoBlock {
private:
    static Position rotationWallKick(int attempt);
    static std::vector<Position> tileRelativePositions(TetrominoBlock::TetrominoPhase blockPhase);

public:
    OBlock();
    ~OBlock() override;
    TetrominoBlock* createClone() const override;
    TetrominoType getBlockType() const override;
    std::vector<Position> getTileCanonicalPositions() const override;
private:
    std::vector<Position> getTileRelativePositions() const override;
    Position getRotationWallKick(int attempt) const override;
};

#endif
