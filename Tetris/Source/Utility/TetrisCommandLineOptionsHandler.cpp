#include "Utility/TetrisCommandLineOptionsHandler.hpp"

#include <iostream>
using std::cout;
using std::endl;
namespace program_options = boost::program_options;

TetrisCommandLineOptionsHandler::TetrisCommandLineOptionsHandler() {
    optionsDescription->add_options()("help,h", "Print help messages")("version,v", "Print version info");
}

TetrisCommandLineOptionsHandler::~TetrisCommandLineOptionsHandler() {
}

CommandLineOptionsHandler::ResultStatus TetrisCommandLineOptionsHandler::respondOptions() const {
    if (optionsMap->count("help") == 1) {
        this->respondOptionHelp();
        return CommandLineOptionsHandler::ResultStatus::EXIT_NO_ERROR;
    }
    else if (optionsMap->count("version") == 1) {
        this->respondOptionVersion();
        return CommandLineOptionsHandler::ResultStatus::EXIT_NO_ERROR;
    }
    else {
        return CommandLineOptionsHandler::ResultStatus::CONTINUE_EXECUTION;
    }
}

void TetrisCommandLineOptionsHandler::respondOptionHelp() const {
    cout << "A lite version of the classic game Tetris" << endl;
    cout << endl;
    cout << *optionsDescription << endl;
}

void TetrisCommandLineOptionsHandler::respondOptionVersion() const {
    cout << "Version info not available" << endl;
}
