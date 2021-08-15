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

KERNEL_VERSION 	:= 1.3.6
AUTHOR 		:= Bobrossrtx

BINUTILS_VERSION:= 2.37
GCC_VERSION	:= 11.2.0

# Linkers & Compilers
CROSS_PREFIX 	:= $(HOME)/.local/bin/TinyKernel-Toolchain
TARGET		:= i386-elf

CC 		:= $(CROSS_PREFIX)/bin/$(TARGET)-gcc
CXX 		:= $(CROSS_PREFIX)/bin/$(TARGET)-g++
LD 		:= $(CROSS_PREFIX)/bin/$(TARGET)-ld
AS 		:= $(CROSS_PREFIX)/bin/$(TARGET)-as
NASM 		:= nasm

CORES 		:= $(shell nproc)

# Directories
BUILD_DIR 	?= build
SRC_DIRS 	?= src
INC_DIRS 	?= include
OBJ_DIR 	:= $(BUILD_DIR)/obj
ISO_DIR 	:= $(BUILD_DIR)/iso
BOOT_DIR 	:= $(BUILD_DIR)/boot
GRUB_DIR 	:= $(BOOT_DIR)/grub

# Files
SRCS 		:= $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s -or -name *.asm)
OBJS 		:= $(SRCS:%=$(OBJ_DIR)/%.o)
TARGET 		?= $(BOOT_DIR)/TinyKernel.elf
ISO 		?= TinyKernel_$(AUTHOR)-$(KERNEL_VERSION).iso

# Flags
INC_FLAGS 	:= $(addprefix -I ,$(INC_DIRS))
CFLAGS 		?= $(INC_FLAGS) -std=gnu99 -ffreestanding -O2 -Wall -Wextra -m32 -fno-stack-protector
LDFLAGS 	?= -m elf_i386 -T linker.ld
ASFLAGS 	?= --32
NASMFLAGS 	?= -f elf32
QEMUFLAGS 	?= cdrom $(ISO_DIR)/$(ISO)

# Package managers
pacman 		:= $(shell command -v pacman 2>/dev/null)
yum 		:= $(shell command -v yum 2>/dev/null)
apt 		:= $(shell command -v apt 2>/dev/null)

# Grub
grub 		:= $(shell command -v grub-file 2>/dev/null)

.PHONY: clean iso run-iso
iso: build
	@echo "GRUB $^ -> $(ISO)"
	@grub-mkrescue -o $(ISO_DIR)/$(ISO) $(BUILD_DIR)

build: $(TARGET)

$(TARGET): clean $(OBJS)
	@$(MKDIR_P) $(dir $@)
	@echo "Linking -> $@"
	@$(LD) $(LDFLAGS) $(OBJS) -o $(TARGET)
ifndef grub
	@echo "Installing grub requirements"
ifdef apt
	@sudo apt-get install grub-common xorriso grub-pc-bin
endif #apt
ifdef pacman
	@sudo pacman -S grub
endif #pacman
endif #grub
	@grub-file --is-x86-multiboot $(TARGET)
	@$(MKDIR_P) $(GRUB_DIR) $(ISO_DIR)
	@cp grub.cfg $(GRUB_DIR)/

$(OBJ_DIR)/%.s.o: %.s
	@$(MKDIR_P) $(dir $@)
	@echo "AS $< -> $@"
	@$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.asm.o: %.asm
	@$(MKDIR_P) $(dir $@)
	@echo "NASM $< -> $@"
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo "CC $< -> $@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cxx.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	@echo "CXX $< -> $@"
	@$(CXX) $(CFLAGS) -c $< -o $@

run: 
	qemu-system-x86_64 -device sb16 -kernel $(TARGET)

run-iso: 
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO)

.PHONY: clean
clean:
	@$(RM) -r $(BUILD_DIR)

install-toolchain:
	@rm -rf $(CROSS_PREFIX)
	@echo "========================"
	@echo "= Installing toolchain ="
	@echo "========================"
	@echo
	git clone https://github.com/TinyKern/toolchain.git $(CROSS_PREFIX)
	@echo
	@echo "========================"
	@echo 
	@echo "Toolchain installed to $(CROSS_PREFIX)"
	@echo "run 'bash install.sh' in $(CROSS_PREFIX) to build the toolchain"

MKDIR_P 	?= mkdir -p
