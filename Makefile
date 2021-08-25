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

include make.mk

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
	@echo "${YELLOW}GRUB $^ -> ${BLUE}$(ISO)${GREEN}"
	@grub-mkrescue -o $(ISO_DIR)/$(ISO) $(BUILD_DIR)
	@echo "${RESET}"

build: $(TARGET)

setup-dirs:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(ISO_DIR)
	@mkdir -p $(BOOT_DIR)
	@mkdir -p $(GRUB_DIR)

$(TARGET): clean setup-dirs $(OBJS)
	@$(MKDIR_P) $(dir $@)
	@echo "${YELLOW}Linking -> ${BLUE}$@${RESET}"
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
	@echo "${YELLOW}AS $< -> ${BLUE}$@${RESET}"
	@$(AS) $(ASFLAGS) $< -o $@

$(OBJ_DIR)/%.asm.o: %.asm
	@$(MKDIR_P) $(dir $@)
	@echo "${YELLOW}NASM $< -> ${BLUE}$@${RESET}"
	@$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.c.o: %.c
	@$(MKDIR_P) $(dir $@)
	@echo "${YELLOW}CC $< -> ${BLUE}$@${RESET}"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cxx.o: %.cpp
	@$(MKDIR_P) $(dir $@)
	@echo "${YELLOW}CXX $< -> ${BLUE}$@${RESET}"
	@$(CXX) $(CFLAGS) -c $< -o $@

run: 
	qemu-system-x86_64 -device sb16 -kernel $(TARGET)

run-serial:
	touch $(SERIAL_LOG_FILE)
	qemu-system-x86_64 -device sb16 -kernel $(TARGET) -append "root=/dev/sda console=ttyS0" -serial stdio

run-debug: 
	qemu-system-x86_64 -device sb16 -kernel $(TARGET) -S -s

run-debug-serial:
	touch $(SERIAL_LOG_FILE)
	qemu-system-x86_64 -device sb16 -kernel $(TARGET) -append "root=/dev/sda console=ttyS0" -serial stdio -S -s

run-iso: 
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO)

run-iso-serial:
	touch $(SERIAL_LOG_FILE)
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO) -serial stdio

run-iso-debug: 
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO)  -S -s

run-iso-debug-serial:
	touch $(SERIAL_LOG_FILE)	
	qemu-system-x86_64 -device sb16 -cdrom $(ISO_DIR)/$(ISO) -serial stdio -S -s

.PHONY: clean
clean:
	@$(RM) -r $(BUILD_DIR)

install-toolchain:
	@rm -rf $(CROSS_PREFIX)
	@echo "${PURPLE}========================${RESET}"
	@echo "${PURPLE}=${RESET} Installing toolchain ${PURPLE}=${RESET}"
	@echo "${PURPLE}========================${RESET}"
	@echo
	git clone https://github.com/TinyKern/toolchain.git $(CROSS_PREFIX)
	@echo
	@echo "${PURPLE}========================${RESET}"
	@echo 
	@echo "Toolchain installed to ${LIGHT_PURPLE}$(CROSS_PREFIX)${RESET}"
	@echo "run ${LIGHT_PURPLE}'bash install.sh'${RESET} in ${LIGHT_PURPLE}$(CROSS_PREFIX)${RESET} to build the toolchain"

.PHONY: clean todos todolist
todolist: todos
todos:
	@echo "============="
	@echo "= TODO List ="
	@echo "============="
	-@for file in $(ALLFILES:Makefile=); do fgrep -H -n -e TODO -e FIXME $$file; done; true

backup: clean
	@echo "===================="
	@echo "= Backing up files ="
	@echo "===================="
	@tar cf - ../$(CURR_DIR) | 7za a -si ../$(BACKUP_DIR)/$(CURR_DIR).$(TODAY)_`date +%H%M`.tar.7z

MKDIR_P 	?= mkdir -p
