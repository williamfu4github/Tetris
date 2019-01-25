#ifndef TetrisStatistics_hpp
#define TetrisStatistics_hpp

class TetrisLevel;

class TetrisStatistics {
public:
    TetrisStatistics();
    ~TetrisStatistics();
    void addClearedLines(int numberOfLines);
    int getGameLevel() const;
    
private:
    TetrisLevel* gameLevel;
    int totalLineCleared;
};

#endif
