#include "GameTetris.hpp"

#include "TetrisModel.hpp"
#include "TetrisUI.hpp"

GameTetris::GameTetris():
    gameStatus(GameTetris::GameStatus::NOT_STARTED) {
    gameModel = new TetrisModel;
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
