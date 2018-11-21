#ifndef TetrominoSpawner_hpp
#define TetrominoSpawner_hpp

#include <random>
#include <deque>
class TetrominoBlock;

class TetrominoSpawner {
public:
    TetrominoSpawner();
    ~TetrominoSpawner();
    TetrominoBlock* createOneTetromino();
private:
    void emptyRandomBag();
    void fillRandomBag();
    
private:
    std::minstd_rand* randomGenerator;
    std::deque<TetrominoBlock*> randomBag;
};

#endif
