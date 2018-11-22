#include "Driver/GameTetris.hpp"

#include "Engine/TetrisEngine.hpp"
#include "UI/TetrisX11UI.hpp"
#include "Data/TetrisData.hpp"

GameTetris::GameTetris():
    gameState(GameState::WELCOME) {
    gameEngine = new TetrisEngine;
    gameUI = new TetrisX11UI;
}

GameTetris::~GameTetris() {
    delete gameEngine;
    delete gameUI;
}

void GameTetris::playGame() {
    while (true) {
//        switch (gameUI->getNextEvent()) {
//            case TetrisUI::ControllerEvent::NO_EVENT:
//                break;
//            case TetrisUI::ControllerEvent::WINDOW_CLOSE:
//                return;
//        }
        gameEngine->performOneFrame();
        gameUI->renderView(this->collectData());
    }
}

// POST: caller must free returned pointer
TetrisData* GameTetris::collectData() const {
    TetrisData* gameData = new TetrisData;
    gameData->gameState = gameState;
    return gameData;
}
