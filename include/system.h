#ifndef __SYSTEM_H__
#define __SYSTEM_H__

/* Allignment macros */
#define ALIGN(x,a)              __ALIGN_MASK(x,(typeof(x))(a)-1)
#define __ALIGN_MASK(x,mask)    (((x)+(mask))&~(mask))

/* Load address (0xC0000000) - What low memory address such as 0xb800 you used to access, shoudl be LOAD_MEMORY_ADDRESS + 0xb800 */
#define LOAD_MEMORY_ADDRESS      0x00000000

/* Sizes */
#define KB(x)                    ((x) * 1024)
#define MB(x)                    ((x) * 1024 * 1024)
#define GB(x)                    ((x) * 1024 * 1024 * 1024)

/* CPU Instructions */
#define sti()           __asm__ ("sti"::)
#define cli()           __asm__ ("cli"::)
#define nop()           __asm__ ("nop"::)
#define hlt()           __asm__ ("hlt"::)
#define ret()           __asm__ ("ret"::)
#define iret()          __asm__ ("iret"::)
#define retf()          __asm__ ("retf"::)
#define clwb()          __asm__ ("clwb"::)
#define pause()         __asm__ ("pause"::)
#define rdtsc()         __asm__ ("rdtsc"::)
#define pause()         __asm__ ("pause"::)
#define rdtsc()         __asm__ ("rdtsc"::)
#define cpuid()         __asm__ ("cpuid"::)
#define rdmsr()         __asm__ ("rdmsr"::)
#define wrmsr()         __asm__ ("wrmsr"::)
#define rdtscp()        __asm__ ("rdtscp"::)
#define lfence()        __asm__ ("lfence"::)
#define mfence()        __asm__ ("mfence"::)
#define sfence()        __asm__ ("sfence"::)
#define clflush()       __asm__ ("clflush"::)
#define xorl(a,b)       __asm__ ("xorl %0,%1"::"r"(a),"r"(b):"cc")
#define xorl_r(a,b,c)   __asm__ ("xorl %0,%1":"=r"(a):"0"(b),"1"(c):"cc")
#define xorl_m(a,b,c)   __asm__ ("xorl %0,%1":"=r"(a):"0"(b),"1"(c):"cc")

#endif /* __SYSTEM_H__ */