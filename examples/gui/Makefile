# Main Makefile for GUI examples

GUI_FRAMEWORK ?= qt
PROJECT_NAME = my_app

UNAME_S := $(shell uname -s)
IS_MACOS := $(filter Darwin,$(UNAME_S))

.PHONY: all qt gtk wx clean docker-all docker-qt docker-gtk docker-wx local-all local-qt local-gtk local-wx

all: docker-$(GUI_FRAMEWORK)

local-all: local-qt local-gtk local-wx

local-qt:
	@echo "Building Qt example locally..."
	$(MAKE) -C qt all

local-gtk:
	@echo "Building GTK example locally..."
	$(MAKE) -C gtk all

local-wx:
	@echo "Building wxWidgets example locally..."
	$(MAKE) -C wx all

docker-all: docker-qt docker-gtk docker-wx

docker-qt:
	@echo "Building Qt example using Docker..."
	docker run --rm -v $(shell cd ../../ && pwd):/src $(PROJECT_NAME)-builder bash -c "cd /src/examples/gui/qt && make"

qt: docker-qt

docker-gtk:
	@echo "Building GTK example using Docker..."
	docker run --rm -v $(shell cd ../../ && pwd):/src $(PROJECT_NAME)-builder bash -c "cd /src/examples/gui/gtk && make"

gtk: docker-gtk

docker-wx:
	@echo "Building wxWidgets example using Docker..."
	docker run --rm -v $(shell cd ../../ && pwd):/src $(PROJECT_NAME)-builder bash -c "cd /src/examples/gui/wx && make"

wx: docker-wx

clean:
	@echo "Cleaning all GUI examples..."
	$(MAKE) -C qt clean
	$(MAKE) -C gtk clean
	$(MAKE) -C wx clean
	@echo "All GUI examples cleaned"
