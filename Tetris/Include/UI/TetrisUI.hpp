#ifndef TetrisUI_hpp
#define TetrisUI_hpp

class TetrisUI {
public:
    enum class ControllerEvent {
        NO_EVENT,
        WINDOW_CLOSE,
        KEY_ENTER,
        KEY_LEFT,
        KEY_RIGHT,
        KEY_DOWN,
        KEY_UP,
        KEY_SPACE,
        KEY_Z,
        KEY_C
    };
    
public:
    ~TetrisUI();
    TetrisUI::ControllerEvent getNextEvent();
public:
    TetrisUI();
};

#endif
