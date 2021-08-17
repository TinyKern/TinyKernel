/**
 * @file kernel.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.4
 * @date 2021-07-06
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#ifndef KERNEL_H
#define KERNEL_H

#include <config.h>
#include <types.h>
#include <sys/char.h>
#include <drivers/keyboard/keyboard.h> 

#define KERNEL_MAGIC 0x1BADB002

struct multiboot_info {
    uint32_t flags;
    uint32_t mem_lower;
    uint32_t mem_upper;
    uint32_t boot_device;
    uint32_t config_table;
    uint32_t boot_loader_name;
    uint32_t buffer_width;
    uint32_t buffer_height;
};

struct kernel_args {
    struct multiboot_info* mbi;
};

#endif
