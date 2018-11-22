#ifndef TetrisBoard_hpp
#define TetrisBoard_hpp

#include "Utility/Position.hpp"
#include "Engine/Tetromino/TetrominoType.hpp"
#include <vector>
struct TetrisData;

class TetrisBoard {
public:
    TetrisBoard();
    ~TetrisBoard();
    bool checkTilesEmpty(std::vector<Position> tilePositions) const;
    bool checkTilesOutside(std::vector<Position> tilePositions) const;
    void setTilesState(std::vector<Position> tilePositions, TetrominoType newState);
    int countFullRows() const;    // not used
    void clearFullRows();
    void collectData(TetrisData* gameData) const;
private:
    bool checkOneTileEmpty(Position tilePosition) const;
    
private:
    std::vector<std::vector<TetrominoType>> gameBoard;
    std::vector<int> rowOccupancies;
    
public:
    static const int boardSizeColumn;
    static const int boardBoundaryRow;
private:
    static const int boardSizeRow;
};

#endif
