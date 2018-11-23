#include "Driver/GameTetris.hpp"

#include "Engine/TetrisEngine.hpp"
#include "UI/TetrisX11UI.hpp"
#include "Utility/Timer.hpp"
#include "Data/TetrisData.hpp"
#include <thread>
namespace chrono = std::chrono;

const chrono::milliseconds GameTetris::countDownQuantum(3000);

GameTetris::GameTetris():
    gameState(GameState::WELCOME) {
    gameEngine = new TetrisEngine;
    gameUI = new TetrisX11UI;
    countDownTimer = new Timer;
}

GameTetris::~GameTetris() {
    delete gameEngine;
    delete gameUI;
    delete countDownTimer;
}

void GameTetris::playGame() {
    while (true) {
        this->performOneFrame();
        switch (gameUI->getNextEvent()) {
            case TetrisUI::ControllerEvent::NO_EVENT:
                break;
            case TetrisUI::ControllerEvent::WINDOW_CLOSE:
                return;
            case TetrisUI::ControllerEvent::KEY_Q:
                return;
            case TetrisUI::ControllerEvent::KEY_RETURN:
                switch (gameState) {
                    case GameState::WELCOME:
                        gameState = GameState::COUNT_DOWN;
                        countDownTimer->startTimer();
                        break;
                    case GameState::COUNT_DOWN:
                        gameState = GameState::PAUSED;
                        countDownTimer->resetTimer();
                        break;
                    case GameState::IN_GAME:
                        gameState = GameState::PAUSED;
                        gameEngine->pauseGame();
                        break;
                    case GameState::PAUSED:
                        gameState = GameState::COUNT_DOWN;
                        countDownTimer->startTimer();
                        break;
                    case GameState::GAME_OVER:
                        break;
                }
                break;
            case TetrisUI::ControllerEvent::KEY_LEFT:
                gameEngine->shiftActiveTetrominoLeft();
                break;
            case TetrisUI::ControllerEvent::KEY_RIGHT:
                gameEngine->shiftActiveTetrominoRight();
                break;
            case TetrisUI::ControllerEvent::KEY_DOWN:
                gameEngine->shiftActiveTetrominoDown();
                break;
            case TetrisUI::ControllerEvent::KEY_UP:
                gameEngine->rotateActiveTetrominoClockwise();
                break;
            case TetrisUI::ControllerEvent::KEY_SPACE:
                gameEngine->dropActiveTetromino();
                break;
            case TetrisUI::ControllerEvent::KEY_Z:
                gameEngine->rotateActiveTetrominoCounterClockwise();
                break;
            case TetrisUI::ControllerEvent::KEY_C:
                gameEngine->holdActiveTetromino();
                break;
        }
        gameEngine->performOneFrame();
        if (gameEngine->getGameStatus() == TetrisEngine::GameStatus::GAME_OVER) {
            gameState = GameState::GAME_OVER;
        }
        gameUI->renderView(this->collectData());
        std::this_thread::sleep_for(chrono::milliseconds(10));
    }
}

void GameTetris::performOneFrame() {
    if (gameState == GameState::COUNT_DOWN) {
        if (this->reachCountDownEvent()) {
            gameState = GameState::IN_GAME;
            countDownTimer->resetTimer();
            gameEngine->startGame();
        }
    }
}

bool GameTetris::reachCountDownEvent() const {
    return (countDownTimer->getAccumulatedTime() >= GameTetris::countDownQuantum);
}

// POST: caller must free returned pointer
TetrisData* GameTetris::collectData() const {
    TetrisData* gameData = new TetrisData;
    gameData->gameState = gameState;
    gameData->countDownTime = static_cast<int>(chrono::duration_cast<chrono::milliseconds>(GameTetris::countDownQuantum - countDownTimer->getAccumulatedTime()).count());
    gameEngine->collectData(gameData);
    return gameData;
}
