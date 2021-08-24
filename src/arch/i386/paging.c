#include <arch/i386/paging.h>
#include <kernel/errno.h>
#include <sys/string.h>
#include <config.h>
#include <stdint.h>

int get_mapping2(pdir_t *pdir, void *vaddrp, uint64_t *pa_ref)
{
    page_table_t *pt;
    const uint64_t vaddr = (uint64_t)vaddrp;
    const uint32_t pt_index = (vaddr >> PAGE_SHIFT) & 0x3ff;
    const uint32_t pd_index = (vaddr >> BIG_PAGE_SHIFT) & 0x3ff;
    page_dir_entry_t e;
    page_t p;

    // Get page dir's entry for this vaddr
    e.raw = pdir->entries[pd_index].raw;

    if (!e.present)
        return -EFAULT;

    if (!e.psize)
    {
        // ASSERT(e.ptaddr != 0);

        // get the page table
        pt = KERNEL_PA_TO_VA(e.ptaddr << PAGE_SHIFT);

        p.raw = pt->pages[pt_index].raw;

        if (!p.present)
            return -EFAULT;
        
        *pa_ref = ((uint64_t) p.page_addr << PAGE_SHIFT) |
                (vaddr & OFFSET_IN_PAGE_MASK);
    }
    else
        *pa_ref = ((uint64_t) e.big_4mb_page.paddr << BIG_PAGE_SHIFT) |
                (vaddr & (4 * MB - 1));
    
    return 0;
}

static int virtual_read_unsafe(pdir_t *pdir, void *extern_va, void *dest, size_t len)
{
    uint64_t pgoff, pa;
    size_t tot, to_read;
    void *va;

    // ASSERT(len <= INT32_MAX);

    for (tot = 0; tot < len; extern_va += to_read, tot += to_read)
    {
        if (get_mapping2(pdir, extern_va, &pa) < 0)
            return -EFAULT;

        pgoff   = ((uint64_t) extern_va) & OFFSET_IN_PAGE_MASK;
        to_read = MIN(PAGE_SIZE - pgoff, len - tot);

        va = KERNEL_PA_TO_VA(pa);
        memcpy(dest + tot, va, to_read);
    }

    return (int)tot;
}

static int virtual_write_unsafe(pdir_t *pdir, void *extern_va, void *src, size_t len)
{
    uint64_t pgoff, pa;
    size_t tot, to_write;
    void *va;

    // ASSERT(len <= INT32_MAX);

    for (tot = 0; tot < len; extern_va += to_write, tot += to_write)
    {
        if (get_mapping2(pdir, extern_va, &pa) < 0)
            return -EFAULT;
        
        pgoff       = ((uint64_t) extern_va) & OFFSET_IN_PAGE_MASK;
        to_write    = MIN(PAGE_SIZE - pgoff, len - tot);

        va = KERNEL_PA_TO_VA(pa);
        memcpy(va, src + tot, to_write);
    }

    return (int)tot;
}


int virtual_read(pdir_t *pdir, void *extern_va, void *dest, size_t len)
{
    int rc;
    // disable_preemtion();
    {
        rc = virtual_read_unsafe(pdir, extern_va, dest, len);
    }
    // enable_preemtion();
    return rc;
}

int virtual_write(pdir_t *pdir, void *extern_va, void *src, size_t len)
{
    int rc;
    // disable_preemtion();
    {
        rc = virtual_write_unsafe(pdir, extern_va, src, len);
    }
    // enable_preemtion();
    return rc;
}
