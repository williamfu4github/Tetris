#ifndef TetrisStatistics_hpp
#define TetrisStatistics_hpp

class TetrisStatistics {
public:
    TetrisStatistics();
    ~TetrisStatistics();
    int getGameLevel() const;
    
private:
    int lineCleared;
};

#endif
