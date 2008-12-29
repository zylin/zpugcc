/*
 * Stub version of fork.
 */

#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>

int
_DEFUN (fork, (),
        _NOARGS)
{
  errno = ENOSYS;
  return -1;
}
