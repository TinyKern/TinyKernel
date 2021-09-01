/**
 * @file elf.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.2
 * @date 2021-08-24
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <arch/i386/elf_core.h>

void get_symtab_and_strtab(Elf_Shdr **symtab, Elf_Shdr **strtab)
{
    Elf_Ehdr *h = (Elf_Ehdr*)(KERNEL_PA_TO_VA(KERNEL_PADDR));
    *symtab = NULL;
    *strtab = NULL;

    if (!KERNEL_SYMBOLS)
        return;

    VERIFY(h->e_shentsize == sizeof(Elf_Shdr));
    Elf_Shdr *sections = (Elf_Shdr*)((void *)h + h->e_shoff);

    for (u32 i = 0; i < h->e_shnum; i++)
    {
        Elf_Shdr *s = sections + i;

        if (s -> sh_type == SHT_SYMTAB)
        {
            ASSERT(!*symtab);
            *symtab = s;
        }
        else if (s->sh_type == SHT_STRTAB && i != h->e_shstrndx)
        {
            ASSERT(!*strtab);
            *strtab = s;
        }
    }

    VERIFY(*symtab != NULL);
    VERIFY(*strtab != NULL);
}

const char *find_sym_at_addr(uint64_t vaddr, long *offset, uint32_t *sym_size)
{
    Elf_Shdr *symtab;
    Elf_Shdr *strtab;

    if (!KERNEL_SYMBOLS)
        return NULL;

    get_symtab_and_strtab(&symtab, &strtab);

    Elf_Sym *syms = (Elf_Sym*) symtab->sh_addr;
    const uint64_t sym_count = symtab->sh_size / sizeof(Elf_Sym);

    for (u32 i = 0; i < sym_count; i++)
    {
        Elf_Sym *sym = syms + i;

        if (IN_RANGE(vaddr, sym->st_value, sym->st_value + sym->st_size))
        {
            if (offset)
                *offset = (long)(vaddr - sym->st_value);
            
            if (sym_size)
                *sym_size = (uint32_t)sym->st_size;
            
            return (char*)strtab->sh_addr + sym->st_name;
        }
    }

    return NULL;
}