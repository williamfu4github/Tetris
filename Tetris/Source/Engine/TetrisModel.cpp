#include "Engine/TetrisModel.hpp"

#include "Engine/Tetromino/TetrominoSpawner.hpp"
#include "Engine/TetrisBoard.hpp"
#include "Engine/Tetromino/TetrominoBlock.hpp"
#include "Engine/TetrisStatistics.hpp"
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
    this->linkWithGameStatistics(nullptr);
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
    for (int attempt = 0; attempt <= 4; attempt ++) {
        TetrominoBlock* proposedBlock = activeTetromino->createClone();
        proposedBlock->rotateClockwise(attempt);
        if (this->handleActionProposal(proposedBlock) == TetrisModel::ActionResult::SUCCESS) {
            return TetrisModel::ActionResult::SUCCESS;
        }
    }
    return TetrisModel::ActionResult::FAILURE;
}

// return SUCCESS or FAILURE
TetrisModel::ActionResult TetrisModel::rotateActiveTetrominoCounterClockwise() {
    for (int attempt = 0; attempt <= 4; attempt ++) {
        TetrominoBlock* proposedBlock = activeTetromino->createClone();
        proposedBlock->rotateCounterClockwise(attempt);
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
    delete activeTetromino;
    activeTetromino = nextTetromino;
    nextTetromino = tetrominoSpawner->createOneTetromino();
    if (this->initializeActiveTetromino() == TetrisModel::ActionResult::GAME_OVER) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    return TetrisModel::ActionResult::SUCCESS;
}

bool TetrisModel::checkActiveTetrominoInAir() const {
    return (activeTetromino->getTilePositions() != shadowTetromino->getTilePositions());
}

void TetrisModel::collectData(TetrisData* gameData) const {
    gameData->activeTetromino = activeTetromino->getBlockType();
    gameData->activeTetrominoPositions = activeTetromino->getTilePositions();
    gameData->shadowTetrominoPositions = shadowTetromino->getTilePositions();
    gameData->nextTetromino = nextTetromino->getBlockType();
    gameData->nextTetrominoPositions = nextTetromino->getTileCanonicalPositions();
    if (holdingTetromino != nullptr) {
        gameData->holdingTetromino = holdingTetromino->getBlockType();
        gameData->holdingTetrominoPositions = holdingTetromino->getTileCanonicalPositions();
    }
    else {
        gameData->holdingTetromino = TetrominoType::EMPTY;
    }
    gameBoard->collectData(gameData);
}

// return SUCCESS or GAME_OVER
// NOTE: game over by block-out
TetrisModel::ActionResult TetrisModel::initializeActiveTetromino() {
    activeTetromino->setBlockPosition(TetrisModel::tetrominoInitialPosition());
    activeTetromino->setBlockPhase(TetrominoBlock::tetrominoInitialPhase);
    this->updateShadowTetromino();
    if (!gameBoard->checkTilesEmpty(activeTetromino->getTilePositions())) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    this->shiftActiveTetrominoDown();
    return TetrisModel::ActionResult::SUCCESS;
}

// return SUCCESS or GAME_OVER
// NOTE: game over by lock-out
TetrisModel::ActionResult TetrisModel::finalizeActiveTetromino() {
    if (gameBoard->checkTilesOutside(activeTetromino->getTilePositions())) {
        return TetrisModel::ActionResult::GAME_OVER;
    }
    gameBoard->setTilesState(activeTetromino->getTilePositions(), activeTetromino->getBlockType());
    gameStatistics->addClearedLines(gameBoard->countFullRows());
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

void TetrisModel::linkWithGameStatistics(TetrisStatistics* gameStatistics) {
    this->gameStatistics = gameStatistics;
}
