/**
 * @file elf_core.h
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.1
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#pragma once

#include <config.h>

#include "elf.h"
#include "paging.h"

#if defined(USE_ELF32) && defined(USE_ELF64)
# error Invalid configuration: USE_ELF32 and USE_ELF64 are both defined.
#endif

#if defined(USE_ELF32) || !defined(USE_ELF64)

    typedef Elf32_Addr Elf_Addr;
    typedef Elf32_Ehdr Elf_Ehdr;
    typedef Elf32_Phdr Elf_Phdr;
    typedef Elf32_Shdr Elf_Shdr;
    typedef Elf32_Sym Elf_Sym;

#elif !defined(USE_ELF32) || defined(USE_ELF64)

    typedef Elf64_Addr Elf_Addr;
    typedef Elf64_Ehdr Elf_Ehdr;
    typedef Elf64_Phdr Elf_Phdr;
    typedef Elf64_Shdr Elf_Shdr;
    typedef Elf64_Sym Elf_Sym;

#else

# error Unknown architecture.

#endif // USE_ELF32 || USE_ELF64

const char *find_sym_at_addr(uint64_t vaddr, long *offset, uint32_t *sym_size);