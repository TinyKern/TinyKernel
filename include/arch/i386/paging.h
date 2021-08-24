#ifndef PAGING_INT_H
#define PAGING_INT_H

#include <types.h>

#define KERNEL_BASE_VA         0xC0000000

#define KERNEL_PA_TO_VA(pa) ((void *) ((uint64_t)(pa) + KERNEL_BASE_VA))
#define KERNEL_VA_TO_PA(va) ((uint64_t)(va) - KERNEL_BASE_VA)

#define PG_PRESENT_BIT_POS      0u
#define PG_RW_BIT_POS           1u
#define PG_US_BIT_POS           2u
#define PG_WT_BIT_POS           3u
#define PG_CD_BIT_POS           4u
#define PG_ACC_BIT_POS          5u
#define PG_DIRTY_BIT_POS        6u // page_t only
#define PG_PAGE_PAT_BIT_POS     7u // page_t only
#define PG_4MB_BIT_POS          7u // page_dir_entry_t only
#define PG_GLOBAL_BIT_POS       8u // page_t only
#define PG_CUSTOM_B0_POS        9u
#define PG_CUSTOM_B1_POS       10u
#define PG_CUSTOM_B2_POS       11u
#define PG_4MB_PAT_BIT_POS     12u // page_dir_entry_t only with psize = 1

#define PG_PRESENT_BIT  (1u << PG_PRESENT_BIT_POS)
#define PG_RW_BIT       (1u << PG_RW_BIT_POS)
#define PG_US_BIT       (1u << PG_US_BIT_POS)
#define PG_WT_BIT       (1u << PG_WT_BIT_POS)
#define PG_CD_BIT       (1u << PG_CD_BIT_POS)
#define PG_ACC_BIT      (1u << PG_ACC_BIT_POS)
#define PG_DIRTY_BIT    (1u << PG_DIRTY_BIT_POS)    // page_t only
#define PG_PAGE_PAT_BIT (1u << PG_PAGE_PAT_BIT_POS) // page_t only
#define PG_4MB_BIT      (1u << PG_4MB_BIT_POS)      // page_dir_entry_t only
#define PG_GLOBAL_BIT   (1u << PG_GLOBAL_BIT_POS)   // page_t only
#define PG_CUSTOM_B0    (1u << PG_CUSTOM_B0_POS)
#define PG_CUSTOM_B1    (1u << PG_CUSTOM_B1_POS)
#define PG_CUSTOM_B2    (1u << PG_CUSTOM_B2_POS)
#define PG_CUSTOM_BITS  (PG_CUSTOM_B0 | PG_CUSTOM_B1 | PG_CUSTOM_B2)
#define PG_4MB_PAT_BIT  (1u << PG_4MB_PAT_BIT_POS)

#define PAGE_FAULT_FL_PRESENT (1u << 0)
#define PAGE_FAULT_FL_RW      (1u << 1)
#define PAGE_FAULT_FL_US      (1u << 2)

#define PAGE_FAULT_FL_COW (PAGE_FAULT_FL_PRESENT | PAGE_FAULT_FL_RW)
#define BIG_PAGE_SHIFT                                            22
#define KERNEL_BASE_PD_IDX        (KERNEL_BASE_VA >> BIG_PAGE_SHIFT)

#define PAGE_SIZE           4096u
#define PAGE_SHIFT          12u
#define OFFSET_IN_PAGE_MASK (PAGE_SIZE - 1)

union x86_page
{
    struct
    {
        uint32_t present    : 1;
        uint32_t rw         : 1;
        uint32_t us         : 1;
        uint32_t wt         : 1;
        uint32_t cd         : 1;
        uint32_t accessed   : 1;
        uint32_t dirty      : 1;
        uint32_t pat        : 1;
        uint32_t global     : 1;
        uint32_t avail      : 3;
        uint32_t page_addr  : 20;
    };

    uint32_t raw;
};

struct x86_page_table
{
    union x86_page pages[1024];
};

union x86_page_dir_entry
{
    struct
    {
        uint32_t present    : 1;
        uint32_t rw         : 1;
        uint32_t us         : 1;
        uint32_t wt         : 1;
        uint32_t cd         : 1;
        uint32_t accessed   : 1;
        uint32_t zero       : 1;
        uint32_t psize      : 1;
        uint32_t ignored    : 1;
        uint32_t avail      : 3;
        uint32_t ptaddr     : 20;
    };

    struct
    {
        uint32_t present    : 1;
        uint32_t rw         : 1;
        uint32_t us         : 1;
        uint32_t wt         : 1;
        uint32_t cd         : 1;
        uint32_t accessed   : 1;
        uint32_t zero       : 1;
        uint32_t one        : 1;
        uint32_t ignored    : 1;
        uint32_t avail      : 3;
        uint32_t pat        : 1;
        uint32_t paddr_zero : 9;
        uint32_t paddr      : 10;
    } big_4mb_page;

    uint32_t raw;
};

struct x86_pdir
{
    union x86_page_dir_entry entries[1024];
};

STATIC_ASSERT(sizeof(struct x86_pdir) == 4096u);

typedef union   x86_page page_t;
typedef struct  x86_page_table page_table_t;
typedef union   x86_page_dir_entry page_dir_entry_t;
typedef struct  x86_pdir pdir_t;

int virtual_read(pdir_t *pdir, void *extern_va, void *dest, size_t len);
int virtual_write(pdir_t *pdir, void *extern_va, void *src, size_t len);

#endif // PAGING_INT_H