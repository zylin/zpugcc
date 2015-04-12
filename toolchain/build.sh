#!/bin/bash
set -e
rm -rf build
mkdir build
cd build
export CFLAGS=-D_FORTIFY_SOURCE=0
../binutils/configure --target=zpu-elf --prefix=`pwd`/../install
make
make install
cd ..

export PATH=`pwd`/install/bin:$PATH
rm -rf gccbuild
mkdir gccbuild
cd gccbuild
#../gcc/configure --target=zpu-elf --prefix=`pwd`/../install --enable-languages=c,c++ --with-gnu-as --with-gnu-ld --with-newlib --disable-shared --enable-newlib -v --enable-checking=misc,tree,rtl,rtlflag,gc,gcac,fold  --disable-multilib --disable-threads --enable-sjlj-exceptions --enable-libstdcxx-allocator=malloc
../gcc/configure --target=zpu-elf --prefix=`pwd`/../install --enable-languages=c --with-gnu-as --with-gnu-ld --with-newlib --disable-shared --enable-newlib -v --enable-checking=misc,tree,rtl,rtlflag,gc,gcac,fold  --disable-multilib --disable-threads --enable-sjlj-exceptions --enable-libstdcxx-allocator=malloc
make
make install

