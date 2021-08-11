<img alt="TinyKernel Cover Art" src="https://raw.githubusercontent.com/TinyKern/TinyKernel/master/Assets/TinyKernel%20Cover%20Art.png" width=650 />

[![Gitpod ready-to-code](https://img.shields.io/badge/Gitpod-ready--to--code-blue?logo=gitpod)](https://gitpod.io/#https://github.com/TinyKern/TinyKernel)
[![Lines of code](https://img.shields.io/tokei/lines/github/TinyKern/TinyKernel?color=pink)](https://github.com/TinyKern/TinyKernel/)
[![Issues Closed](https://img.shields.io/github/issues-search/TinyKern/TinyKernel?color=red&label=Issues%20Closed&query=is%3Aclosed)](https://github.com/TinyKern/TinyKernel/issues)
[![License](https://img.shields.io/github/license/TinyKern/TinyKernel)](https://github.com/TinyKern/TinyKernel/blob/0.1.3/LICENSE)
[![Tag](https://img.shields.io/github/v/tag/TinyKern/TinyKernel)](https://github.com/TinyKern/TinyKernel/releases)

# TinyKernel - 0.1.3
Tiny Kernel is a work in progress Operating System kernel.

By the end of the project, I hope to have a fully functional and working Kernel. Since System development is my prefered type of development, 
I thought it was time to finally create a project from the ground up, with its own x86 architecture and its own operating system to end up using
the kernel.

## Setup
[Disclaimer] - TinyKernel currently only builds on Linux distributions.

Currently, there is too many files for people to just manually enter commands to run and build, therefor, you should really use the provided Makefile. just enter `make` into the commandline at the root of the project, & it will build the project for you. After, you can enter `make run` into the command line, & it will run the following project.
### ISO
#### Debian/Ubuntu
---
**Install Qemu:**
- `sudo apt-get install qemu qemu-system-x86`

After installing Qemu, you can then run the Iso file, the command is:
- `qemu-system-x86_64 -cdrom path/to/iso`

## Screenshots

Date: 7/25/2021

<img alt="TinyKernel Cover Art" src="https://raw.githubusercontent.com/TinyKern/TinyKernel/master/Assets/TinyKernel%20Preview.png" width=650 />

---
Date: 8/11/2021

<img alt="TinyKernel Cover Art" src="https://raw.githubusercontent.com/TinyKern/TinyKernel/master/Assets/TinyKernelPreview2.png" width=650 />
