#include "common.h"

int main(int ac, char *av[])
{
  char a[32] = "Introduction", b[32] = "Programming", *s, *t;

  s = a;
  t = b;

  while (*s++ = *t++)
    ;

  puts(a);
  puts(s);

  return 0;
}