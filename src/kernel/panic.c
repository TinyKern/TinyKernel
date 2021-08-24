#include <arch/i386/elf_core.h>
#include <arch/i386/paging.h>
#include <kernel/panic.h>

volatile bool __in_panic;
volatile bool __in_double_fault;
volatile bool __in_kernel_shutdown;

// regs_t panic_state_regs;

// static size_t stackwalk32(void **frames, size_t count, void *ebp, pdir_t *pdir)
// {
//     bool curr_dir = false;
//     void *retAddr;
//     size_t i;

//     if (!ebp)
//         ebp = __builtin_frame_address(0);
    
//     if (!pdir)
//     {
//         pdir = get_curr_pdir();
//         curr_dir = true;
//     }

//     for (i = 0; i < count; i++)
//     {
//         if ((uint64_t)ebp < KERNEL_BASE_VA)
//             break;
        
//         if (curr_dir)
//         {
//             retAddr = *((void **)ebp + 1);
//             ebp     = *((void **)ebp);
//         }
//         else
//         {
//             if (virtual_read(pdir, (void **)ebp + 1, &retAddr, 4) < 0)
//                 break;

//             if (virtual_read(pdir, (void **)ebp, &ebp, 4) < 0)
//                 break;
//         }

//         if (!ebp || !retAddr)
//             break;

//         frames[i] = retAddr;
//     }

//     return i;
// }

// void dump_stacktrace(void *ebp, pdir_t *pdir)
// {
//     void *frames[32] = {0};
//     size_t c = stackwalk32(frames, ARRAY_SIZE(frames), ebp, pdir);

//     kprintf("Stacktrace (%d frames):\n", c);

//     for (size_t i = 0; i < c; i++)
//     {
//         long off = 0;
//         uint32_t sym_size;
//         uint64_t va = (uint64_t)frames[i];
//         const char *sym_name;

//         sym_name = find_sym_at_addr(va, &off, &sym_size);

//         if (sym_name && off == 0)
//         {
//             sym_name = find_sym_at_addr(va - 1, &off, &sym_size);
//             off++;
//         }

//         kprintf("[%x] %s + %d\n", TO_PTR(va), sym_name ? sym_name : "???", off);
//     }

//     kprintf("\n");
// }

void kpanic(int errcode, char* errmsg)
{
    clear_screen();
    vga_set_default_color(vga_create_color(BLACK, WHITE));
    kprintf("Kernel panic: %s - 0x%x\n", errmsg, errcode);

    for(;;) {}
}
