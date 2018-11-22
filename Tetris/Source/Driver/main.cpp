#include "Driver/TetrisCommandLineOptionsHandler.hpp"
#include "Driver/GameTetris.hpp"

namespace {
    void configureProgramSettings() {
        std::ios_base::sync_with_stdio(false);
    }
    
    void runMainProgram() {
        GameTetris gameTetris;
        gameTetris.playGame();
    }
}

int main(int argc, char** argv) {
    ::configureProgramSettings();
    TetrisCommandLineOptionsHandler cmdOptionsHandler;
    switch (cmdOptionsHandler.handleOptions(argc, argv)) {
        case CommandLineOptionsHandler::ResultStatus::EXIT_NO_ERROR:
            return EXIT_SUCCESS;
        case CommandLineOptionsHandler::ResultStatus::EXIT_WITH_ERROR:
            return EXIT_FAILURE;
        case CommandLineOptionsHandler::ResultStatus::CONTINUE_EXECUTION:
            try {
                ::runMainProgram();
                return EXIT_SUCCESS;
            }
            catch (...) {
                return EXIT_FAILURE;
            }
    }
}
