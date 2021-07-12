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

KERNEL_VERSION := 0.1.3
AUTHOR := Bobrossrtx

# Linkers & Compilers
CC = gcc
CPP = g++
LD = ld
AS = as

# Directories
BUILD_DIR ?= build
BOOT_DIR := $(BUILD_DIR)/boot
GRUB_DIR := $(BOOT_DIR)/grub
OBJ_DIR := $(BUILD_DIR)/obj
ISO_DIR := $(BUILD_DIR)/iso
SRC_DIRS ?= src
INC_DIRS := include

# Files
ISO ?= TinyKernel_$(AUTHOR)-$(KERNEL_VERSION).iso
TARGET_BIN ?= $(BOOT_DIR)/TinyKernel.bin
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(OBJ_DIR)/%.o)

# Flags
INC_FLAGS := $(addprefix -I ,$(INC_DIRS))
CFLAGS ?= $(INC_FLAGS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32
LDFLAGS ?= -m elf_i386 -T linker.ld
ASFLAGS ?= --32
QEMUFLAGS ?= cdrom $(ISO_DIR)/$(ISO)

# Package managers
apt := $(shell command -v apt 2>/dev/null)
yum := $(shell command -v yum 2>/dev/null)
pacman := $(shell command -v pacman 2>/dev/null)

# Grub
grub := $(shell command -v grub-file 2>/dev/null)

$(TARGET_BIN): clean $(OBJS)
	@$(MKDIR_P) $(dir $@)
	$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET_BIN)
ifndef grub
ifdef apt
	@echo Installing grub requirements
	@sudo apt-get install grub-common xorriso
endif #apt
endif
	@$(MKDIR_P) $(GRUB_DIR) $(ISO_DIR)
	@cp grub.cfg $(GRUB_DIR)/
	@grub-mkrescue -o $(ISO) $(BUILD_DIR)
	@mv $(ISO) $(ISO_DIR)/

$(OBJ_DIR)/%.s.o: %.s
	@$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run:
	qemu-system-x86_64 -cdrom build/iso/TinyKernel_Bobrossrtx-0.1.3.iso

.PHONY: clean
clean:
	@$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p