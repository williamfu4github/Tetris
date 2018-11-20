# Makefile
# note: all source files need to be .cpp
# note: main program _main symbol must be defined in main.cpp
# note: all test files need to be .cpp, with a _main symbol
# note: must have at least one test in TESTDIR

# default config=debug
ifndef config
    config=debug
endif

# default verbose=false
ifndef verbose
    verbose=false
endif

# if verbose=false, then silent
ifeq ($(verbose),false)
    SILENT = @
endif

# set variables
# make necessary changes here
# -----------------------------------------------------------------------------------------------------

    PROJECT       = Tetris
#    VERSION       = NOT COMPLETED
    CXX           = clang++
    HOMEDIR       = ..
    INCLDIR      := $(HOMEDIR)/Include

    SRCDIR       := $(HOMEDIR)/Source
    DEFINES       =
    INCLUDES     := -I$(INCLDIR) -I/usr/local/include
    LIBDIRS       = -L/usr/local/lib
    LIBS          = -lboost_program_options

    TESTDIR      := $(HOMEDIR)/Test
    TESTDEFS      =
    TESTINCLS    := -I$(INCLDIR)
    TESTLIBDIRS   =
    TESTLIBS      =

ifeq ($(config),debug)
    OBJDIR       := $(HOMEDIR)/Build/Debug
    CXXFLAGS     := -std=c++11 -Wall -Wextra -MMD -MP $(DEFINES) $(INCLUDES)
    LDFLAGS      := $(LIBDIRS) $(LIBS)
endif

ifeq ($(config),release)
    OBJDIR       := $(HOMEDIR)/Build/Release
    CXXFLAGS     := -std=c++11 -Wall -Wextra -MMD -MP -O3 -DNDEBUG $(DEFINES) $(INCLUDES)
    LDFLAGS      := $(LIBDIRS) $(LIBS)
endif

    TESTCXXFLAGS := -std=c++11 -Wall -Wextra -MMD -MP $(TESTDEFS) $(TESTINCLS)
    TESTLDFLAGS  := $(LIBDIRS) $(LIBS) $(TESTLIBDIRS) $(TESTLIBS)

# -----------------------------------------------------------------------------------------------------

# detect source files
SOURCES          := $(shell find $(SRCDIR) -type f -name '*.cpp')
OBJECTS          := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/Object/%.o)
OBJSUBDIRS       := $(shell echo $(dir $(OBJECTS)) | tr ' ' '\n' | sort | uniq | tr '\n' ' ')

# detect test files
TESTSRCS         := $(shell find $(TESTDIR) -type f -name '*.cpp')
TESTOBJS         := $(TESTSRCS:$(TESTDIR)/%.cpp=$(OBJDIR)/TestObject/%.o)
TESTS            := $(TESTSRCS:$(TESTDIR)/%.cpp=$(OBJDIR)/Test/%.out)
TESTOBJSUBDIRS   := $(shell echo $(dir $(TESTOBJS)) | tr ' ' '\n' | sort | uniq | tr '\n' ' ')
TESTSUBDIRS      := $(shell echo $(dir $(TESTS)) | tr ' ' '\n' | sort | uniq | tr '\n' ' ')
TESTLINKOBJS     := $(filter-out $(OBJDIR)/Object/main.o, $(OBJECTS))

# define options
.PHONY: $(PROJECT) clean help

# define functions
.PHONY: preBuild build buildTest runTest postBuild

# default option
$(PROJECT): preBuild build buildTest runTest postBuild

# before build of main program
preBuild:
	@ echo Start building $(PROJECT) in $(config) mode...
	$(SILENT) mkdir -p $(OBJSUBDIRS)
	$(SILENT) mkdir -p $(TESTOBJSUBDIRS)
	$(SILENT) mkdir -p $(TESTSUBDIRS)
	$(SILENT) rm -f $(OBJDIR)/RunTestLog.txt

# build the main program
build: $(HOMEDIR)/$(PROJECT)

# compile and link the main program if necessary
$(HOMEDIR)/$(PROJECT): $(OBJECTS)
	@ echo Linking $(PROJECT)...
	$(SILENT) $(CXX) $(LDFLAGS) $^ -o $(OBJDIR)/$(PROJECT)

# generic rule for making source .o files
$(OBJDIR)/Object/%.o: $(SRCDIR)/%.cpp
	@ echo Compiling $(<:$(SRCDIR)/%.cpp=%.cpp)...
	$(SILENT) $(CXX) $(CXXFLAGS) -c $< -o $@

# build all the test .out files
buildTest: $(TESTS)

# generic rule for making test .out and .o files
$(OBJDIR)/Test/%.out: $(OBJDIR)/TestObject/%.o $(TESTLINKOBJS)
	@ echo Making $(@:$(OBJDIR)/Test/%.out=%.out)...
	$(SILENT) $(CXX) $(TESTLDFLAGS) $^ -o $@
$(OBJDIR)/TestObject/%.o: $(TESTDIR)/%.cpp
	$(SILENT) $(CXX) $(TESTCXXFLAGS) -c $< -o $@

# run all the tests
runTest:
	@ echo Running tests...
	$(SILENT) for test in $(TESTS); do \
          ./$$test --log_level=message 1>>$(OBJDIR)/RunTestLog.txt 2>&1 \
          || (cat $(OBJDIR)/RunTestLog.txt; exit 1); \
      done

# after all tests run
postBuild:
	$(SILENT) cp $(OBJDIR)/$(PROJECT) $(HOMEDIR)
	@ echo Build Succeeded!

# tell make not to remove the intermediate test .o files
.PRECIOUS: $(TESTOBJS)

# let preprocessor detect .hpp dependencies and inject into make rules
-include $(OBJECTS:$(OBJDIR)/Object/%.o=$(OBJDIR)/Object/%.d)
-include $(TESTOBJS:$(OBJDIR)/TestObject/%.o=$(OBJDIR)/TestObject/%.d)

# option clean
clean:
	@ echo Cleaning $(PROJECT)...
	$(SILENT) rm -f $(HOMEDIR)/$(PROJECT)
	$(SILENT) rm -rf $(HOMEDIR)/Build/Debug
	$(SILENT) rm -rf $(HOMEDIR)/Build/Release
	@ echo Done!

# option help
help:
	@ echo ""
	@ echo "Usage: make [config=name] [verbose=bool] [target]"
	@ echo ""
	@ echo "configuration:"
	@ echo "   debug    (default)"
	@ echo "   release"
	@ echo ""
	@ echo "verbose:"
	@ echo "   true"
	@ echo "   false    (default)"
	@ echo ""
	@ echo "target:"
	@ echo "   $(PROJECT)   (default)"
	@ echo "   clean"
	@ echo "   help"
	@ echo ""
