/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: CC0-1.0
 */
#include "include/janitor.h"
#include <stdio.h>
#include <stdlib.h>

int
main ()
{
  void *data = malloc(128);
  struct janitor_context *ctx = janitor_context_new();
  janitor_context_add(ctx, data, free);
  janitor_clean (ctx);
  printf ("hello, world!\n");
}
