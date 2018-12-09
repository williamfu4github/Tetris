#ifndef TetrominoBlock_hpp
#define TetrominoBlock_hpp

#include "Utility/Position.hpp"
#include "Engine/Tetromino/TetrominoType.hpp"
#include <vector>

class TetrominoBlock {
public:
    enum class TetrominoPhase {
        UP,
        RIGHT,
        DOWN,
        LEFT
    };
public:
    static const TetrominoBlock::TetrominoPhase tetrominoInitialPhase;
    
public:
    virtual ~TetrominoBlock() = 0;
    virtual TetrominoBlock* createClone() const = 0;
    virtual TetrominoType getBlockType() const = 0;
    void setBlockPosition(Position newPosition);
    void setBlockPhase(TetrominoBlock::TetrominoPhase newPhase);
    void shiftLeft();
    void shiftRight();
    void shiftDown();
    void shiftUp();
    void rotateClockwise(int attempt);
    void rotateCounterClockwise(int attempt);
    std::vector<Position> getTilePositions() const;
    virtual std::vector<Position> getTileCanonicalPositions() const = 0;
protected:
    TetrominoBlock();
private:
    virtual std::vector<Position> getTileRelativePositions() const = 0;
    virtual Position getRotationWallKick(int attempt) const = 0;
    
protected:
    Position blockPosition;
    TetrominoBlock::TetrominoPhase blockPhase;
};

#endif
