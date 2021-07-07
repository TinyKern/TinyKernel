# TinyKernel - 0.1.3
Tiny Kernel is a work in progress Operating System kernel.

By the end of the project, I hope to have a fully functional and working Kernel. Since System development is my prefered type of development, 
I thought it was time to finally create a project from the ground up, with its own x86 architecture and its own operating system to end up using
the kernel.

## Setup
[Disclaimer] - TinyKernel currently only builds on Linux distributions.

To setup TinyKernel, you can either clone the project or you can even install the iso from the [releases page](https://github.com/bobrossrtx/TinyKernel/releases).
If you install the iso disk file directly, you can skip to [#ISO](https://github.com/bobrossrtx/TinyKernel/new/master?readme=1#iso).
At the moment, TinyKernel only runs using qemu, so you are going to have to install qemu, but don't worry, it isn't hard.

### Cloned
#### Debian/Ubuntu
---
1st, You are going to want to clone the project, you can do that by using the git command: 
- `git clone https://github.com/bobrossrtx/TinyKernel/new/master?readme=1#iso`

After, you can either build manually or you can use the install script `install-debian.sh`.
The install script installs all of the necessery requirements including qemu, then compiles and builds the
kernel automatically. Else, if you want to build it manually, here are the commands in correct order:
- `version=0.1.3`
- `iso_name="TinyKernel_Bobrossrtx-${version}.iso"`
- `apt-get -y --no-install-recommends install binutils gcc` (no binutils & gcc)
- `apt-get -y --no-install-recommends install qemu-system-x86 grub-common xorriso`
- `include_dir="include"`
- `kernel_dir="kernel"`
- `build_dir="build"`
- `mkdir $build_dir`
- `mkdir -p $boot_dir $grub_dir $obj_dir $iso_dir`
- `as --32 ./boot.s -o ${obj_dir}/boot.o` Assemble the boot assembly file
- `gcc -m32 -c ${kernel_dir}/kernel.c -o ${obj_dir}/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I $include_dir`
- `ld -m elf_i386 -T linker.ld ${obj_dir}/kernel.o ${obj_dir}/boot.o -o ${boot_dir}/TinyKernel.bin`
- `grub-file --is-x86-multiboot ${boot_dir}/TinyKernel.bin` Check if TinyKernel.bin is x86 multiboot file
- `cp grub.cfg ${grub_dir}/grub.cfg` Copy Grub config to build/boot/grub/
- `grub-mkrescue -o ${iso_name} ${build_dir}` Generate ISO disk file
- `mv ${iso_name} ${iso_dir}/${iso_name}` Move ISO disk file to build/iso/

After building, you can run the kernel. The command to do so id:
- `qemu-system-x86_64 -cdrom ${iso_dir}/${iso_name}`

or

- `qemu-system-x86_64 -cdrom path/to/iso` default path is "TinyKernel/build/iso/TinyKernel.iso"

### ISO
#### Debian/Ubuntu
---
**Install Qemu:**
- `sudo apt-get install qemu qemu-system-x86`

After installing Qemu, you can then run the Iso file, the command is:
- `qemu-system-x86_64 -cdrom path/to/iso`
