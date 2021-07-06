# * @file install-debian.sh
# * @author Owen Boreham (owenkadeboreham@gmail.com)
# * @version 0.1
# * @date 2021-07-06
# * 
# * @copyright Copyright (c) 2021 TinyKernel
# * This file is part of TinyKernel which is released
# * under Apache License 2.0.  See file LICENSE or go
# * to https://www.apache.org/licenses/LICENSE-2.0 for
# * full license details.

clear;
version=0.1.3;
iso_name="TinyKernel_Bobrossrtx-${version}.iso";
echo \
"
▀█▀ █ █▄░█ █▄█ █▄▀ █▀▀ █▀█ █▄░█ ▄▀█ █░░
░█░ █ █░▀█ ░█░ █░█ ██▄ █▀▄ █░▀█ █▀█ █▄▄
    Created by: Owen Boreham
    Version: ${version}
    Iso: ${iso_name}
";

include_dir="include";
kernel_dir="kernel";
build_dir="build";

# Build subdirs
boot_dir="${build_dir}/boot";
grub_dir="${boot_dir}/grub";
obj_dir="${build_dir}/obj";
iso_dir="${build_dir}/iso";

clean()
{
  echo "${build_dir}/ already exists:"
  echo "  rm -rf ${build_dir}\n";
  rm -rf $build_dir;
}

if [ -d "build" ]; then
  clean;
fi

# Install QEMU
echo "Installing QEMU & GRUB & xorriso:";
echo "  apt-get install qemu-system-x86";
echo "  apt-get install grub-common";
echo "  apt-get install xorriso\n";
sudo apt-get install qemu-system-x86 grub-common xorriso;

sleep 0.5; # suspense...
# Create build dirs
echo "Creating Build dir:";
echo "  mkdir ${build_dir}:             📁";
sleep 0.5; # suspense...
echo "        ${boot_dir}:        📁";
sleep 0.5; # suspense...
echo "        ${grub_dir}:   📁";
sleep 0.5; # suspense...
echo "        ${obj_dir}:         📁";
sleep 0.5; # suspense...
echo "        ${iso_dir}:         📁\n";

# Create the build directories
mkdir $build_dir;
mkdir -p $boot_dir $grub_dir $obj_dir $iso_dir;

# assemble boot.s file
sleep 0.5; # suspense...
echo "Assembling ./boot.s:";
echo "  as --32 ./boot.s -o ${obj_dir}/boot.o";
as --32 ./boot.s -o ${obj_dir}/boot.o;

sleep 0.5; # suspense...
# Compile ${kernel_dir}/kernel.c file
echo "Compiling ./${kernel_dir}/kernel.c:";
echo "  gcc -m32 -c ${kernel_dir}/kernel.c -o ${obj_dir}/kernel.o \\";
echo "    -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ${include_dir}\n";
gcc -m32 -c ${kernel_dir}/kernel.c -o ${obj_dir}/kernel.o \
  -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I $include_dir;

sleep 0.5; # suspense...
# Linking the kernel with ${obj_dir}/kernel.o and ${obj_dir}/boot.o files
echo "Linking kernel:";
echo "  ld -m elf_i386 -T linker.ld ${obj_dir}/kernel.o ${obj_dir}/boot.o \\";
echo "    -o ${boot_dir}/TinyKernel.bin\n";
ld -m elf_i386 -T linker.ld ${obj_dir}/kernel.o ${obj_dir}/boot.o \
  -o ${boot_dir}/TinyKernel.bin;

sleep 0.5; # suspense..
# Check TinyKernel.bin file is x86 multiboot file or not
echo "Checking ${boot_dir}/TinyKernel.bin:";
echo "  grub-file --is-x86-multiboot ${boot_dir}/TinyKernel.bin";
grub-file --is-x86-multiboot ${boot_dir}/TinyKernel.bin;

sleep 0.5; # suspense..

# Building the ISO file
echo "Building ISO:";
echo "  cp grub.cfg ${grub_dir}/grub.cfg";
echo "  grub-mkrescue -o ${iso_name} ${build_dir}";
cp grub.cfg ${grub_dir}/grub.cfg;
grub-mkrescue -o ${iso_name} ${build_dir};
echo "Moving ISO:";
echo "  mv ${iso_name} ${iso_dir}/${iso_name}";
mv ${iso_name} ${iso_dir}/${iso_name};

# Run
while true; do
  read -p "Do you want to run? <Y/n>: " yn;
  case $yn in
    [Yy]* ) qemu-system-x86_64 -cdrom ${iso_dir}/${iso_name}; break;;
    [Nn]* ) exit;;
    * ) echo "\nPlease enter <Y/n>";;
  esac
done