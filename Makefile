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
AUTHOR 			:= Bobrossrtx

BINUTILS_VERSION:= 2.37
GCC_VERSION		:= 11.2.0

# Linkers & Compilers
CROSS_PREFIX 	:= $(HOME)/.local/bin/TinyKernel-Toolchain
ARCH			:= i386-elf

CC 				:= $(CROSS_PREFIX)/bin/$(ARCH)-gcc
CXX 			:= $(CROSS_PREFIX)/bin/$(ARCH)-g++
LD 				:= $(CROSS_PREFIX)/bin/$(ARCH)-ld
AS 				:= $(CROSS_PREFIX)/bin/$(ARCH)-as
NASM 			:= nasm

CORES 			:= $(shell nproc)

# Directories
BUILD_DIR 		?= build
SRC_DIRS 		?= src
INC_DIRS 		?= include
OBJ_DIR 		:= $(BUILD_DIR)/obj
ISO_DIR 		:= $(BUILD_DIR)/iso
BOOT_DIR 		:= $(BUILD_DIR)/boot
GRUB_DIR 		:= $(BOOT_DIR)/grub

PROJ_DIRS 		:= $(SRC_DIRS) $(INC_DIRS) $(OBJ_DIR) $(ISO_DIR) $(BOOT_DIR) $(GRUB_DIR)

# Files
AUXS		 	:= Makefile README.md LICENSE CODE_OF_CONDUCT.md
SRCS 			:= $(shell find $(PROJ_DIRS) -name *.cpp -or -name *.c -or -name *.s -or -name *.asm)
HDRS 			:= $(shell find $(PROJ_DIRS) -name *.h -or -name *.hh)
OBJS 			:= $(SRCS:%=$(OBJ_DIR)/%.o)
DEPS			:= $(SRCS:%=$(OBJ_DIR)/%.d)
TARGET 			?= $(BOOT_DIR)/TinyKernel.elf
ISO 			?= TinyKernel_$(AUTHOR)-$(KERNEL_VERSION).iso

ALLFILES 		:= $(SRCS) $(HDRS) $(OBJS) $(AUXS)

# Flags
LOWER_WARNINGS	:= -Wall -Wextra

## Warning flags for later use when refactoring & cleaning
WARNING_FLAGS	:= $(LOWER_WARNINGS) -pedantic -Wshadow -Wpointer-arith -Wcast-align \
					-Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
					-Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
					-Wconversion -Wstrict-prototypes

INC_FLAGS 		:= $(addprefix -I ,$(INC_DIRS))
CFLAGS 			?= $(INC_FLAGS) -MMD -MP -std=gnu99 -ffreestanding -O2 -m32 -fno-stack-protector $(LOWER_WARNINGS) -g
LDFLAGS 		?= -m elf_i386 -T config/linker.ld
ASFLAGS 		?= --32
NASMFLAGS 		?= -f elf32
QEMUFLAGS 		?= cdrom $(ISO_DIR)/$(ISO)

# Backups
CURR_DIR		:= $(shell basename `pwd`)
TODAY 			:= $(shell date +%Y-%m-%d)
BACKUP_DIR		:= Backups/$(TODAY)

# Package managers
pacman 			:= $(shell command -v pacman 2>/dev/null)
yum 			:= $(shell command -v yum 2>/dev/null)
apt 			:= $(shell command -v apt 2>/dev/null)

# Grub	
grub 			:= $(shell command -v grub-file 2>/dev/null)

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
	@cp config/grub.cfg $(GRUB_DIR)/

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

run-debug: 
	qemu-system-x86_64 -device sb16 -kernel $(TARGET) -S -s

run-iso: 
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO)

run-iso-debug: 
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO)  -S -s

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

.PHONY: clean todos
todolist: todos
todos:
	@echo "============="
	@echo "= TODO List ="
	@echo "============="
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -e TODO -e FIXME $$file; done; true

backup: clean
ifndef /usr/bin/7z
	$(error 7Zip is not installed, please install 7zip)
endif
	@echo "===================="
	@echo "= Backing up files ="
	@echo "===================="
	@tar cf - ../$(CURR_DIR) | 7za a -si ../$(BACKUP_DIR)/$(CURR_DIR).$(TODAY)_`date +%H%M`.tar.7z

MKDIR_P 	?= mkdir -p
