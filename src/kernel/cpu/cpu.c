#include <kernel/cpu/cpu.h>
#include <kernel/stdio.h>

void cpuid(uint32 value, uint32 *eax, uint32 *ebx, uint32 *ecx, uint32 *edx)
{
	uint32 eaxres, ebxres, ecxres, edxres;
	asm("xorl\t%eax, %eax");
	asm("xorl\t%ebx, %ebx");
	asm("xorl\t%ecx, %ecx");
	asm("xorl\t%edx, %edx");
	asm("movl\t%0, %%eax"
			: "=m"(value));
	asm("cpuid");
	asm("movl\t%%eax, %0"
			: "=m"(eaxres));
	asm("movl\t%%ebx, %0"
			: "=m"(ebxres));
	asm("movl\t%%ecx, %0"
			: "=m"(ecxres));
	asm("movl\t%%edx, %0"
			: "=m"(edxres));
	*eax = eaxres;
	*ebx = ebxres;
	*ecx = ecxres;
	*edx = edxres;
}

void print_eax(uint32 eax)
{
	uint32 step_id, model, family_id, proc_type, ext_mod_id, ext_family_id;
	step_id = model = family_id = proc_type = ext_mod_id = ext_family_id = eax;

	step_id &= (2 << 3) - 1;  // bits 0-3
	model >>= 4;						  // bits 4-7
	model &= (2 << 3) - 1;
	family_id >>= 8;          // bits 8-11
	family_id &= (2 << 3) - 1;
	proc_type >>= 12;         // bits 12-13
	proc_type &= (2 << 1) - 1;
	ext_mod_id >>= 16;        // bits 16-19
	ext_mod_id &= (2 << 3) - 1;
	ext_family_id >>= 20;     // bits 20-27
	ext_family_id &= (2 << 7) - 1;

	kprintf("    EAX ------------------------|\n");
	kprintf("        Stepping ID       : %d\n", step_id);
	kprintf("        Model             : %d\n", model);
	kprintf("        Family ID         : %d\n", family_id);
	kprintf("        ProcessorType     : %d\n", proc_type);
	kprintf("        Extended Model ID : %d\n", ext_mod_id);
	kprintf("        Extended Family   : %d\n", ext_family_id);
}

void print_ebx(uint32 ebx)
{
	uint32 brand_index, cache_line_size, max_addr_id, init_apic_id;
	brand_index = cache_line_size = max_addr_id = init_apic_id = 0;
	char* bytes = (char *)&ebx;

	brand_index = bytes[0];			// bits 0-7
	cache_line_size = bytes[1]; 	// bits 8-15
	max_addr_id = bytes[2];			// bits 16-23
	init_apic_id = bytes[3];		// bits 24-31

	kprintf("    EBX ------------------------|\n");
	kprintf("        Brand Index       : %d\n", brand_index);
	kprintf("        Cache Line Size   : %d\n", cache_line_size);
	kprintf("        Max Address Id    : %d\n", max_addr_id);
	kprintf("        APIC ID           : %d\n", init_apic_id);
}

void print_edx(uint32 edx)
{
    uint32 apic_id, max_log_proc, max_cores, max_threads;
    apic_id = max_log_proc = max_cores = max_threads = 0;
    char* bytes = (char *)&edx;
        
    apic_id = bytes[0];				// bits 0-7
    max_log_proc = bytes[1];		// bits 8-15
    max_cores = bytes[2];			// bits 16-23
    max_threads = bytes[3];		    // bits 24-31

	kprintf("    EDX ------------------------|\n");
	kprintf("        APIC ID           : %d\n", apic_id);
    kprintf("        Max Logical Proc  : %d\n", max_log_proc);
    kprintf("        Max Cores         : %d\n", max_cores);
    kprintf("        Max Threads       : %d\n", max_threads);
}

void cpuid_test()
{
	uint32 eax, ebx, ecx, edx;

	kprintf("CPUID :\n");

	cpuid(0, &eax, &ebx, &ecx, &edx);

	print_eax(eax);
	print_ebx(ebx);
	print_edx(edx);
}