# User
ifeq ($(USER),root)
RUNNING_USER:=$(SUDO_USER)
else
RUNNING_USER:=$(USER)
endif

# Config Path
CONFIG_PATH:=/home/${RUNNING_USER}/.config/proxy

BIN_DIR:=bin
SRC_DIR:=src
OBJ_DIR:=obj
HEAD_DIR:=include
DEP_DIR:=$(OBJ_DIR)
INC_DIR=.

# Shell
ifeq ($(SH),zsh)
SHELL_CONFIG_FILE:=.zshrc
else
SHELL_CONFIG_FILE=.bashrc
endif

VARIANT?=release

# CC and C Flags
CFLAGS=-std=gnu11 -D SHELL_CONFIG_FILE=\"${SHELL_CONFIG_FILE}\" -D USER=\"${RUNNING_USER}\"

ifeq ($(VARIANT),debug)
CFLAGS+= -Og
else
CFLAGS+= -Ofast
endif
CFLAGS+= $(addprefix -I,$(INC_DIR))

ifeq ($(ARCH),x86_64)
CFLAGS+= -m64
else ifeq ($(ARCH),i386)
CFLAGS+= -m32
endif

$(info OS: $(OS), Arch: $(ARCH))

# Files
SRCFILES := $(shell find $(SRC_DIR) -type f -name "*.c")
OBJFILES := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCFILES))
DEPFILES := $(patsubst $(SRC_DIR)/%.c,$(DEP_DIR)/%.d,$(SRCFILES))
HEADERFILES:=$(shell find $(HEAD_DIR) -type f -name "*.h")

.PHONY: all clean run install

all: $(BIN_DIR)/$(BIN) Makefile

$(BIN_DIR)/$(BIN): $(OBJFILES) Makefile
	@echo "Building Final Binary!"
	@$(CC) $(CFLAGS) $(OBJFILES) -o $(BIN_DIR)/$(BIN)
	@echo "All Done!"
	@echo ""
	@echo ""
	@echo "Run using:"
	@echo "make run"
	@echo ""

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@
	@echo "Compiling $< file"

install: ./$(BIN_DIR)/$(BIN)
	@echo "Installing!!"
	@sudo cp ./$(BIN_DIR)/$(BIN) /usr/bin
	@if [ ! -d $(CONFIG_PATH) ]; then \
		sudo mkdir -p $(CONFIG_PATH); \
	else \
		echo "Config Directory Already Exists. Skipping..."; \
	fi
	@sudo cp ./scripts/set.sh $(CONFIG_PATH)
	@sudo chmod +x $(CONFIG_PATH)/set.sh
	@sudo chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_PATH)/set.sh
	@sudo cp ./scripts/unset.sh $(CONFIG_PATH)
	@sudo chmod +x $(CONFIG_PATH)/unset.sh
	@sudo chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_PATH)/unset.sh
	@sudo touch $(CONFIG_PATH)/proxy.sh
	@sudo chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_PATH)/proxy.sh
	@if [ ! -f "$(CONFIG_PATH)/config" ] || [ "$(VARIANT)" = "debug" ]; \
	then \
		cp config_unix $(CONFIG_PATH); \
		mv $(CONFIG_PATH)/config_unix $(CONFIG_PATH)/config; \
		sudo chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_PATH)/config; \
	else \
		echo "Skipping copying of sample config file"; \
	fi
	@sudo chown $(SUDO_USER):$(SUDO_USER) $(CONFIG_PATH)/config
	@if grep -Fxq "source ${CONFIG_PATH}/proxy.sh" /home/$(SUDO_USER)/$(SHELL_CONFIG_FILE); \
	then \
		echo "Source command already added!"; \
		echo "Continuing..."; \
	else \
		sudo echo "source ${CONFIG_PATH}/proxy.sh" >> /home/$(SUDO_USER)/$(SHELL_CONFIG_FILE); \
	fi
	@echo "Installation Completed!"

clean:
	@rm -rf $(OBJ_DIR)/** $(BIN_DIR)/**
	@echo "Cleaned up!"

run:
	@./$(BIN_DIR)/$(BIN)

-include $(DEPFILES)