#
# ZPU:
# 
# There appears to be some sort of forward symbol reference bug that
# trips GDB. Disable for now as smooth running of the testsuite scripts
# is more important that chasing down this bug.
#
# Also GDB bugs have much lower priority than GCC bugs.

if { [istarget "zpu-*-*"] } {
  return 1
}
return 0
