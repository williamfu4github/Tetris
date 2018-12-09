#ifndef TetrisUI_hpp
#define TetrisUI_hpp

struct TetrisData;

class TetrisUI {
public:
    enum class ControllerEvent {
        NO_EVENT,
        WINDOW_CLOSE,
        KEY_Q,
        KEY_RETURN,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_DOWN,
        KEY_UP,
        KEY_SPACE,
        KEY_Z,
        KEY_C
    };
protected:
    static const int boardSizeColumn;
    static const int boardBoundaryRow;

public:
    virtual ~TetrisUI() = 0;
    virtual TetrisUI::ControllerEvent getNextEvent() = 0;
    virtual void renderView(TetrisData* gameData) = 0;
protected:
    TetrisUI();
};

#endif
