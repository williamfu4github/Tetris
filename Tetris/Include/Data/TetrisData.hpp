#ifndef TetrisData_hpp
#define TetrisData_hpp

#include "Utility/Position.hpp"
#include "Driver/GameState.hpp"
#include "Engine/Tetromino/TetrominoType.hpp"
#include <vector>

struct TetrisData {
public:
    TetrisData();
    ~TetrisData();

public:
    GameState gameState;
    int countDownTime;
    TetrominoType activeTetromino;
    std::vector<Position> activeTetrominoPositions;
    std::vector<Position> shadowTetrominoPositions;
    TetrominoType nextTetromino;
    std::vector<Position> nextTetrominoPositions;
    TetrominoType holdingTetromino;
    std::vector<Position> holdingTetrominoPositions;
    std::vector<std::vector<TetrominoType>> gameBoard;
};

#endif
