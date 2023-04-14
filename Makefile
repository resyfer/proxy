BIN:=proxy
VERSION:=1.0.0

OS?=UNIX
ARCH?=x86_64
VARIANT?=release

ifeq ($(OS),UNIX)
SH?=bash
endif

TARGET=$(firstword $(MAKECMDGOALS))
ifeq ($(TARGET),)
TARGET=all
endif

all:
	@if [ ! -d ./bin ]; then \
		mkdir ./bin; \
	fi
	@if [ ! -d ./obj ]; then \
		mkdir ./obj; \
	fi
ifeq ($(OS),UNIX)
	@echo "Executing Unix Makefile"
	@$(MAKE) -f $(CURDIR)/unix.mak $(firstword $(MAKECMDGOALS)) BIN=$(BIN) VERSION=$(VERSION) OS=$(OS) ARCH=$(ARCH) VARIANT=$(VARIANT) SH=$(SH)
else ifeq ($(OS),WIN32)
	@echo Executing Windows Makefile
	@$(MAKE) -f $(CURDIR)/win.mak $(firstword $(MAKECMDGOALS)) BIN=$(BIN) VERSION=$(VERSION) OS=$(OS) ARCH=$(ARCH) VARIANT=$(VARIANT)
endif

install: all