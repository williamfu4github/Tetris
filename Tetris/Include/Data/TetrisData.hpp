#ifndef TetrisData_hpp
#define TetrisData_hpp

#include "Driver/GameState.hpp"

struct TetrisData {
public:
    TetrisData();
    ~TetrisData();

public:
    GameState gameState;
};

#endif
