# Makefile for tests with Google Test



CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I../src/includes -pthread

SRC_DIR = ../src/sources
TEST_DIR = .
BUILD_DIR = build

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    CXXFLAGS += -DPLATFORM_LINUX
    GTEST_LIBS = -lgtest -lgtest_main
else ifeq ($(UNAME_S),Darwin)
    CXXFLAGS += -DPLATFORM_MACOS
    GTEST_LIBS = -lgtest -lgtest_main
else
    CXXFLAGS += -DPLATFORM_WINDOWS
    GTEST_LIBS = -lgtest -lgtest_main
endif

SRC_FILES = $(filter-out $(SRC_DIR)/main.cpp, $(wildcard $(SRC_DIR)/*.cpp))
TEST_FILES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(TEST_FILES))
SRC_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRC_FILES))

all: prepare test

prepare:
	@mkdir -p $(BUILD_DIR)

test: $(BUILD_DIR)/run_tests
	@echo "Running tests..."
	@./$(BUILD_DIR)/run_tests
	@echo "Cleaning object files..."
	@rm -f $(BUILD_DIR)/*.o

$(BUILD_DIR)/run_tests: $(SRC_OBJS) $(TEST_OBJS)
	@echo "Linking test executable..."
	@$(CXX) $(CXXFLAGS) -o $@ $^ $(GTEST_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | prepare
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.cpp | prepare
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	@echo "Cleaning up..."
	@rm -rf $(BUILD_DIR)

install-gtest:
ifeq ($(UNAME_S),Linux)
	@echo "Installing Google Test for Linux..."
	@sudo apt-get update
	@sudo apt-get install -y libgtest-dev cmake
	@cd /usr/src/gtest && sudo cmake . && sudo make && sudo cp *.a /usr/lib
else ifeq ($(UNAME_S),Darwin)
	@echo "Installing Google Test for macOS..."
	@brew install googletest
else
	@echo "Please install Google Test manually for your Windows system"
endif

.PHONY: all prepare test clean install-gtest
