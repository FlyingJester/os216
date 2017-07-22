OS 216
======

OS 216 is a hobby OS meant to be a learning experience, and to be fun to write.
Maybe some day it will be a good example of microkernel design and demonstrate
an efficient message passing interface, good driver architecture, and have a
clean and portable linker, libc, and C++ standard library implementation.

It is intended to be a microkernel OS with its own linker, libc, and C++
standard library. It is based on the concept that sending a message between
processes results in the message being unmapped in the sender's address space
and then being mapped into the receiver's address space.

The kernel will only contain drivers to manage memory, schedule CPU time, and
multiplex the system (PCI) bus. All other drivers will run in userspace, with
any memory-mapped IO or IO port usage being audited by the kernel.

The kernel is written in C, C++, and assembly. Most of the kernel is written in
C++, semi-portable drivers (like PCI and VGA text mode drivers) are mostly
written in C, and low-level (non-portable) drivers are mostly written in
assembly.

Working:
  * Base syscall interface
  * Basic interrupt subsystem
  * Some memory management
  * In-kernel dynamic memory

TODO:
  * Task switching
  * Fleshed out syscall setup
  * Message passing and memory mapping
  * Driver interface

Someday (soonish wishlist):
  * SB16 driver
  * VESA driver
  * ATAPI driver
  * exFAT file server

Someday (ambitious wishlist):
  * sndio audio server from OpenBSD
  * Hammer2 file server from DragonflyBSD
  * Booktree drivers from FreeBSD
  * xhci USB3 driver port from Linux
