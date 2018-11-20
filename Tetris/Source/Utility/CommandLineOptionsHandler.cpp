#include "Utility/CommandLineOptionsHandler.hpp"

#include <iostream>
using std::cerr;
using std::endl;
namespace program_options = boost::program_options;


CommandLineOptionsHandler::~CommandLineOptionsHandler() {
    delete optionsDescription;
    delete optionsMap;
}

CommandLineOptionsHandler::CommandLineOptionsHandler() {
    optionsDescription = new program_options::options_description("Options");
    optionsMap = new program_options::variables_map;
}

// PRE: can only be called once
CommandLineOptionsHandler::ResultStatus CommandLineOptionsHandler::handleOptions(int argc, char** argv) {
    try {
        program_options::store(program_options::parse_command_line(argc, argv, *optionsDescription), *optionsMap);
        program_options::notify(*optionsMap);
    }
    catch (program_options::error& e) {
        cerr << "ERROR: " << e.what() << endl;
        cerr << endl;
        cerr << *optionsDescription << endl;
        return CommandLineOptionsHandler::ResultStatus::EXIT_WITH_ERROR;
    }
    return this->respondOptions();
}
