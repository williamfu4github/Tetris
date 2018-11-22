#ifndef GameTetris_hpp
#define GameTetris_hpp

#include "Driver/GameState.hpp"
#include <chrono>
class TetrisEngine;
class TetrisUI;
class Timer;
struct TetrisData;

class GameTetris {
public:
    GameTetris();
    ~GameTetris();
    void playGame();
private:
    void performOneFrame();
    bool reachCountDownEvent() const;
    TetrisData* collectData() const;
    
private:
    GameState gameState;
    TetrisEngine* gameEngine;
    TetrisUI* gameUI;
    Timer* countDownTimer;
    
private:
    static const std::chrono::milliseconds countDownQuantum;
};

#endif
