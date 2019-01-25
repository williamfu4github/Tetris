#ifndef TetrisLevel_hpp
#define TetrisLevel_hpp

class TetrisLevel {
private:
    static const int levelMax;
    static int lineValue(int numberOfLines);
    static int levelLineValueTarget(int gameLevel);

public:
    TetrisLevel();
    ~TetrisLevel();
    void addClearedLines(int numberOfLines);
    int getGameLevel() const;
    
private:
    int gameLevel;
    int lineValueToNext;
};

#endif
