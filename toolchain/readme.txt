For demo
========
- Alpha release of toolchain including GDB.
- Alpha CD
- Create demo apps
  - Eliza (requires IO)
  - Dhrystone
  - eCos hello world/RedBoot?
- Finish presentation
- Abel prototype
  - Install software & compile VHDL & Simulate
  - Upload a selection of binaries


Todo
====
- Add -msim -mzeta options so correct linker files are chosen
- Add movdi/df. Requires careful integration w/regStack. R0:DF
  means that the value is stored in two consequtive registers.
- Can --relax be made default? See CRIS target
- Can -fomit-frame-pointer be made default w/-O1/O2/Os/O3?

Codesize
========
- Add LOADSP/STOREP
- Remove register allocation? Check how effective dead stack slot
  elimination actually is.
- more efficient cleanup of regStack
- ADDPC
- retire BRANCH(merge intocompare instructions)
- LOADPC/STOREPC
- Make CALL PC relative
- Add non-relaxable 13 bit absolute relocation, useful for microcode.

Wishlists
=========

- Get Mingw32 toolchain up and running. Fixed in GCC 4.0? See PR 14316

Testsuites
==========
- add newlib testsuite
- add libgloss testsuite
- add eCos testsuite 
- add GDB testsuite

Running the testsuite
=====================
1. Start the simulator

2. Run tests. E.g. to run only the execute tests...

make check-gcc RUNTESTFLAGS="execute.exp --target_board=zpu-remote --all"

Other examples:

- Run specific test:

make check-gcc RUNTESTFLAGS="compile.exp=20000804-1.c --target_board=zpu-remote --all"





Compiling toolchain under Linux
===============================

1. check out ecosboard/toolchain in Eclipse
2. chmod +x on all the executables that was checked out. Fortunally
a script exists for this purpose. This is a bug that has been fixed
in Eclipse 3.1

cd ecosboard/toolchain
sh fixperm.sh

3. Build as usual

Compiling eCos appliaction
==========================
1. Place eCos + zpu-elf-* in environment

export PATH=$PATH:`pwd`/install/bin:`pwd`/ecos-install/gnutools/arm-elf/bin:`pwd`/ecos-install/ecos-2.0/tools/bin
export ECOS_REPOSITORY=`pwd`/ecosboard/zpu/ecos/packages

2. Build eCos

mkdir foo
cd foo
ecosconfig new zeta default
ecosconfig tree
make

3. Link hello world app with eCos linker library

zpu-elf-gcc  -Iinstall/include hello.c -Linstall/lib  -Ttarget.ld  -nostdlib   -o hello.elf -Wall

Regression testing
==================
A bit of ad-hoc regression testing until we have our nightly build up will be fine.


Potential optimisations
=======================
- add support for loadsp/storesp
- add support for loadpc
- fix calling convention 
- which operators should we add support for? Today e.g. xorsi3 is handled via
  libcalls.

Building GDB
============
- Create symbolic links into binutils inside ecosboard\zpu\toolchain\gdb

mkdir bfd
cd bfd
lndir ../../binutils/bfd
cd ..
mkdir include
cd include
lndir ../../binutils/include
cd ..
mkdir opcodes
cd opcodes
lndir ../../binutils/opcodes
cd ..
mkdir libiberty
cd libiberty
lndir ../../binutils/libiberty

mkdir gdbbuild
cd gdbbuild
../ecosboard/zpu/toolchain/gdb/configure --target=zpu-elf --prefix=`pwd`/../install
make
make install

Powerful debugging tips
=======================

- The zpu-elf-gcc compiler will sometimes crash while compiling 
programs when entries are missing/malformed in the .md file.
- Grep the source code(e.g. using Eclipse).
- Use the debugger. From the gccbuild directory:

$ cd gcc
$ insight --args ./cc1  ../../gcctest/prehello.c -dg && cat ../../gcctest/prehello.s 

- Dump RTL for each pass, e.g. '-dg' dumps RTL  after register allocation.
- GCC will cause a segmentation fault when running, at which point the stack trace might
be lost. Try setting an earlier breakpoint using e.g break emit_*. Remember that 
Insight console has name completion using <TAB>. An example is where I had
defined beq, but not bne and the compiler crashed when trying to jump to bne code
emitter.

Building GCC
============
It is highly recommended to have the build directory be outside the Eclipse 
project where the toolchain is hosted. This makes CVS synchronization much 
easier.

To build bintools:

$ mkdir build
$ cd build
$ ../ecosboard/zpu/toolchain/binutils/configure --target=zpu-elf --prefix=`pwd`/../install
$ make
$ make install

To build GCC:

$ mkdir gccbuild
$ cd gccbuild
$ export PATH=$PATH:`pwd`/../install/bin
$ zpu-elf-ld -v 
GNU ld version 2.15
$ ../ecosboard/zpu/toolchain/gcc/configure --target=zpu-elf --prefix=`pwd`/../install --enable-languages=c,c++ --with-gnu-as --with-gnu-ld --with-newlib --disable-shared --enable-newlib -v --enable-checking=misc,tree,rtl,rtlflag,gc,gcac,fold  --disable-multilib --disable-threads --enable-sjlj-exceptions --enable-libstdcxx-allocator=malloc
$ make
$ make install
