KERNEL_VERSION 	:= 1.3.6
AUTHOR 			:= Bobrossrtx

CONFIG_ARCH		:= i386
BUILD_GITREF	:=	$(shell git rev-parse --abbrev-ref HEAD || echo unknown)@$(shell git rev-parse --short HEAD || echo unknown)
BUILD_UNAME 	:=	$(shell uname -s -o -m -r)
BUILD_DATE		:=	$(shell date "+%Y-%m-%d %H:%M:%S")
BUILD_VERSION	:=	$(KERNEL_VERSION)

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

PROJ_DIRS 		:= $(SRC_DIRS) $(INC_DIRS) $(OBJ_DIR)

SERIAL_LOG_FILE := $(BUILD_DIR)/serial.log

ifneq (,$(findstring xterm,${TERM}))
	BLACK		:= $(shell tput -Txterm setaf 0)
	RED			:= $(shell tput -Txterm setaf 1)
	GREEN		:= $(shell tput -Txterm setaf 2)
	YELLOW		:= $(shell tput -Txterm setaf 3)
	LIGHT_PURPLE:= $(shell tput -Txterm setaf 4)
	PURPLE		:= $(shell tput -Txterm setaf 5)
	BLUE		:= $(shell tput -Txterm setaf 6)
	WHITE		:= $(shell tput -Txterm setaf 7)
	RESET		:= $(shell tput -Txterm sgr0)
else
	BLACK		:= ""
	RED			:= ""
	GREEN		:= ""
	YELLOW		:= ""
	LIGHT_PURPLE:= ""
	PURPLE		:= ""
	BLUE		:= ""
	WHITE		:= ""
	RESET		:= ""
endif
