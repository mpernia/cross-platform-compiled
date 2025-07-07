# wxWidgets example Makefile

PROJECT_NAME = my_wx_app

ROOT_DIR = ../../..
SRC_DIR = $(ROOT_DIR)/src
BUILD_DIR = build
DIST_DIR = $(ROOT_DIR)/dist

WX_CONFIG = wx-config
WX_CXXFLAGS = $(shell $(WX_CONFIG) --cxxflags)
WX_LIBS = $(shell $(WX_CONFIG) --libs)

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra $(WX_CXXFLAGS) -I$(SRC_DIR)/includes
LDFLAGS = $(WX_LIBS) -lz

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    PLATFORM = LINUX
    CFLAGS += -DPLATFORM_LINUX
else ifeq ($(UNAME_S),Darwin)
    PLATFORM = MACOS
    CFLAGS += -DPLATFORM_MACOS

    UNAME_M := $(shell uname -m)
    ifeq ($(UNAME_M),arm64)
        PLATFORM = MACOS_ARM64
        CFLAGS += -arch arm64
    endif
else
    PLATFORM = WINDOWS
    CFLAGS += -DPLATFORM_WINDOWS
    LDFLAGS += -static -lws2_32
    BINARY_EXTENSION = .exe
endif

BINARY_NAME = $(PROJECT_NAME)_$(shell echo $(PLATFORM) | tr A-Z a-z)$(BINARY_EXTENSION)
SOURCES = main.cpp $(SRC_DIR)/sources/logger.cpp

MAIN_OBJ = $(BUILD_DIR)/main.o
LOGGER_OBJ = $(BUILD_DIR)/logger.o
OBJECTS = $(MAIN_OBJ) $(LOGGER_OBJ)

OUTPUT = $(BUILD_DIR)/$(BINARY_NAME)
DIST_OUTPUT = $(DIST_DIR)/$(BINARY_NAME)

.PHONY: all clean

all: clean prepare build

prepare:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(DIST_DIR)
	@echo "Cleaning previous object files..."
	@rm -f $(BUILD_DIR)/*.o

build: $(OUTPUT)
	@cp -f $(OUTPUT) $(DIST_OUTPUT)
	@echo "Build completed: $(DIST_OUTPUT)"

$(OUTPUT): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(MAIN_OBJ): main.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LOGGER_OBJ): $(SRC_DIR)/sources/logger.cpp
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)/*
	@echo "Cleaned build files"
