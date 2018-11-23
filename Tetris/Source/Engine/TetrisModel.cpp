#include "Engine/TetrisModel.hpp"

#include "Engine/Tetromino/TetrominoSpawner.hpp"
#include "Engine/TetrisBoard.hpp"
#include "Engine/Tetromino/TetrominoBlock.hpp"
#include "Data/TetrisData.hpp"

Position TetrisModel::tetrominoInitialPosition() {
    return Position(TetrisBoard::boardBoundaryRow, (TetrisBoard::boardSizeColumn - 4) / 2);
}

TetrisModel::TetrisModel():
    shadowTetromino(nullptr),
    holdingTetromino(nullptr) {
    tetrominoSpawner = new TetrominoSpawner;
    gameBoard = new TetrisBoard;
    activeTetromino = tetrominoSpawner->createOneTetromino();
    nextTetromino = tetrominoSpawner->createOneTetromino();
    this->initializeActiveTetromino();
}

TetrisModel::~TetrisModel() {
    delete tetrominoSpawner;
    delete gameBoard;
    delete activeTetromino;
    delete shadowTetromino;
    delete nextTetromino;
    delete holdingTetromino;
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::shiftActiveTetrominoDown() {
    TetrominoBlock* proposedBlock = activeTetromino->createClone();
    proposedBlock->shiftDown();
    return this->handleActionProposal(proposedBlock);
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::shiftActiveTetrominoLeft() {
    TetrominoBlock* proposedBlock = activeTetromino->createClone();
    proposedBlock->shiftLeft();
    return this->handleActionProposal(proposedBlock);
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::shiftActiveTetrominoRight() {
    TetrominoBlock* proposedBlock = activeTetromino->createClone();
    proposedBlock->shiftRight();
    return this->handleActionProposal(proposedBlock);
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::rotateActiveTetrominoClockwise() {
    for (int attemptNumber = 0; attemptNumber <= 4; attemptNumber ++) {
        TetrominoBlock* proposedBlock = activeTetromino->createClone();
        proposedBlock->rotateClockwise(attemptNumber);
        if (this->handleActionProposal(proposedBlock) == TetrisModel::ActionResult::SUCCESS) {
            return TetrisModel::ActionResult::SUCCESS;
        }
    }
    return TetrisModel::ActionResult::FAILURE;
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::rotateActiveTetrominoCounterClockwise() {
    for (int attemptNumber = 0; attemptNumber <= 4; attemptNumber ++) {
        TetrominoBlock* proposedBlock = activeTetromino->createClone();
        proposedBlock->rotateCounterClockwise(attemptNumber);
        if (this->handleActionProposal(proposedBlock) == TetrisModel::ActionResult::SUCCESS) {
            return TetrisModel::ActionResult::SUCCESS;
        }
    }
    return TetrisModel::ActionResult::FAILURE;
}

// return SUCCESS or GAME_OVER
TetrisModel::ActionResult TetrisModel::holdActiveTetromino() {
    std::swap(holdingTetromino, activeTetromino);
    if (activeTetromino == nullptr) {
        activeTetromino = nextTetromino;
        nextTetromino = tetrominoSpawner->createOneTetromino();
    }
    return this->initializeActiveTetromino();
}

// return SUCCESS or GAME_OVER
TetrisModel::ActionResult TetrisModel::dropActiveTetromino() {
    delete activeTetromino;
    activeTetromino = shadowTetromino->createClone();
    if (this->finalizeActiveTetromino() == TetrisModel::ActionResult::GAME_OVER) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    activeTetromino = nextTetromino;
    nextTetromino = tetrominoSpawner->createOneTetromino();
    if (this->initializeActiveTetromino() == TetrisModel::ActionResult::GAME_OVER) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    return TetrisModel::ActionResult::SUCCESS;
}

void TetrisModel::collectData(TetrisData* gameData) const {
    gameData->activeTetromino = activeTetromino->getBlockType();
    gameData->activeTetrominoPositions = activeTetromino->getTilePositions();
    gameData->shadowTetrominoPositions = shadowTetromino->getTilePositions();
    gameData->nextTetromino = nextTetromino->getBlockType();
    gameData->nextTetrominoPositions = nextTetromino->getTileRelativePositions();
    if (holdingTetromino != nullptr) {
        gameData->holdingTetromino = holdingTetromino->getBlockType();
        gameData->holdingTetrominoPositions = holdingTetromino->getTileRelativePositions();
    }
    else {
        gameData->holdingTetromino = TetrominoType::EMPTY;
    }
    gameBoard->collectData(gameData);
}

// return SUCCESS or GAME_OVER
TetrisModel::ActionResult TetrisModel::initializeActiveTetromino() {
    activeTetromino->setBlockPosition(TetrisModel::tetrominoInitialPosition());
    this->updateShadowTetromino();
    if (!gameBoard->checkTilesEmpty(activeTetromino->getTilePositions())) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    this->shiftActiveTetrominoDown();
    return TetrisModel::ActionResult::SUCCESS;
}

// return SUCCESS or GAME_OVER
TetrisModel::ActionResult TetrisModel::finalizeActiveTetromino() {
    if (gameBoard->checkTilesOutside(activeTetromino->getTilePositions())) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    gameBoard->setTilesState(activeTetromino->getTilePositions(), activeTetromino->getBlockType());
    delete activeTetromino;
    // TODO update score/stat
    gameBoard->clearFullRows();
    return TetrisModel::ActionResult::SUCCESS;
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::handleActionProposal(TetrominoBlock* proposedBlock) {
    if (gameBoard->checkTilesEmpty(proposedBlock->getTilePositions())) {
        delete activeTetromino;
        activeTetromino = proposedBlock;
        this->updateShadowTetromino();
        return TetrisModel::ActionResult::SUCCESS;
    }
    else {
        delete proposedBlock;
        return TetrisModel::ActionResult::FAILURE;
    }
}

// NOTE: shadowTetromino tiles will be occupied in gameBoard if activeTetromino tiles is occupied
void TetrisModel::updateShadowTetromino() {
    delete shadowTetromino;
    shadowTetromino = activeTetromino->createClone();
    do {
        shadowTetromino->shiftDown();
    }
    while (gameBoard->checkTilesEmpty(shadowTetromino->getTilePositions()));
    shadowTetromino->shiftUp();
}
