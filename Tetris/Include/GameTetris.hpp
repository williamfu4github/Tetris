#ifndef GameTetris_hpp
#define GameTetris_hpp

class TetrisEngine;
class TetrisUI;

class GameTetris {
private:
    enum class GameStatus {
        NOT_STARTED,
        COUNT_DOWN,
        IN_GAME,
        PAUSED,
        GAME_OVER
    };
    
public:
    GameTetris();
    ~GameTetris();
    void playGame();
    
private:
    GameTetris::GameStatus gameStatus;
    TetrisEngine* gameModel;
    TetrisUI* gameUI;
};

#endif
