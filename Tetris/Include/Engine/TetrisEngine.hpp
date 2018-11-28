#ifndef TetrisEngine_hpp
#define TetrisEngine_hpp

#include <chrono>
class TetrisModel;
class Timer;
struct TetrisData;

class TetrisEngine {
public:
    enum class GameStatus {
        NOT_STARTED,
        IN_GAME,
        PAUSED,
        GAME_OVER
    };
private:
    enum class TemporalTask {
        GRAVITATION,
        LOCK_DELAY
    };
    enum class HoldStatus {
        AVAILABLE,
        COOL_DOWN
    };
    
public:
    TetrisEngine();
    ~TetrisEngine();
    void startGame();
    void pauseGame();
    void performOneFrame();
    void shiftActiveTetrominoDown();
    void shiftActiveTetrominoLeft();
    void shiftActiveTetrominoRight();
    void rotateActiveTetrominoClockwise();
    void rotateActiveTetrominoCounterClockwise();
    void holdActiveTetromino();
    void dropActiveTetromino();
    TetrisEngine::GameStatus getGameStatus() const;
    void collectData(TetrisData* gameData) const;
private:
    void startNewTemporalTask(TetrisEngine::TemporalTask newTask);
    bool reachTemporalTaskEvent() const;
    
private:
    TetrisEngine::GameStatus gameStatus;
    TetrisEngine::TemporalTask temporalTask;
    TetrisEngine::HoldStatus holdStatus;
    Timer* gameTimeTimer;
    Timer* temporalTaskTimer;
    TetrisModel* gameModel;
    
private:
    static const std::chrono::milliseconds gravitationQuantum;
    static const std::chrono::milliseconds lockDelayQuantum;
};

#endif
