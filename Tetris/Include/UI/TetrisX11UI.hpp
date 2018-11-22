#ifndef TetrisX11UI_hpp
#define TetrisX11UI_hpp

#include "UI/TetrisUI.hpp"
#include <X11/Xlib.h>
#include <string>
#include <unordered_map>

class TetrisX11UI : public TetrisUI {
public:
    TetrisX11UI();
    ~TetrisX11UI() override;
    TetrisUI::ControllerEvent getNextEvent() override;
    void renderView(TetrisData* gameData) override;
private:
    void createGameWindow();
    void createGraphicalResource();
    int calculateBoardSizeX() const;
    int calculateBoardSizeY() const;
    int calculateWindowSizeX() const;
    int calculateWindowSizeY() const;
    int calculateWindowPositionX() const;
    int calculateWindowPositionY() const;
    void drawLine(std::string color, int startX, int startY, int endX, int endY);
    void drawString(std::string text, std::string color, int fontSize, std::string font, int x, int y);
    void renderBoardGrid();
    void renderWelcomeView();
    
private:
    Display* deviceDisplay;
    int deviceScreen;
    Window* gameWindow;
    GC* graphicsContext;
    std::unordered_map<std::string, XColor> colorMap;
    
private:
    static const std::string windowTitle;
    static const int gridTileSize;
    static const std::string gridLineColor;
    static const int windowMarginX;
    static const int windowMarginY;
};

#endif






//    void interpretGameData() override;
//    void renderNotStartedView();
//    void renderCountDownView();
//    void renderInGameView();
//    void renderPausedView();
//    void renderGameOverView();


//    void renderBoard();
//    void renderShadowTetromino();
//    void renderActiveTetromino();
//    void renderNextTetromino();
//    void renderHoldingTetromino();
//    void drawTile(int row, int column, std::string color);




