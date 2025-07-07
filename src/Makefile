# Makefile for source code compilation

CC = g++
CFLAGS = -std=c++17 -Wall -Wextra
LDFLAGS =

PROJECT_NAME = my_app
OUTPUT_NAME ?= $(PROJECT_NAME)
BUILD_OUTPUT = $(BUILD_DIR)/$(OUTPUT_NAME)
DIST_OUTPUT ?= ../dist/$(OUTPUT_NAME)

SRC_DIR = sources
INC_DIR = includes
OBJ_DIR = ../build/obj
BUILD_DIR = ../build

UNAME_S := $(shell uname -s)

ifdef PLATFORM
    ifeq ($(PLATFORM),LINUX)
        CFLAGS += -DPLATFORM_LINUX
        LDFLAGS += -lz
        CC = g++
    else ifeq ($(PLATFORM),MACOS)
        CFLAGS += -DPLATFORM_MACOS
        LDFLAGS += -lz
        CC = g++
    else ifeq ($(PLATFORM),MACOS_ARM64)
        CFLAGS += -DPLATFORM_MACOS -arch arm64
        LDFLAGS += -lz
        CC = g++
    else ifeq ($(PLATFORM),WINDOWS)
        CFLAGS += -DPLATFORM_WINDOWS
        LDFLAGS += -static -lz -lws2_32
        CC = x86_64-w64-mingw32-g++
    endif
else
    ifeq ($(UNAME_S),Linux)
        CFLAGS += -DPLATFORM_LINUX
        LDFLAGS += -static -Wl,-Bstatic -lz -Wl,-Bdynamic
    else ifeq ($(UNAME_S),Darwin)
        CFLAGS += -DPLATFORM_MACOS
        LDFLAGS += -lz
    else
        CFLAGS += -DPLATFORM_WINDOWS
        LDFLAGS += -static -lz -lws2_32
    endif
endif

SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

all: clean prepare build copy_to_dist

prepare:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(dir $(DIST_OUTPUT))

build: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BUILD_OUTPUT) $(OBJECTS) $(LDFLAGS)

copy_to_dist: build
	cp -f $(BUILD_OUTPUT) $(DIST_OUTPUT)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/*.o $(BUILD_OUTPUT) $(DIST_OUTPUT)

.PHONY: all clean prepare
