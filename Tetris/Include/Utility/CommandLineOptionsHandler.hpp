#ifndef CommandLineOptionsHandler_hpp
#define CommandLineOptionsHandler_hpp

#include <boost/program_options.hpp>

class CommandLineOptionsHandler {
public:
    enum class ResultStatus {
        EXIT_NO_ERROR,
        EXIT_WITH_ERROR,
        CONTINUE_EXECUTION
    };
    
public:
    virtual ~CommandLineOptionsHandler() = 0;
    CommandLineOptionsHandler::ResultStatus handleOptions(int argc, char** argv);
protected:
    CommandLineOptionsHandler();
private:
    virtual CommandLineOptionsHandler::ResultStatus respondOptions() const = 0;
    
protected:
    boost::program_options::options_description* optionsDescription;
    boost::program_options::variables_map* optionsMap;
};

#endif
