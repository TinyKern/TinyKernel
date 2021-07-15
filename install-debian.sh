# * @file install-debian.sh
# * @author Owen Boreham (owenkadeboreham@gmail.com)
# * @version 0.1.2
# * @date 2021-07-06
# * 
# * @copyright Copyright (c) 2021 TinyKernel
# * This file is part of TinyKernel which is released
# * under Apache License 2.0.  See file LICENSE or go
# * to https://www.apache.org/licenses/LICENSE-2.0 for
# * full license details.

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

# install requirements
echo "Installing important requirements:";
echo "  apt-get install binutils";
echo "  apt-get install gcc";
sudo apt-get -y --no-install-recommends install binutils gcc;
sudo apt-get -y --no-install-recommends install qemu-system-x86;
make iso

# Run
while true; do
  read -p "Do you want to run? <Y/n>: " yn;
  case $yn in
    [Yy]* ) make run; break;;
    [Nn]* ) exit;;
    * ) echo "Please enter <Y/n>";;
  esac
done
