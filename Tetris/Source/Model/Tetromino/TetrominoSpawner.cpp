#include "Model/Tetromino/TetrominoSpawner.hpp"

#include "Model/Tetromino/IBlock.hpp"
#include "Model/Tetromino/OBlock.hpp"
#include "Model/Tetromino/TBlock.hpp"
#include "Model/Tetromino/SBlock.hpp"
#include "Model/Tetromino/ZBlock.hpp"
#include "Model/Tetromino/JBlock.hpp"
#include "Model/Tetromino/LBlock.hpp"
#include <chrono>
namespace chrono = std::chrono;

TetrominoSpawner::TetrominoSpawner() {
    randomGenerator = new std::minstd_rand;
    randomGenerator->seed(static_cast<unsigned int>(chrono::system_clock::now().time_since_epoch().count()));
}

TetrominoSpawner::~TetrominoSpawner() {
    delete randomGenerator;
    this->emptyRandomBag();
}

// POST: caller must free returned pointer
TetrominoBlock* TetrominoSpawner::createOneTetromino() {
    if (randomBag.empty()) {
        this->fillRandomBag();
    }
    TetrominoBlock* newBlock = randomBag.front();
    randomBag.pop_front();
    return newBlock;
}

void TetrominoSpawner::emptyRandomBag() {
    while (!randomBag.empty()) {
        delete randomBag.front();
        randomBag.pop_front();
    }
}

// PRE: randomBag must be empty
// NOTE: 7-bag random of blocks
void TetrominoSpawner::fillRandomBag() {
    randomBag.push_back(new IBlock);
    randomBag.push_back(new OBlock);
    randomBag.push_back(new TBlock);
    randomBag.push_back(new SBlock);
    randomBag.push_back(new ZBlock);
    randomBag.push_back(new JBlock);
    randomBag.push_back(new LBlock);
    std::shuffle(randomBag.begin(), randomBag.end(), *randomGenerator);
}
