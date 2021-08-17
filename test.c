/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: CC0-1.0
 */
#include <stdio.h>
#include <stdlib.h>

void janitor_clean (void *);

int
main ()
{
  janitor_clean (NULL);
  printf ("hello, world!\n");
}
