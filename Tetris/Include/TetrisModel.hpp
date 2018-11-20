#ifndef TetrisModel_hpp
#define TetrisModel_hpp

class TetrisModel {
private:
    enum class ModelStatus {
        NOT_STARTED,
        IN_GAME,
        GAME_OVER
    };
    
public:
    TetrisModel();
    ~TetrisModel();
};

#endif
