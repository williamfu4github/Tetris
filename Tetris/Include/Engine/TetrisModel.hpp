#ifndef TetrisModel_hpp
#define TetrisModel_hpp

#include "Utility/Position.hpp"
class TetrominoSpawner;
class TetrisBoard;
class TetrominoBlock;
class TetrisStatistics;
struct TetrisData;

class TetrisModel {
public:
    enum class ActionResult {
        SUCCESS,
        FAILURE,
        GAME_OVER
    };
private:
    static Position tetrominoInitialPosition();

public:
    TetrisModel();
    ~TetrisModel();
    TetrisModel::ActionResult shiftActiveTetrominoDown();
    TetrisModel::ActionResult shiftActiveTetrominoLeft();
    TetrisModel::ActionResult shiftActiveTetrominoRight();
    TetrisModel::ActionResult rotateActiveTetrominoClockwise();
    TetrisModel::ActionResult rotateActiveTetrominoCounterClockwise();
    TetrisModel::ActionResult holdActiveTetromino();
    TetrisModel::ActionResult dropActiveTetromino();
    bool checkActiveTetrominoInAir() const;
    void collectData(TetrisData* gameData) const;
private:
    TetrisModel::ActionResult initializeActiveTetromino();
    TetrisModel::ActionResult finalizeActiveTetromino();
    TetrisModel::ActionResult handleActionProposal(TetrominoBlock* proposedBlock);
    void updateShadowTetromino();
    
private:
    TetrominoSpawner* tetrominoSpawner;
    TetrisBoard* gameBoard;
    TetrominoBlock* activeTetromino;
    TetrominoBlock* shadowTetromino;
    TetrominoBlock* nextTetromino;
    TetrominoBlock* holdingTetromino;

private:
    TetrisStatistics* gameStatistics;
public:
    void linkWithGameStatistics(TetrisStatistics* gameStatistics);
};

#endif
