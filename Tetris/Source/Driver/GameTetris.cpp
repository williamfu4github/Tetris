#include "Driver/GameTetris.hpp"

#include "Engine/TetrisEngine.hpp"
#include "UI/TetrisUI.hpp"

GameTetris::GameTetris():
    gameStatus(GameTetris::GameStatus::NOT_STARTED) {
    gameModel = new TetrisEngine;
    gameUI = new TetrisUI;
}

GameTetris::~GameTetris() {
    delete gameModel;
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
    }
}
