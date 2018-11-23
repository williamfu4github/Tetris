#ifndef TetrominoBlock_hpp
#define TetrominoBlock_hpp

#include "Utility/Position.hpp"
#include "Engine/Tetromino/TetrominoType.hpp"
#include <vector>

class TetrominoBlock {
protected:
    enum class TetrominoPhase {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
    
public:
    virtual ~TetrominoBlock() = 0;
    virtual TetrominoBlock* createClone() const = 0;
    virtual TetrominoType getBlockType() const = 0;
    void setBlockPosition(Position newPosition);
    void shiftLeft();
    void shiftRight();
    void shiftDown();
    void shiftUp();
    void rotateClockwise(int attemptNumber);
    void rotateCounterClockwise(int attemptNumber);
    std::vector<Position> getTilePositions() const;
    virtual std::vector<Position> getTileRelativePositions() const = 0;
protected:
    TetrominoBlock();
private:
    virtual Position getRotationWallKick(int attemptNumber) const = 0;
    
protected:
    Position blockPosition;
    TetrominoBlock::TetrominoPhase blockPhase;
};

#endif
