#ifndef GameTetris_hpp
#define GameTetris_hpp

#include "Driver/GameState.hpp"
class TetrisEngine;
class TetrisUI;
class TetrisData;

class GameTetris {
public:
    GameTetris();
    ~GameTetris();
    void playGame();
private:
    TetrisData* collectData() const;
    
private:
    GameState gameState;
    TetrisEngine* gameEngine;
    TetrisUI* gameUI;
};

#endif
