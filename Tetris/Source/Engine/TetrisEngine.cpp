#include "Engine/TetrisEngine.hpp"

#include "Utility/Timer.hpp"
#include "Engine/TetrisModel.hpp"
#include "Engine/TetrisStatistics.hpp"
namespace chrono = std::chrono;

const chrono::milliseconds TetrisEngine::lockDelayQuantum(500);

chrono::milliseconds TetrisEngine::gravitationQuantum(int gameLevel) {
    switch (gameLevel) {
        case 1:
            return chrono::milliseconds(1000);
        case 2:
            return chrono::milliseconds(793);
        case 3:
            return chrono::milliseconds(618);
        case 4:
            return chrono::milliseconds(473);
        case 5:
            return chrono::milliseconds(355);
        case 6:
            return chrono::milliseconds(262);
        case 7:
            return chrono::milliseconds(190);
        case 8:
            return chrono::milliseconds(135);
        case 9:
            return chrono::milliseconds(94);
        case 10:
            return chrono::milliseconds(64);
        case 11:
            return chrono::milliseconds(43);
        case 12:
            return chrono::milliseconds(28);
        case 13:
            return chrono::milliseconds(18);
        default:
            return chrono::milliseconds(10);
    }
}

TetrisEngine::TetrisEngine():
    gameStatus(TetrisEngine::GameStatus::NOT_STARTED),
    temporalTask(TetrisEngine::TemporalTask::GRAVITATION),
    allowHoldAction(true) {
    gameTimeTimer = new Timer;
    temporalTaskTimer = new Timer;
    gameModel = new TetrisModel;
    gameStatistics = new TetrisStatistics;
    gameModel->linkWithGameStatistics(gameStatistics);
}

TetrisEngine::~TetrisEngine() {
    delete gameTimeTimer;
    delete temporalTaskTimer;
    delete gameModel;
    delete gameStatistics;
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

// NOTE: lock delay mechanism with Infinity
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
            return (temporalTaskTimer->getAccumulatedTime() >= TetrisEngine::gravitationQuantum(gameStatistics->getGameLevel()));
        case TetrisEngine::TemporalTask::LOCK_DELAY:
            return (temporalTaskTimer->getAccumulatedTime() >= TetrisEngine::lockDelayQuantum);
    }
}
