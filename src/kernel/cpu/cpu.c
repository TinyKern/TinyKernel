/**
 * @file cpu.c
 * @author Owen Boreham (owenkadeboreham@gmail.com)
 * @version 0.1.3
 * @date 2021-07-29
 * 
 * @copyright Copyright (c) 2021 TinyKernel
 * This file is part of TinyKernel which is released
 * under Apache License 2.0.  See file LICENSE or go
 * to https://www.apache.org/licenses/LICENSE-2.0 for
 * full license details.
 */

#include <kernel/cpu/cpu.h>
#include <kernel/stdio.h>

void cpuid(uint32_t value, uint32_t *eax, uint32_t *ebx, uint32_t *ecx, uint32_t *edx)
{
	uint32_t eaxres, ebxres, ecxres, edxres;
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

static void print_eax(uint32_t eax)
{
	uint32_t step_id, model, family_id, proc_type, ext_mod_id, ext_family_id;
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

	kprintf("\tEAX ------------------------|\n");
	kprintf("\t\tStepping ID       : %d\n", step_id);
	kprintf("\t\tModel             : %d\n", model);
	kprintf("\t\tFamily ID         : %d\n", family_id);
	kprintf("\t\tProcessorType     : %d\n", proc_type);
	kprintf("\t\tExtended Model ID : %d\n", ext_mod_id);
	kprintf("\t\tExtended Family   : %d\n", ext_family_id);
}

static void print_ebx(uint32_t ebx)
{
	uint32_t brand_index, cache_line_size, max_addr_id, init_apic_id;
	brand_index = cache_line_size = max_addr_id = init_apic_id = 0;
	char* bytes = (char *)&ebx;

	brand_index = bytes[0];			// bits 0-7
	cache_line_size = bytes[1]; 	// bits 8-15
	max_addr_id = bytes[2];			// bits 16-23
	init_apic_id = bytes[3];		// bits 24-31

	kprintf("\tEBX ------------------------|\n");
	kprintf("\t\tBrand Index       : %d\n", brand_index);
	kprintf("\t\tCache Line Size   : %d\n", cache_line_size);
	kprintf("\t\tMax Address Id    : %d\n", max_addr_id);
	kprintf("\t\tAPIC ID           : %d\n", init_apic_id);
}

static void print_edx(uint32_t edx)
{
    uint32_t apic_id, max_log_proc, max_cores, max_threads;
    apic_id = max_log_proc = max_cores = max_threads = 0;
    char* bytes = (char *)&edx;
        
    apic_id = bytes[0];				// bits 0-7
    max_log_proc = bytes[1];		// bits 8-15
    max_cores = bytes[2];			// bits 16-23
    max_threads = bytes[3];		    // bits 24-31

	kprintf("\tEDX ------------------------|\n");
	kprintf("\t\tAPIC ID           : %d\n", apic_id);
    kprintf("\t\tMax Logical Proc  : %d\n", max_log_proc);
    kprintf("\t\tMax Cores         : %d\n", max_cores);
    kprintf("\t\tMax Threads       : %d\n", max_threads);
}

void cpuid_info()
{
	uint32_t eax, ebx, ecx, edx;

	kprintf("CPUID :\n");

	cpuid(0, &eax, &ebx, &ecx, &edx);

	print_eax(eax);
	print_ebx(ebx);
	print_edx(edx);
}