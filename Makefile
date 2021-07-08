# * @file Makefile
# * @author Owen Boreham (owenkadeboreham@gmail.com)
# * @version 0.1.5
# * @date 2021-07-08
# * 
# * @copyright Copyright (c) 2021 TinyKernel
# * This file is part of TinyKernel which is released
# * under Apache License 2.0.  See file LICENSE or go
# * to https://www.apache.org/licenses/LICENSE-2.0 for
# * full license details.

CC = gcc
LD = ld
AS = as
BUILD_DIR ?= build
BOOT_DIR := $(BUILD_DIR)/boot
OBJ_DIR := $(BUILD_DIR)/obj
SRC_DIRS ?= src
INC_DIRS := include

TARGET_BIN ?= $(BOOT_DIR)/TinyKernel.bin
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

INC_FLAGS := $(addprefix -I ,$(INC_DIRS))
CFLAGS ?= $(INC_FLAGS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS ?= -m elf_i386 -T linker.ld
ASFLAGS ?= --32

$(TARGET_BIN): clean $(OBJS)
	@$(MKDIR_P) $(dir $@)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET_BIN)

$(OBJ_DIR)/%.s.o: %.s
	@$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	@$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p