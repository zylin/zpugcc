
#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>

unsigned int sleep(unsigned int seconds)
{
  errno = ENOSYS;
  return -1;
}
