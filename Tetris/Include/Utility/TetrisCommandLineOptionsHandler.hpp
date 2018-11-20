#ifndef TetrisCommandLineOptionsHandler_hpp
#define TetrisCommandLineOptionsHandler_hpp

#include "Utility/CommandLineOptionsHandler.hpp"

class TetrisCommandLineOptionsHandler : public CommandLineOptionsHandler {
public:
    TetrisCommandLineOptionsHandler();
    ~TetrisCommandLineOptionsHandler() override;
private:
    CommandLineOptionsHandler::ResultStatus respondOptions() const override;
    void respondOptionHelp() const;
    void respondOptionVersion() const;
};

#endif
