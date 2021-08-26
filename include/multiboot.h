#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT_SEARCH                32768
#define MULTIBOOT_HEADER_ALIGN          8

#define MULTIBOOT_MAGIC                 0xe85250d6
#define MULTIBOOT_BOOTLOADER_MAGIC      0x36D76289
#define MULTIBOOT_BOOTLOADER_MAGIC_S    0x2BADB002

#define MULTIBOOT_MOD_ALIGN             0x00001000
#define MULTIBOOT_INFO_ALIGN            0x00000008

#define MULTIBOOT_TAG_ALIGN                     8
#define MULTIBOOT_TAG_TYPE_END                  0
#define MULTIBOOT_TAG_TYPE_CMDLINE              1
#define MULTIBOOT_TAG_TYPE_BOOT_LOADER_NAME     2
#define MULTIBOOT_TAG_TYPE_MODULE               3
#define MULTIBOOT_TAG_TYPE_BASIC_MEMINFO        4
#define MULTIBOOT_TAG_TYPE_BOOTDEV              5
#define MULTIBOOT_TAG_TYPE_MMAP                 6
#define MULTIBOOT_TAG_TYPE_VBE                  7
#define MULTIBOOT_TAG_TYPE_FRAMEBUFFER          8
#define MULTIBOOT_TAG_TYPE_ELF_SECTIONS         9
#define MULTIBOOT_TAG_TYPE_APM                  10

#define MULTIBOOT_HEADER_TAG_END                    0
#define MULTIBOOT_HEADER_TAG_INFORMATION_REQUEST    1
#define MULTIBOOT_HEADER_TAG_ADDRESS                2
#define MULTIBOOT_HEADER_TAG_ENTRY_ADDRESS          3
#define MULTIBOOT_HEADER_TAG_CONSOLE_FLAGS          4
#define MULTIBOOT_HEADER_TAG_FRAMEBUFFER            5
#define MULTIBOOT_HEADER_TAG_MODULE_ALIGN           6
#define MULTIBOOT_HEADER_TAG_OPTIONAL               1

#define MULTIBOOT_ARCHITECTURE_I386                 0
#define MULTIBOOT_ARCHITECTURE_MIPS32               4

#define MULTIBOOT_CONSOLE_FLAGS_REQUIRED            1
#define MULTIBOOT_CONSOLE_FLAGS_EGA_TEXT_SUPPORTED  2

#ifndef ASM_FILE

typedef unsigned char   multiboot_uint8_t;
typedef unsigned short  multiboot_uint16_t;
typedef unsigned int    multiboot_uint32_t;
typedef unsigned long   multiboot_uint64_t;

struct multiboot_header
{
    // Must be MULTIBOOT_MAGIC
    multiboot_uint32_t  magic;

    // ISA
    multiboot_uint8_t   architecture;

    // Total size of the header
    multiboot_uint32_t  header_length;

    // The above fields + current must equal 0 mod 2^32
    multiboot_uint32_t  checksum;
};

struct multiboot_header_tag
{
    multiboot_uint16_t type;
    multiboot_uint16_t flags;
    multiboot_uint32_t size;
};

struct multiboot_header_tag_info_request
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  requests[0];
};

struct multiboot_header_tag_address
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  header_addr;
    multiboot_uint32_t  load_addr;
    multiboot_uint32_t  load_end_addr;
    multiboot_uint32_t  bss_end_addr;
};

struct multiboot_header_tag_entry_address
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  entry_addr;
};

struct multiboot_header_tag_console_flags
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  console_flags;
};

struct multiboot_header_tag_framebuffer
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  width;
    multiboot_uint32_t  height;
    multiboot_uint32_t  depth;
};

struct multiboot_header_tag_module_align
{
    multiboot_uint16_t  type;
    multiboot_uint16_t  flags;
    multiboot_uint32_t  size;
    multiboot_uint32_t  width;
    multiboot_uint32_t  height;
    multiboot_uint32_t  depth;
};

struct multiboot_color
{
    multiboot_uint8_t   red;
    multiboot_uint8_t   green;
    multiboot_uint8_t   blue;
};

struct multiboot_mmap_entry
{
    multiboot_uint64_t  addr;
    multiboot_uint64_t  length;
#define MULTIBOOT_MEMORY_AVAILABLE      1
#define MULTIBOOT_MEMORY_RESERVED       2
#define MULTIBOOT_MEMORY_ACPI_RECLAIM   3
#define MULTIBOOT_MEMORY_NVS            4
    multiboot_uint32_t  type;
    multiboot_uint32_t  zero;
} __attribute__((packed));
typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_tag
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
};

struct multiboot_tag_string
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    char                string[0];
};

struct multiboot_tag_module
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint32_t  mod_start;
    multiboot_uint32_t  mod_end;
    char                cmdline[0];
};

struct multiboot_tag_basic_meminfo
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint32_t  mem_lower;
    multiboot_uint32_t  mem_upper;
};

struct multiboot_tag_bootdev
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint32_t  biosdev;
    multiboot_uint32_t  slice;
    multiboot_uint32_t  part;
};

struct multiboot_vbe_info_block
{
    multiboot_uint8_t   external_specification[512];
};

struct multiboot_vbe_mode_info_block
{
    multiboot_uint8_t   external_specification[256];
};

struct multiboot_tag_vbe
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint16_t  vbe_mode;
    multiboot_uint16_t  vbe_interface_seg;
    multiboot_uint16_t  vbe_interface_off;
    multiboot_uint16_t  vbe_interface_len;

    struct multiboot_vbe_info_block         vbe_control_info;
    struct multiboot_vbe_mode_info_block    vbe_mode_info;
};

struct multiboot_tag_framebuffer_common
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;

    multiboot_uint64_t  framebuffer_addr;
    multiboot_uint32_t  framebuffer_pitch;
    multiboot_uint32_t  framebuffer_width;
    multiboot_uint32_t  framebuffer_height;
    multiboot_uint8_t   framebuffer_bpp;
#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED      0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB          1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
    multiboot_uint8_t   framebuffer_type;
    multiboot_uint16_t  reserved;
};

struct multiboot_tag_framebuffer
{
    struct multiboot_tag_framebuffer_common common;

    union
    {
        struct
        {
            multiboot_uint16_t      framebuffer_pallete_num_colors;
            struct multiboot_color  framebuffer_pallete[0];
        };
        struct
        {
            multiboot_uint8_t       framebuffer_red_field_position;
            multiboot_uint8_t       framebuffer_red_mask_size;
            multiboot_uint8_t       framebuffer_green_field_position;
            multiboot_uint8_t       framebuffer_green_mask_size;
            multiboot_uint8_t       framebuffer_blue_field_position;
            multiboot_uint8_t       framebuffer_blue_mask_size;
        };
    };
};

struct multiboot_tag_elf_sections
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint32_t  num;
    multiboot_uint32_t  entsize;
    multiboot_uint32_t  shndx;
    char                sections[0];
};

struct multiboot_tag_apm
{
    multiboot_uint32_t  type;
    multiboot_uint32_t  size;
    multiboot_uint16_t  version;
    multiboot_uint16_t  cseg;
    multiboot_uint32_t  offset;
    multiboot_uint16_t  cseg_16;
    multiboot_uint16_t  dseg;
    multiboot_uint16_t  flags;
    multiboot_uint16_t  cseg_len;
    multiboot_uint16_t  cseg_16_len;
    multiboot_uint16_t  dseg_len;
};

struct multiboot_aout_symbol_table
{
    multiboot_uint32_t  tabsize;
    multiboot_uint32_t  strsize;
    multiboot_uint32_t  addr;
    multiboot_uint32_t  reserved;
};
typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

// The section header table for ELF
struct multiboot_elf_section_header_table
{
    multiboot_uint32_t  num;
    multiboot_uint32_t  size;
    multiboot_uint32_t  addr;
    multiboot_uint32_t  shndx;
};
typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info
{
    // Multiboot info version number
    multiboot_uint32_t  flags;

    // Available memory from BIOS
    multiboot_uint32_t  mem_lower;
    multiboot_uint32_t  mem_upper;

    // Root partition
    multiboot_uint32_t  boot_device;

    // Kernel command line
    multiboot_uint32_t  cmdline;

    // Module List
    multiboot_uint32_t  mods_count;
    multiboot_uint32_t  mods_addr;

    union
    {
        multiboot_aout_symbol_table_t           aout_sym;
        multiboot_elf_section_header_table_t    elf_sec;
    } u;

    // Memory Mapping buffer
    multiboot_uint32_t  mmap_length;
    multiboot_uint32_t  mmap_addr;

    // Drive info buffer
    multiboot_uint32_t  drives_length;
    multiboot_uint32_t  drives_addr;

    // ROM configuration table
    multiboot_uint32_t  config_table;

    // Boot loader name
    multiboot_uint8_t   boot_loader_name[6];

    // APM table
    multiboot_uint32_t  apm_table;
    
    // Video
    multiboot_uint32_t  vbe_control_info;
    multiboot_uint32_t  vbe_mode_info;
    multiboot_uint16_t  vbe_mode;
    multiboot_uint16_t  vbe_interface_seg;
    multiboot_uint16_t  vbe_interface_off;
    multiboot_uint16_t  vbe_interface_len;

    // Framebuffer
    multiboot_uint64_t  framebuffer_addr;
    multiboot_uint32_t  framebuffer_pitch;
    multiboot_uint32_t  framebuffer_width;
    multiboot_uint32_t  framebuffer_height;
    multiboot_uint8_t   framebuffer_bpp;
#ifdef MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED || MULTIBOOT_FRAMEBUFFER_TYPE_RGB || MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT
#undef MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED
#undef MULTIBOOT_FRAMEBUFFER_TYPE_RGB
#undef MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT

#define MULTIBOOT_FRAMEBUFFER_TYPE_INDEXED      0
#define MULTIBOOT_FRAMEBUFFER_TYPE_RGB          1
#define MULTIBOOT_FRAMEBUFFER_TYPE_EGA_TEXT     2
#endif
    multiboot_uint8_t   framebuffer_type;
    union
    {
        struct
        {
            multiboot_uint16_t      framebuffer_pallete_num_colors;
            struct multiboot_color  framebuffer_pallete[0];
        };
        struct
        {
            multiboot_uint8_t       framebuffer_red_field_position;
            multiboot_uint8_t       framebuffer_red_mask_size;
            multiboot_uint8_t       framebuffer_green_field_position;
            multiboot_uint8_t       framebuffer_green_mask_size;
            multiboot_uint8_t       framebuffer_blue_field_position;
            multiboot_uint8_t       framebuffer_blue_mask_size;
        };
    };
};
typedef struct multiboot_info multiboot_info_t;

#endif // ASM_FILE

#endif // MULTIBOOT_H