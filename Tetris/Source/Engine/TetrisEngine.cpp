#include "Engine/TetrisEngine.hpp"

#include "Utility/Timer.hpp"
#include "Engine/TetrisModel.hpp"
namespace chrono = std::chrono;

const chrono::milliseconds TetrisEngine::gravitationQuantum(1000);
const chrono::milliseconds TetrisEngine::lockDelayQuantum(500);

TetrisEngine::TetrisEngine():
    gameStatus(TetrisEngine::GameStatus::NOT_STARTED),
    temporalTask(TetrisEngine::TemporalTask::GRAVITATION),
    allowHoldAction(true) {
    gameTimeTimer = new Timer;
    temporalTaskTimer = new Timer;
    gameModel = new TetrisModel;
}

TetrisEngine::~TetrisEngine() {
    delete gameTimeTimer;
    delete temporalTaskTimer;
    delete gameModel;
}

void TetrisEngine::startGame() {
    if ((gameStatus == TetrisEngine::GameStatus::NOT_STARTED) || (gameStatus == TetrisEngine::GameStatus::PAUSED)) {
        gameStatus = TetrisEngine::GameStatus::IN_GAME;
        gameTimeTimer->startTimer();
        temporalTaskTimer->startTimer();
    }
}

void TetrisEngine::pauseGame() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        gameStatus = TetrisEngine::GameStatus::PAUSED;
        gameTimeTimer->pauseTimer();
        temporalTaskTimer->pauseTimer();
    }
}

void TetrisEngine::performOneFrame() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (this->reachTemporalTaskEvent()) {
            switch (temporalTask) {
                case TetrisEngine::TemporalTask::GRAVITATION:
                    this->shiftActiveTetrominoDown();
                    break;
                case TetrisEngine::TemporalTask::LOCK_DELAY:
                    this->dropActiveTetromino();
                    break;
            }
        }
    }
}

void TetrisEngine::shiftActiveTetrominoDown() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (gameModel->shiftActiveTetrominoDown() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(false);
        }
    }
}

void TetrisEngine::shiftActiveTetrominoLeft() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (gameModel->shiftActiveTetrominoLeft() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(true);
        }
    }
}

void TetrisEngine::shiftActiveTetrominoRight() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (gameModel->shiftActiveTetrominoRight() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(true);
        }
    }
}

void TetrisEngine::rotateActiveTetrominoClockwise() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (gameModel->rotateActiveTetrominoClockwise() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(true);
        }
    }
}

void TetrisEngine::rotateActiveTetrominoCounterClockwise() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        if (gameModel->rotateActiveTetrominoCounterClockwise() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(true);
        }
    }
}

void TetrisEngine::holdActiveTetromino() {
    if ((gameStatus == TetrisEngine::GameStatus::IN_GAME) && allowHoldAction) {
        allowHoldAction = false;
        if (gameModel->holdActiveTetromino() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(false);
        }
        else {
            gameStatus = TetrisEngine::GameStatus::GAME_OVER;
            gameTimeTimer->pauseTimer();
            temporalTaskTimer->resetTimer();
        }
    }
}

void TetrisEngine::dropActiveTetromino() {
    if (gameStatus == TetrisEngine::GameStatus::IN_GAME) {
        allowHoldAction = true;
        if (gameModel->dropActiveTetromino() == TetrisModel::ActionResult::SUCCESS) {
            this->updateTemporalTask(false);
        }
        else {
            gameStatus = TetrisEngine::GameStatus::GAME_OVER;
            gameTimeTimer->pauseTimer();
            temporalTaskTimer->resetTimer();
        }
    }
}

TetrisEngine::GameStatus TetrisEngine::getGameStatus() const {
    return gameStatus;
}

void TetrisEngine::collectData(TetrisData* gameData) const {
    gameModel->collectData(gameData);
}

void TetrisEngine::updateTemporalTask(bool carryGravity) {
    if (gameModel->checkActiveTetrominoInAir()) {
        if (!carryGravity || (temporalTask == TetrisEngine::TemporalTask::LOCK_DELAY)) {
            temporalTaskTimer->resetTimer();
            temporalTask = TetrisEngine::TemporalTask::GRAVITATION;
            temporalTaskTimer->startTimer();
        }
    }
    else {
        temporalTaskTimer->resetTimer();
        temporalTask = TetrisEngine::TemporalTask::LOCK_DELAY;
        temporalTaskTimer->startTimer();
    }
}

bool TetrisEngine::reachTemporalTaskEvent() const {
    switch (temporalTask) {
        case TetrisEngine::TemporalTask::GRAVITATION:
            return (temporalTaskTimer->getAccumulatedTime() >= TetrisEngine::gravitationQuantum);
        case TetrisEngine::TemporalTask::LOCK_DELAY:
            return (temporalTaskTimer->getAccumulatedTime() >= TetrisEngine::lockDelayQuantum);
    }
}
