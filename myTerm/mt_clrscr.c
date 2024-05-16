#include <myTerm.h>

int
mt_clrscr (void)
{
  fflush (stdout);
  if (write (STDOUT_FILENO, "\033[H\033[J", 6) == -1)
    return -1;
  return 0;
}