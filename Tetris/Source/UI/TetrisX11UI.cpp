#include "UI/TetrisX11UI.hpp"

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
const int TetrisX11UI::windowMargin = 30;
const int TetrisX11UI::dashboardSize = 140;
const string TetrisX11UI::shadowColor = "grey";

string TetrisX11UI::tetrominoColorNomination(TetrominoType blockType) {
    switch (blockType) {
        case TetrominoType::EMPTY:
            return "black";
        case TetrominoType::I:
            return "cyan";
        case TetrominoType::O:
            return "yellow";
        case TetrominoType::T:
            return "purple";
        case TetrominoType::S:
            return "green";
        case TetrominoType::Z:
            return "red";
        case TetrominoType::J:
            return "blue";
        case TetrominoType::L:
            return "orange";
    }
}

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
        case ClientMessage: {
            unsigned long code = static_cast<unsigned long>(event.xclient.data.l[0]);
            if (code == ::XInternAtom(deviceDisplay, "WM_DELETE_WINDOW", false)) {
                return TetrisUI::ControllerEvent::WINDOW_CLOSE;
            }
            break;
        }
        case KeyPress: {
            KeySym key = ::XLookupKeysym(&event.xkey, 0);
            if (key == XK_q) {
                return TetrisUI::ControllerEvent::KEY_Q;
            }
            else if (key == XK_Return) {
                return TetrisUI::ControllerEvent::KEY_RETURN;
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
        // TODO receive only when auto-repeat happens, need to remove in future
        case KeyRelease:
            break;
    }
    return TetrisUI::ControllerEvent::NO_EVENT;
}

void TetrisX11UI::renderView(TetrisData* gameData) {
    ::XClearWindow(deviceDisplay, *gameWindow);
    switch (gameData->gameState) {
        case GameState::WELCOME:
            this->renderWelcomeView();
            break;
        case GameState::COUNT_DOWN:
            this->renderCountDownView(gameData);
            break;
        case GameState::IN_GAME:
            this->renderInGameView(gameData);
            break;
        case GameState::PAUSED:
            this->renderPausedView();
            break;
        case GameState::GAME_OVER:
            this->renderGameOverView();
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
    return (this->calculateBoardSizeX() + TetrisX11UI::windowMargin * 2);
}

int TetrisX11UI::calculateWindowSizeY() const {
    return (this->calculateBoardSizeY() + TetrisX11UI::windowMargin * 2 + TetrisX11UI::dashboardSize);
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

void TetrisX11UI::renderWelcomeView() {
    this->drawString("This game is named Tetris", "white", 26, "helvetica", 30, 150);
    this->drawString("Press ENTER to start", "white", 26, "helvetica", 50, 550);
}

void TetrisX11UI::renderCountDownView(TetrisData* gameData) {
    int numberDisplay = (gameData->countDownTime - 1) / 1000 + 1;
    int fontSize = gameData->countDownTime % 1000 / 15 + 2;
    this->drawString(std::to_string(numberDisplay), "white", fontSize, "helvetica", 175, 350);
}

void TetrisX11UI::renderInGameView(TetrisData* gameData) {
    this->renderBoardGrid();
    this->renderBoard(gameData);
    this->renderShadowTetromino(gameData);
    this->renderActiveTetromino(gameData);
    this->renderDashboard(gameData);
}

void TetrisX11UI::renderPausedView() {
    this->drawString("Paused", "white", 26, "helvetica", 40, 150);
}

void TetrisX11UI::renderGameOverView() {
    this->drawString("Game Over", "white", 26, "helvetica", 40, 150);
}

void TetrisX11UI::renderBoardGrid() {
    int leftX = TetrisX11UI::windowMargin;
    int rightX = leftX + this->calculateBoardSizeX() - 1;
    int leftY = TetrisX11UI::windowMargin + TetrisX11UI::dashboardSize;
    int rightY = leftY + this->calculateBoardSizeY() - 1;
    for (int i = 0; i < TetrisUI::boardSizeColumn + 1; i ++) {
        this->drawLine(TetrisX11UI::gridLineColor, leftX + i * (TetrisX11UI::gridTileSize + 1), leftY, leftX + i * (TetrisX11UI::gridTileSize + 1), rightY);
    }
    for (int j = 0; j < TetrisUI::boardBoundaryRow + 1; j ++) {
        this->drawLine(TetrisX11UI::gridLineColor, leftX, leftY + j * (TetrisX11UI::gridTileSize + 1), rightX, leftY + j * (TetrisX11UI::gridTileSize + 1));
    }
}

void TetrisX11UI::renderOneBlock(Position position, string color) {
    int row = TetrisUI::boardBoundaryRow - 1 - position.row;
    int column = position.column;
    int leftX = TetrisX11UI::windowMargin + 1 + column * TetrisX11UI::gridTileSize + column;
    int leftY = TetrisX11UI::windowMargin + TetrisX11UI::dashboardSize + 1 + row * TetrisX11UI::gridTileSize + row;
    ::XSetForeground(deviceDisplay, *graphicsContext, colorMap[color].pixel);
    ::XFillRectangle(deviceDisplay, *gameWindow, *graphicsContext, leftX, leftY, TetrisX11UI::gridTileSize, TetrisX11UI::gridTileSize);
}

void TetrisX11UI::renderBoard(TetrisData* gameData) {
    for (int row = 0; row < TetrisUI::boardBoundaryRow; row ++) {
        for (int column = 0; column < TetrisUI::boardSizeColumn; column ++) {
            if (gameData->gameBoard[row][column] != TetrominoType::EMPTY) {
                this->renderOneBlock(Position(row, column), TetrisX11UI::tetrominoColorNomination(gameData->gameBoard[row][column]));
            }
        }
    }
}

void TetrisX11UI::renderActiveTetromino(TetrisData* gameData) {
    for (Position position : gameData->activeTetrominoPositions) {
        if (position.row < TetrisX11UI::boardBoundaryRow) {
            this->renderOneBlock(position, TetrisX11UI::tetrominoColorNomination(gameData->activeTetromino));
        }
    }
}

void TetrisX11UI::renderShadowTetromino(TetrisData* gameData) {
    for (Position position : gameData->shadowTetrominoPositions) {
        if (position.row < TetrisX11UI::boardBoundaryRow) {
            this->renderOneBlock(position, TetrisX11UI::shadowColor);
        }
    }
}

void TetrisX11UI::renderDashboard(TetrisData* gameData) {
    this->drawString("Holding:", "white", 20, "helvetica", 40, 50);
    this->renderNextTetromino(gameData);
    this->drawString("Next:", "white", 20, "helvetica", 240, 50);
    this->renderHoldingTetromino(gameData);
}

void TetrisX11UI::renderNextTetromino(TetrisData* gameData) {
    for (Position position : gameData->nextTetrominoPositions) {
        position.row = position.row + TetrisX11UI::boardBoundaryRow + 2;
        position.column += 6;
        this->renderOneBlock(position, TetrisX11UI::tetrominoColorNomination(gameData->nextTetromino));
    }
}

void TetrisX11UI::renderHoldingTetromino(TetrisData* gameData) {
    for (Position position : gameData->holdingTetrominoPositions) {
        position.row = position.row + TetrisX11UI::boardBoundaryRow + 2;
        this->renderOneBlock(position, TetrisX11UI::tetrominoColorNomination(gameData->holdingTetromino));
    }
}
