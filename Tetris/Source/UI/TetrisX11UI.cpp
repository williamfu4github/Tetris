#include "UI/TetrisX11UI.hpp"

TetrisX11UI::TetrisX11UI():
    TetrisUI() {
}

TetrisX11UI::~TetrisX11UI() {
}

TetrisUI::ControllerEvent TetrisX11UI::getNextEvent() {
    return TetrisUI::ControllerEvent::NO_EVENT;
}

void TetrisX11UI::renderView(TetrisData* gameData) {
    return;
}

//#include "TetrisData.hpp"
//#include <X11/Xutil.h>
//#include <iostream>
//#include <vector>
//using std::cerr;
//using std::endl;
//using std::string;
//using std::vector;
//
//const string TetrisX11UI::windowTitle = "Tetris";
//const int TetrisX11UI::gridTileSize = 30;
//const int TetrisX11UI::windowMarginX = 60;
//const int TetrisX11UI::windowMarginY = 80;
//
//TetrisX11UI::TetrisX11UI():
//    TetrisUI() {
//    deviceDisplay = ::XOpenDisplay(nullptr);
//    if (deviceDisplay == nullptr) {
//        cerr << "ERROR: X11 cannot open device display" << endl;
//    }
//    deviceScreen = ::XDefaultScreen(deviceDisplay);
//    this->createGameWindow();
//    this->createGraphicalResource();
//}
//
//TetrisX11UI::~TetrisX11UI() {
//    ::XDestroyWindow(deviceDisplay, *gameWindow);
//    delete gameWindow;
//    ::XFreeGC(deviceDisplay, *graphicsContext);
//    delete graphicsContext;
//    ::XCloseDisplay(deviceDisplay);
//}
//
//TetrisUI::ControllerEvent TetrisX11UI::getNextEvent() {
//    if (::XPending(deviceDisplay) == 0) {
//        return TetrisUI::ControllerEvent::NO_EVENT;
//    }
//    XEvent event;
//    ::XNextEvent(deviceDisplay, &event);
//    switch (event.type) {
//        case Expose:
//            this->interpretGameData();
//            return TetrisUI::ControllerEvent::NO_EVENT;
//        case ClientMessage:
//            if (event.xclient.data.l[0] == ::XInternAtom(deviceDisplay, "WM_DELETE_WINDOW", false)) {
//                return TetrisUI::ControllerEvent::WINDOW_CLOSE;
//            }
//            break;
//        case KeyPress:
//        {
//            KeySym key = ::XLookupKeysym(&event.xkey, 0);
//            if (key == XK_Return) {
//                return TetrisUI::ControllerEvent::KEY_ENTER;
//            }
//            else if (key == XK_Left) {
//                return TetrisUI::ControllerEvent::KEY_LEFT;
//            }
//            else if (key == XK_Right) {
//                return TetrisUI::ControllerEvent::KEY_RIGHT;
//            }
//            else if (key == XK_Down) {
//                return TetrisUI::ControllerEvent::KEY_DOWN;
//            }
//            else if (key == XK_Up) {
//                return TetrisUI::ControllerEvent::KEY_UP;
//            }
//            else if (key == XK_space) {
//                return TetrisUI::ControllerEvent::KEY_SPACE;
//            }
//            else if (key == XK_c) {
//                return TetrisUI::ControllerEvent::KEY_C;
//            }
//            else if (key == XK_v) {
//                return TetrisUI::ControllerEvent::KEY_V;
//            }
//            break;
//        }
//        default:
//            return TetrisUI::ControllerEvent::NO_EVENT;
//    }
//    return TetrisUI::ControllerEvent::NO_EVENT;
//}
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
//void TetrisX11UI::renderNotStartedView() {
//    this->drawString("This game is named Tetris", 26, 30, 150);
//    this->drawString("Press ENTER to start", 26, 50, 550);
//}
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
//void TetrisX11UI::createGameWindow() {
//    gameWindow = new Window;
//    *gameWindow = ::XCreateSimpleWindow(deviceDisplay, ::XRootWindow(deviceDisplay, deviceScreen), this->calculateWindowPositionX(), this->calculateWindowPositionY(), this->calculateWindowSizeX(), this->calculateWindowSizeY(), 1, ::XBlackPixel(deviceDisplay, deviceScreen), ::XBlackPixel(deviceDisplay, deviceScreen));
//    XSizeHints* wmSizeHint = ::XAllocSizeHints();
//    wmSizeHint->min_width = this->calculateWindowSizeX();
//    wmSizeHint->min_height = this->calculateWindowSizeY();
//    wmSizeHint->max_width = this->calculateWindowSizeX();
//    wmSizeHint->max_height = this->calculateWindowSizeY();
//    wmSizeHint->flags = PPosition | PSize | PMinSize | PMaxSize;
//    ::XSetStandardProperties(deviceDisplay, *gameWindow, TetrisX11UI::windowTitle.c_str(), nullptr, None, nullptr, 0, wmSizeHint);
//    ::XFree(wmSizeHint);
//    Atom wmCloseWindow = ::XInternAtom(deviceDisplay, "WM_DELETE_WINDOW", false);
//    ::XSetWMProtocols(deviceDisplay, *gameWindow, &wmCloseWindow, 1);
//    ::XSelectInput(deviceDisplay, *gameWindow, ExposureMask | KeyPressMask);
//    ::XMapRaised(deviceDisplay, *gameWindow);
//}
//
//void TetrisX11UI::createGraphicalResource() {
//    graphicsContext = new GC;
//    *graphicsContext = ::XCreateGC(deviceDisplay, *gameWindow, 0, nullptr);
//    Colormap palette = ::XDefaultColormap(deviceDisplay, deviceScreen);
//    vector<string> colorList{"black", "white", "grey", "brown", "cyan", "yellow", "purple", "green", "red", "blue", "orange"};
//    for (string colorString : colorList) {
//        XColor color;
//        if (::XAllocNamedColor(deviceDisplay, palette, colorString.c_str(), &color, &color) == 0) {
//            cerr << "ERROR: X11 cannot find color " << colorString << " for the device display" << endl;
//        }
//        colorMap[colorString] = color;
//    }
//}
//
//void TetrisX11UI::renderBoardGrid() {
//    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap["brown"].pixel);
//    int xStart = (this->calculateWindowSizeX() - this->calculateBoardSizeX()) / 2;
//    int xEnd = xStart + this->calculateBoardSizeX() - 1;
//    int yStart = (this->calculateWindowSizeY() - this->calculateBoardSizeY()) / 2;
//    int yEnd = yStart + this->calculateBoardSizeY() - 1;
//    for (int i = 0; i < 11; i ++) {
//        ::XDrawLine(deviceDisplay, *gameWindow, *graphicsContext, xStart + i + i * TetrisX11UI::gridTileSize, yStart, xStart + i + i * TetrisX11UI::gridTileSize, yEnd);
//    }
//    for (int j = 0; j < 21; j ++) {
//        ::XDrawLine(deviceDisplay, *gameWindow, *graphicsContext, xStart, yStart + j + j * TetrisX11UI::gridTileSize, xEnd, yStart + j + j * TetrisX11UI::gridTileSize);
//    }
//}
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
//void TetrisX11UI::drawString(string text, int fontSize, int x, int y) {
//    string font = "-*-helvetica-*-r-*-*-" + std::to_string(fontSize) + "-*-*-*-*-*-*-*";
//    ::XSetFont(deviceDisplay, *graphicsContext, ::XLoadFont(deviceDisplay, font.c_str()));
//    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap["white"].pixel);
//    ::XDrawString(deviceDisplay, *gameWindow, *graphicsContext, x, y, text.c_str(), static_cast<int>(text.size()));
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
//int TetrisX11UI::calculateBoardSizeX() const {
//    return gridTileSize * 10 + 11;
//}
//
//int TetrisX11UI::calculateBoardSizeY() const {
//    return gridTileSize * 20 + 21;
//}
//
//int TetrisX11UI::calculateWindowSizeX() const {
//    return (this->calculateBoardSizeX() + TetrisX11UI::windowMarginX);
//}
//
//int TetrisX11UI::calculateWindowSizeY() const {
//    return (this->calculateBoardSizeY() + TetrisX11UI::windowMarginY);
//}
//
//int TetrisX11UI::calculateWindowPositionX() const {
//    return (::XDisplayWidth(deviceDisplay, deviceScreen) - this->calculateWindowSizeX()) / 2;
//}
//
//int TetrisX11UI::calculateWindowPositionY() const {
//    return (::XDisplayHeight(deviceDisplay, deviceScreen) - this->calculateWindowSizeY()) / 2;
//}

