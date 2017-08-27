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

License Info
------------

The kernel is licensed under a BSD-like license, with a derivative product name
clause.

All userland libraries, including the libc are licensed under the MPL.

liborl (used for loading ELF files) is licensed under the Sybase Open Source
License 1.0.

Feature Wishlist
----------------

Working:
  * Base syscall interface
  * Basic interrupt subsystem
  * Some memory management
  * In-kernel dynamic memory
  * Driver interface
  * memory mapping

TODO:
  * Task switching
  * Fleshed out syscall setup
  * Message passing

Someday (soonish wishlist):
  * SB16 or AC97 driver
  * ATAPI driver
  * exFAT file server

Someday (ambitious wishlist):
  * VESA driver
  * sndio audio server from OpenBSD
  * Hammer2 file server from DragonflyBSD
  * Booktree drivers from FreeBSD
  * xhci USB3 driver port from Linux
