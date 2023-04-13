# User
USER:=$(shell echo $$USERNAME)

# Config Path
CONFIG_PATH?=/c/Users/$(USER)/$(BIN)

BIN_DIR:=bin
SRC_DIR:=src
OBJ_DIR:=obj
HEAD_DIR:=include
DEP_DIR:=$(OBJ_DIR)
INC_DIR=.

# CC and C Flags
CC=gcc
CFLAGS=-std=gnu11

ifeq ($(VARIANT),debug)
CFLAGS+= -Og
else
CFLAGS+= -Ofast
endif
CFLAGS+= $(addprefix -I,$(INC_DIR))

$(info OS: $(OS), Arch: $(ARCH))

# Files
SRCFILES := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJFILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCFILES))
DEPFILES := $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRCFILES))
HEADERFILES:=$(shell find $(HEAD_DIR) -type f -name "*.h")

.PHONY: all clean run install

all: ./$(BIN_DIR)/$(BIN) win.mak Makefile

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c win.mak Makefile
	@echo "Compiling $< file"
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@ -static

$(BIN_DIR)/$(BIN): $(OBJFILES) win.mak Makefile
	@echo "Building Final Binary!"
	@$(CC) $(CFLAGS) $(OBJFILES) -o $(BIN_DIR)/$(BIN).exe -static
	@echo "All Done!"
	@echo ""
	@echo ""
	@echo "Run using:"
	@echo "make run"
	@echo ""

install: ./$(BIN_DIR)/$(BIN) win.mak Makefile
	@echo "Installing!!"
	@if [ ! -d $(CONFIG_PATH) ]; then \
		mkdir -p $(CONFIG_PATH); \
	else \
		echo "Proxy Config Directory already exists. Skipping..."; \
	fi
	@if [ ! -f $(CONFIG_PATH)/config ]; then \
		cp ./config $(CONFIG_PATH); \
	else \
		echo "Config already exists. Skipping..."; \
	fi
	@cp ./scripts/set.ps1 $(CONFIG_PATH)/set.ps1
	@cp ./scripts/unset.ps1 $(CONFIG_PATH)/unset.ps1
	@cp ./$(BIN_DIR)/$(BIN).exe $(CONFIG_PATH)
	@echo "Installation Done!"

-include $(DEPFILES)