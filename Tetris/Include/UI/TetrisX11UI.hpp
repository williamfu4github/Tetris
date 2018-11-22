#ifndef TetrisX11UI_hpp
#define TetrisX11UI_hpp

#include "UI/TetrisUI.hpp"
#include <X11/Xlib.h>

class TetrisX11UI : public TetrisUI {
public:
    TetrisX11UI();
    ~TetrisX11UI() override;
    TetrisUI::ControllerEvent getNextEvent() override;
    void renderView(TetrisData* gameData) override;
private:
    void createGameWindow();
    void createGraphicalResource();
    
private:
    Display* deviceDisplay;
    int deviceScreen;
    Window* gameWindow;
    GC* graphicsContext;
};

#endif



//#include <string>
//#include <unordered_map>
//



//    void interpretGameData() override;
//    void renderNotStartedView();
//    void renderCountDownView();
//    void renderInGameView();
//    void renderPausedView();
//    void renderGameOverView();

//    void renderBoardGrid();
//    void renderBoard();
//    void renderShadowTetromino();
//    void renderActiveTetromino();
//    void renderNextTetromino();
//    void renderHoldingTetromino();
//    void drawString(std::string text, int fontSize, int x, int y);
//    void drawTile(int row, int column, std::string color);
//    int calculateBoardSizeX() const;
//    int calculateBoardSizeY() const;
//    int calculateWindowSizeX() const;
//    int calculateWindowSizeY() const;
//    int calculateWindowPositionX() const;
//    int calculateWindowPositionY() const;
//

//    std::unordered_map<std::string, XColor> colorMap;
//
//private:
//    static const std::string windowTitle;
//    static const int gridTileSize;
//    static const int windowMarginX;
//    static const int windowMarginY;


