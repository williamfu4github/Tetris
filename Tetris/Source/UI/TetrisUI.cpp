#include "UI/TetrisUI.hpp"

TetrisUI::~TetrisUI() {
}

TetrisUI::TetrisUI() {
}

TetrisUI::ControllerEvent TetrisUI::getNextEvent() {
    return TetrisUI::ControllerEvent::NO_EVENT;
}
