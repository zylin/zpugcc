# zpugcc

This repository contain the gcc, which is adapted for https://github.com/zylin/zpu CPU,
the worlds smallest 32 bit CPU with GCC toolchain.

# ZPU toolchain source code
The ZPU toolchain is too big to be hosted together with the HDL and the idea is that most HDL or normal users would not want to download and build their own toolchain.

# ZPU build instructions to build unstable on linux (same for CygWin32)

    git clone https://github.com/zylin/zpugcc.git
    cd toolchain/toolchain
    sh fixperm.sh
    . env.sh
    sh build.sh
    tar -cjvf zpugcclinux_unstable.tar.bz2 install 

Build a different version

    git log => shows log entries
    git checkout 322875263beccb1d75936bd1dd9150c1647dc9c0 => checkout a version
    Note that build.sh is only present in the later versions, but that it should work fine for those versions in git where it is absent. 

# Cygwin build problems
If you are having problems building with Cygwin, try erasing the *entire* c:\cygwin folder and try again. 
