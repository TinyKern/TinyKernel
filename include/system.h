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