#include "UI/TetrisX11UI.hpp"

#include "Data/TetrisData.hpp"
#include <X11/Xutil.h>
#include <iostream>
#include <vector>
using std::cerr;
using std::endl;
using std::string;
using std::vector;

const string TetrisX11UI::windowTitle = "Tetris";
const int TetrisX11UI::gridTileSize = 30;
const string TetrisX11UI::gridLineColor = "brown";
const int TetrisX11UI::windowMarginX = 60;
const int TetrisX11UI::windowMarginY = 80;

TetrisX11UI::TetrisX11UI():
    TetrisUI() {
    deviceDisplay = ::XOpenDisplay(nullptr);
    if (deviceDisplay == nullptr) {
        cerr << "ERROR: X11 cannot open device display" << endl;
        throw 0;
    }
    deviceScreen = ::XDefaultScreen(deviceDisplay);
    this->createGameWindow();
    this->createGraphicalResource();
}

TetrisX11UI::~TetrisX11UI() {
    ::XDestroyWindow(deviceDisplay, *gameWindow);
    delete gameWindow;
    ::XFreeGC(deviceDisplay, *graphicsContext);
    delete graphicsContext;
    ::XCloseDisplay(deviceDisplay);
}

TetrisUI::ControllerEvent TetrisX11UI::getNextEvent() {
    if (::XPending(deviceDisplay) == 0) {
        return TetrisUI::ControllerEvent::NO_EVENT;
    }
    XEvent event;
    ::XNextEvent(deviceDisplay, &event);
    switch (event.type) {
        // TODO remove expose event
        case Expose:
            return TetrisUI::ControllerEvent::NO_EVENT;
        case ClientMessage:
            if (event.xclient.data.l[0] == ::XInternAtom(deviceDisplay, "WM_DELETE_WINDOW", false)) {
                return TetrisUI::ControllerEvent::WINDOW_CLOSE;
            }
            break;
        case KeyPress: {
            KeySym key = ::XLookupKeysym(&event.xkey, 0);
            if (key == XK_Return) {
                return TetrisUI::ControllerEvent::KEY_ENTER;
            }
            else if (key == XK_Left) {
                return TetrisUI::ControllerEvent::KEY_LEFT;
            }
            else if (key == XK_Right) {
                return TetrisUI::ControllerEvent::KEY_RIGHT;
            }
            else if (key == XK_Down) {
                return TetrisUI::ControllerEvent::KEY_DOWN;
            }
            else if (key == XK_Up) {
                return TetrisUI::ControllerEvent::KEY_UP;
            }
            else if (key == XK_space) {
                return TetrisUI::ControllerEvent::KEY_SPACE;
            }
            else if (key == XK_z) {
                return TetrisUI::ControllerEvent::KEY_Z;
            }
            else if (key == XK_c) {
                return TetrisUI::ControllerEvent::KEY_C;
            }
            break;
        }
    }
    return TetrisUI::ControllerEvent::NO_EVENT;
}

void TetrisX11UI::renderView(TetrisData* gameData) {
    ::XClearWindow(deviceDisplay, *gameWindow);
//    this->renderBoardGrid();
    switch (gameData->gameState) {
        case GameState::WELCOME:
            this->renderWelcomeView();
            break;
    }
    delete gameData;
}

void TetrisX11UI::createGameWindow() {
    gameWindow = new Window;
    *gameWindow = ::XCreateSimpleWindow(deviceDisplay, ::XRootWindow(deviceDisplay, deviceScreen), this->calculateWindowPositionX(), this->calculateWindowPositionY(), this->calculateWindowSizeX(), this->calculateWindowSizeY(), 1, ::XBlackPixel(deviceDisplay, deviceScreen), ::XBlackPixel(deviceDisplay, deviceScreen));
    XSizeHints* wmSizeHint = ::XAllocSizeHints();
    wmSizeHint->min_width = this->calculateWindowSizeX();
    wmSizeHint->min_height = this->calculateWindowSizeY();
    wmSizeHint->max_width = this->calculateWindowSizeX();
    wmSizeHint->max_height = this->calculateWindowSizeY();
    wmSizeHint->flags = PPosition | PSize | PMinSize | PMaxSize;
    ::XSetStandardProperties(deviceDisplay, *gameWindow, TetrisX11UI::windowTitle.c_str(), nullptr, None, nullptr, 0, wmSizeHint);
    ::XFree(wmSizeHint);
    Atom wmCloseWindow = ::XInternAtom(deviceDisplay, "WM_DELETE_WINDOW", false);
    ::XSetWMProtocols(deviceDisplay, *gameWindow, &wmCloseWindow, 1);
    ::XSelectInput(deviceDisplay, *gameWindow, ExposureMask | KeyPressMask);
    ::XMapRaised(deviceDisplay, *gameWindow);
}

void TetrisX11UI::createGraphicalResource() {
    graphicsContext = new GC;
    *graphicsContext = ::XCreateGC(deviceDisplay, *gameWindow, 0, nullptr);
    Colormap palette = ::XDefaultColormap(deviceDisplay, deviceScreen);
    vector<string> colorList{"black", "white", "grey", "brown", "cyan", "yellow", "purple", "green", "red", "blue", "orange"};
    for (string colorString : colorList) {
        XColor color;
        if (::XAllocNamedColor(deviceDisplay, palette, colorString.c_str(), &color, &color) == 0) {
            cerr << "ERROR: X11 cannot find color " << colorString << " for the device display" << endl;
            throw 0;
        }
        colorMap[colorString] = color;
    }
}

int TetrisX11UI::calculateBoardSizeX() const {
    return (TetrisX11UI::gridTileSize + 1) * TetrisUI::boardSizeColumn + 1;
}

int TetrisX11UI::calculateBoardSizeY() const {
    return (TetrisX11UI::gridTileSize + 1) * TetrisUI::boardBoundaryRow + 1;
}

int TetrisX11UI::calculateWindowSizeX() const {
    return (this->calculateBoardSizeX() + TetrisX11UI::windowMarginX);
}

int TetrisX11UI::calculateWindowSizeY() const {
    return (this->calculateBoardSizeY() + TetrisX11UI::windowMarginY);
}

int TetrisX11UI::calculateWindowPositionX() const {
    return (::XDisplayWidth(deviceDisplay, deviceScreen) - this->calculateWindowSizeX()) / 2;
}

int TetrisX11UI::calculateWindowPositionY() const {
    return (::XDisplayHeight(deviceDisplay, deviceScreen) - this->calculateWindowSizeY()) / 2;
}

void TetrisX11UI::drawLine(string color, int startX, int startY, int endX, int endY) {
    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap[color].pixel);
    ::XDrawLine(deviceDisplay, *gameWindow, *graphicsContext, startX, startY, endX, endY);
}

void TetrisX11UI::drawString(string text, string color, int fontSize, string font, int x, int y) {
    string fontString = "-*-" + font + "-*-r-*-*-" + std::to_string(fontSize) + "-*-*-*-*-*-*-*";
    ::XSetFont(deviceDisplay, *graphicsContext, ::XLoadFont(deviceDisplay, fontString.c_str()));
    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap[color].pixel);
    ::XDrawString(deviceDisplay, *gameWindow, *graphicsContext, x, y, text.c_str(), static_cast<int>(text.size()));
}

void TetrisX11UI::renderBoardGrid() {
    int leftX = TetrisX11UI::windowMarginX / 2;
    int rightX = leftX + this->calculateBoardSizeX() - 1;
    int leftY = TetrisX11UI::windowMarginY / 2;
    int rightY = leftY + this->calculateBoardSizeY() - 1;
    for (int i = 0; i < TetrisUI::boardSizeColumn + 1; i ++) {
        this->drawLine(TetrisX11UI::gridLineColor, leftX + i * (TetrisX11UI::gridTileSize + 1), leftY, leftX + i * (TetrisX11UI::gridTileSize + 1), rightY);
    }
    for (int j = 0; j < TetrisUI::boardBoundaryRow + 1; j ++) {
        this->drawLine(TetrisX11UI::gridLineColor, leftX, leftY + j * (TetrisX11UI::gridTileSize + 1), rightX, leftY + j * (TetrisX11UI::gridTileSize + 1));
    }
}

void TetrisX11UI::renderWelcomeView() {
    this->drawString("This game is named Tetris", "white", 26, "helvetica", 30, 150);
    this->drawString("Press ENTER to start", "white", 26, "helvetica", 50, 550);
}





//
//void TetrisX11UI::interpretGameData() {
//    ::XClearWindow(deviceDisplay, *gameWindow);
//    if (gameData != nullptr) {
//        switch (gameData->gameStatus) {
//            case TetrisModel::GameStatus::NOT_STARTED:
//                this->renderNotStartedView();
//                break;
//            case TetrisModel::GameStatus::COUNT_DOWN:
//                this->renderCountDownView();
//                break;
//            case TetrisModel::GameStatus::IN_GAME:
//                this->renderInGameView();
//                break;
//            case TetrisModel::GameStatus::PAUSED:
//                this->renderPausedView();
//                break;
//            case TetrisModel::GameStatus::GAME_OVER:
//                this->renderGameOverView();
//                break;
//        }
//    }
//}
//
//
//void TetrisX11UI::renderCountDownView() {
//    this->drawString(std::to_string(3 - gameData->countDownTime / 1000), 101 - gameData->countDownTime % 1000 / 10, 180, 350);
//}
//
//void TetrisX11UI::renderInGameView() {
//    this->renderBoardGrid();
//    this->renderBoard();
//    this->renderShadowTetromino();
//    this->renderActiveTetromino();
//}
//
//void TetrisX11UI::renderPausedView() {
//    this->drawString("Paused", 24, 40, 150);
//}
//
//void TetrisX11UI::renderGameOverView() {
//    this->drawString("GameOver", 24, 40, 150);
//}
//
//

//
//void TetrisX11UI::renderBoard() {
//    for (int row = 0; row < 20; row ++) {
//        for (int column = 0; column < 10; column ++) {
//            string color;
//            switch ((gameData->gameBoard)[row][column]) {
//                case TetrisBoard::TileState::EMPTY:
//                    color = "black";
//                    break;
//                case TetrisBoard::TileState::I:
//                    color = "cyan";
//                    break;
//                case TetrisBoard::TileState::O:
//                    color = "yellow";
//                    break;
//                case TetrisBoard::TileState::T:
//                    color = "purple";
//                    break;
//                case TetrisBoard::TileState::S:
//                    color = "green";
//                    break;
//                case TetrisBoard::TileState::Z:
//                    color = "red";
//                    break;
//                case TetrisBoard::TileState::J:
//                    color = "blue";
//                    break;
//                case TetrisBoard::TileState::L:
//                    color = "orange";
//                    break;
//            }
//            if (color != "black") {
//                this->drawTile(row, column, color);
//            }
//        }
//    }
//}
//
//void TetrisX11UI::renderShadowTetromino() {
//    for (Position position : gameData->shadowTetrominoPositions) {
//        this->drawTile(position.row, position.column, "grey");
//    }
//}
//
//void TetrisX11UI::renderActiveTetromino() {
//    string color;
//    switch (gameData->activeTetromino) {
//        case TetrominoBlock::TetrominoType::I:
//            color = "cyan";
//            break;
//        case TetrominoBlock::TetrominoType::O:
//            color = "yellow";
//            break;
//        case TetrominoBlock::TetrominoType::T:
//            color = "purple";
//            break;
//        case TetrominoBlock::TetrominoType::S:
//            color = "green";
//            break;
//        case TetrominoBlock::TetrominoType::Z:
//            color = "red";
//            break;
//        case TetrominoBlock::TetrominoType::J:
//            color = "blue";
//            break;
//        case TetrominoBlock::TetrominoType::L:
//            color = "orange";
//            break;
//    }
//    for (Position position : gameData->activeTetrominoPositions) {
//        if (position.row < 20) {
//            this->drawTile(position.row, position.column, color);
//        }
//    }
//}
//
//void TetrisX11UI::renderNextTetromino() {
//
//}
//
//void TetrisX11UI::renderHoldingTetromino() {
//
//}
//
//void TetrisX11UI::drawTile(int row, int column, string color) {
//    row = 19 - row;
//    int xStart = (this->calculateWindowSizeX() - this->calculateBoardSizeX()) / 2 + 1 + column + column * TetrisX11UI::gridTileSize;
//    int yStart = (this->calculateWindowSizeY() - this->calculateBoardSizeY()) / 2 + 1 + row + row * TetrisX11UI::gridTileSize;
//    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap[color].pixel);
//    ::XFillRectangle(deviceDisplay, *gameWindow, *graphicsContext, xStart, yStart, TetrisX11UI::gridTileSize, TetrisX11UI::gridTileSize);
//}
//


