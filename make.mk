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