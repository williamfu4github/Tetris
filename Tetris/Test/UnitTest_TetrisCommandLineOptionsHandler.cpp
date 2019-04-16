#include "Driver/TetrisCommandLineOptionsHandler.hpp"

#define BOOST_TEST_MODULE "Class_TetrisCommandLineOptionsHandler"
#include <boost/test/unit_test.hpp>
#include <wordexp.h>
using MainStatus = CommandLineOptionsHandler::ResultStatus;

struct TestFixture_Method_handle {
public:
    TestFixture_Method_handle() {
        tetrisCmdLineOptionsHandler = new TetrisCommandLineOptionsHandler;
        cmdLineOptions = new wordexp_t;
    }
    ~TestFixture_Method_handle() {
        delete tetrisCmdLineOptionsHandler;
        delete cmdLineOptions;
    }
    MainStatus handle() {
        return tetrisCmdLineOptionsHandler->handleOptions(static_cast<int>(cmdLineOptions->we_wordc), cmdLineOptions->we_wordv);
    }
    
public:
    CommandLineOptionsHandler* tetrisCmdLineOptionsHandler;
    wordexp_t* cmdLineOptions;
};

BOOST_FIXTURE_TEST_SUITE( Method_handle_ExpectedInput, TestFixture_Method_handle )

    BOOST_AUTO_TEST_CASE( noOption ) {
        ::wordexp("./Tetris", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( optionHelpLong ) {
        ::wordexp("./Tetris --help", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_NO_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( optionHelpShort ) {
        ::wordexp("./Tetris -h", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_NO_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( optionVersionLong ) {
        ::wordexp("./Tetris --version", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_NO_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( optionVersionShort ) {
        ::wordexp("./Tetris -v", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_NO_ERROR);
        ::wordfree(cmdLineOptions);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_FIXTURE_TEST_SUITE( Method_handle_UnexpectedInput, TestFixture_Method_handle )

    BOOST_AUTO_TEST_CASE( extraSpace ) {
        ::wordexp(" ./Tetris  ", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( extraWord1 ) {
        ::wordexp("./Tetris apple", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( extraWord2 ) {
        ::wordexp("./Tetris apple bee cat", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( badOption1 ) {
        ::wordexp("./Tetris -t", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_WITH_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( badOption2 ) {
        ::wordexp("./Tetris --varsion", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_WITH_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( bothOptions ) {
        ::wordexp("./Tetris --help -v", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::EXIT_NO_ERROR);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( separatedOption ) {
        ::wordexp("./Tetris -- version", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( separatedOptions ) {
        ::wordexp("./Tetris -- help -- version", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

    BOOST_AUTO_TEST_CASE( separatedBadOptions ) {
        ::wordexp("./Tetris -- ver -- help!", cmdLineOptions, 0);
        BOOST_CHECK(this->handle() == MainStatus::CONTINUE_EXECUTION);
        ::wordfree(cmdLineOptions);
    }

BOOST_AUTO_TEST_SUITE_END()
