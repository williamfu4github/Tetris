#ifndef GameTetris_hpp
#define GameTetris_hpp

class TetrisModel;
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
    TetrisModel* gameModel;
    TetrisUI* gameUI;
};

#endif
