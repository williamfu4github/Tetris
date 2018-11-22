#include "Engine/TetrisBoard.hpp"

#include "Data/TetrisData.hpp"
using std::vector;

const int TetrisBoard::boardSizeColumn = 10;
const int TetrisBoard::boardBoundaryRow = 20;
const int TetrisBoard::boardSizeRow = 25;

TetrisBoard::TetrisBoard() {
    for (int row = 0; row < TetrisBoard::boardSizeRow; row ++) {
        gameBoard.push_back(vector<TetrominoType>{});
        gameBoard.back().resize(TetrisBoard::boardSizeColumn, TetrominoType::EMPTY);
        rowOccupancies.push_back(0);
    }
}

TetrisBoard::~TetrisBoard() {
}

// NOTE: position may be off board
bool TetrisBoard::checkTilesEmpty(vector<Position> tilePositions) const {
    for (Position position : tilePositions) {
        if (!this->checkOneTileEmpty(position)) {
            return false;
        }
    }
    return true;
}

// PRE: position must be on board
bool TetrisBoard::checkTilesOutside(vector<Position> tilePositions) const {
    for (Position position : tilePositions) {
        if (position.row < TetrisBoard::boardBoundaryRow) {
            return false;
        }
    }
    return true;
}

// PRE: position must be on board
// PRE: no duplicate positions
void TetrisBoard::setTilesState(vector<Position> tilePositions, TetrominoType newState) {
    for (Position position : tilePositions) {
        TetrominoType oldState = gameBoard[position.row][position.column];
        if ((oldState == TetrominoType::EMPTY) && (newState != TetrominoType::EMPTY)) {
            rowOccupancies[position.row] ++;
        }
        else if ((oldState != TetrominoType::EMPTY) && (newState == TetrominoType::EMPTY)) {
            rowOccupancies[position.row] --;
        }
        gameBoard[position.row][position.column] = newState;
    }
}

int TetrisBoard::countFullRows() const {
    int count = 0;
    for (int row = 0; row < TetrisBoard::boardSizeRow; row ++) {
        if (rowOccupancies[row] == TetrisBoard::boardSizeColumn) {
            count ++;
        }
    }
    return count;
}

void TetrisBoard::clearFullRows() {
    for (int row = TetrisBoard::boardSizeRow - 1; row >= 0; row --) {
        if (rowOccupancies[row] == TetrisBoard::boardSizeColumn) {
            for (int index = row + 1; index < TetrisBoard::boardSizeRow; index ++) {
                // use swap to improve time efficiency to O(1)
                std::swap(gameBoard[index - 1], gameBoard[index]);
                rowOccupancies[index - 1] = rowOccupancies[index];
            }
            gameBoard.back().clear();
            gameBoard.back().resize(TetrisBoard::boardSizeColumn, TetrominoType::EMPTY);
            rowOccupancies.back() = 0;
        }
    }
}

void TetrisBoard::collectData(TetrisData* gameData) const {
    gameData->gameBoard = gameBoard;
    gameData->gameBoard.resize(TetrisBoard::boardBoundaryRow);
}

// NOTE: position may be off board
bool TetrisBoard::checkOneTileEmpty(Position tilePosition) const {
    if ((tilePosition.row < 0) || (tilePosition.row >= TetrisBoard::boardSizeRow)) {
        return false;
    }
    if ((tilePosition.column < 0) || (tilePosition.column >= TetrisBoard::boardSizeColumn)) {
        return false;
    }
    return (gameBoard[tilePosition.row][tilePosition.column] == TetrominoType::EMPTY);
}
