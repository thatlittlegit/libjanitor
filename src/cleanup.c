/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
#include "cell.h"
#include <stdio.h>

void *
janitor_clean_post_c (void *sp)
{
  struct janitor_cell *cell = janitor_cell_find (sp);
  void *ret = janitor_cell_get_return (cell);
  struct janitor_context *ctx = janitor_cell_get_context (cell);
  janitor_cell_free (cell);

  printf ("hello\n");

  return ret;
}
