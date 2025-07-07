# Main Makefile for cross-platform compilation

PROJECT_NAME = my_app
BUILD_TIMESTAMP = $(shell date +%s)

SRC_DIR = src
BUILD_DIR = build
DIST_DIR = dist

# Detect if we're running on macOS
UNAME_S := $(shell uname -s)
IS_MACOS := $(filter Darwin,$(UNAME_S))

.PHONY: all clean clean-all linux macos macos_arm64 windows update_timestamp test install-gtest crossplatform

all: clean docker-test docker-compile
ifeq ($(IS_MACOS),Darwin)
	@echo "\nDetected macOS environment, replacing Docker macOS binary with native version..."
	@if [ -f "$(DIST_DIR)/$(PROJECT_NAME)_macos" ]; then \
		rm -f "$(DIST_DIR)/$(PROJECT_NAME)_macos"; \
		echo "Removed non-native macOS binary"; \
	fi
	@echo "Building native macOS binary..."
	@cd $(SRC_DIR) && $(MAKE) PLATFORM=MACOS OUTPUT_NAME=$(PROJECT_NAME)_macos DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)_macos
	@chmod +x "$(DIST_DIR)/$(PROJECT_NAME)_macos"
	@echo "Native macOS binary created: $(DIST_DIR)/$(PROJECT_NAME)_macos"
endif

update_timestamp:
	@echo "Updating build timestamp..."
	@echo "#define BUILD_TIMESTAMP $(BUILD_TIMESTAMP)" > $(SRC_DIR)/includes/build_info.h
	@echo "Updated BUILD_TIMESTAMP to $(BUILD_TIMESTAMP)"

linux:
	@echo "Building for Linux (x86_64)..."
	@mkdir -p $(DIST_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(SRC_DIR) && $(MAKE) PLATFORM=LINUX OUTPUT_NAME=$(PROJECT_NAME)_linux DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)_linux
	@echo "Linux build completed: $(DIST_DIR)/$(PROJECT_NAME)_linux"

macos:
	@echo "Building for macOS (x86_64)..."
	@mkdir -p $(DIST_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(SRC_DIR) && $(MAKE) PLATFORM=MACOS OUTPUT_NAME=$(PROJECT_NAME)_macos DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)_macos
	@echo "macOS build completed: $(DIST_DIR)/$(PROJECT_NAME)_macos"

macos_arm64:
	@echo "Building for macOS (ARM64)..."
	@mkdir -p $(DIST_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(SRC_DIR) && $(MAKE) PLATFORM=MACOS_ARM64 OUTPUT_NAME=$(PROJECT_NAME)_macos_arm64 DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)_macos_arm64
	@echo "macOS ARM64 build completed: $(DIST_DIR)/$(PROJECT_NAME)_macos_arm64"

windows:
	@echo "Building for Windows (x86_64)..."
	@mkdir -p $(DIST_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(SRC_DIR) && $(MAKE) PLATFORM=WINDOWS OUTPUT_NAME=$(PROJECT_NAME)_windows.exe DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)_windows.exe
	@echo "Windows build completed: $(DIST_DIR)/$(PROJECT_NAME)_windows.exe"

local:
	@echo "Building for local platform..."
	@mkdir -p $(DIST_DIR)
	@mkdir -p $(BUILD_DIR)
	@cd $(SRC_DIR) && $(MAKE) OUTPUT_NAME=$(PROJECT_NAME) DIST_OUTPUT=../$(DIST_DIR)/$(PROJECT_NAME)
	@echo "Local build completed: $(DIST_DIR)/$(PROJECT_NAME)"

clean:
	@echo "Cleaning build files..."
	@rm -rf $(BUILD_DIR)/*
	@cd $(SRC_DIR) && $(MAKE) clean
	@cd tests && $(MAKE) clean
	@echo "Clean completed (distribution files preserved)"

clean-all:
	@echo "Removing all generated files..."
	@rm -rf $(BUILD_DIR)/* $(DIST_DIR)/*
	@cd $(SRC_DIR) && $(MAKE) clean
	@cd tests && $(MAKE) clean
	@echo "All files cleaned"

test:
	@echo "Running unit tests..."
	@cd tests && $(MAKE) test

install-gtest:
	@echo "Installing Google Test dependencies..."
	@cd tests && $(MAKE) install-gtest

docker-build:
	docker build -t $(PROJECT_NAME)-builder -f Dockerfile.builder .

crossplatform: update_timestamp linux macos windows

docker-compile: docker-build
	docker run --rm -v $(PWD):/src $(PROJECT_NAME)-builder make crossplatform

docker-linux: docker-build
	docker run --rm -v $(PWD):/src $(PROJECT_NAME)-builder make linux

docker-windows: docker-build
	docker run --rm -v $(PWD):/src $(PROJECT_NAME)-builder make windows

docker-test: docker-build
	docker run --rm -v $(PWD):/src $(PROJECT_NAME)-builder make test
