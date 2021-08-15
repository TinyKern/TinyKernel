#include <kernel/cpu/gdt/gdt.h>

struct GDT gdt_entries[3];
struct GDT_PTR gdt_first;

extern void load_gdt(struct GDT*);

void gdt_init()
{
    // Set null segment
    gdt_entries[NULL_SEGMENT].segment_limit = 0;
    gdt_entries[NULL_SEGMENT].base_low      = 0;
    gdt_entries[NULL_SEGMENT].base_middle   = 0;
    gdt_entries[NULL_SEGMENT].access        = 0;
    gdt_entries[NULL_SEGMENT].granularity   = 0;
    gdt_entries[NULL_SEGMENT].base_high     = 0;

    // Set code segment
    gdt_entries[CODE_SEGMENT].segment_limit = 0xFFFF;
    gdt_entries[CODE_SEGMENT].base_low      = 0;
    gdt_entries[CODE_SEGMENT].base_middle   = 0;
    gdt_entries[CODE_SEGMENT].access        = 0x9A;
    gdt_entries[CODE_SEGMENT].granularity   = 0b11001111;
    gdt_entries[CODE_SEGMENT].base_high     = 0;

    // Set data segment
    gdt_entries[DATA_SEGMENT].segment_limit = 0xFFFF;
    gdt_entries[DATA_SEGMENT].base_low      = 0;
    gdt_entries[DATA_SEGMENT].base_middle   = 0;
    gdt_entries[DATA_SEGMENT].access        = 0x92;
    gdt_entries[DATA_SEGMENT].granularity   = 0b11001111;
    gdt_entries[DATA_SEGMENT].base_high     = 0;

    gdt_first.limit_size = sizeof(gdt_entries) - 1;
    gdt_first.base_address = (struct GDT*)&gdt_entries;

    load_gdt((struct GDT*)&gdt_first);
}