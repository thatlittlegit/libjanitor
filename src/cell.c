/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
#define _DEFAULT_SOURCE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct janitor_cell
{
  void *key;
  void *real_return;
  struct janitor_context *ctx;
};

static struct janitor_cell **g_cells = NULL;
static unsigned g_ncells = 0;

struct janitor_cell *
janitor_cell_new (void *key, void *ret, struct janitor_context *context)
{
  assert (key != NULL);
  assert (ret != NULL);

  struct janitor_cell *new_cell = malloc (sizeof (struct janitor_cell));
  if (new_cell == NULL)
    goto cleanup_nothing;

  struct janitor_cell **new_gcells
      = reallocarray (g_cells, g_ncells + 1, sizeof (struct janitor_cell *));
  if (new_gcells == NULL)
    goto cleanup_cell;

  g_cells = new_gcells;
  g_ncells += 1;

  new_gcells[g_ncells - 1] = new_cell;

  new_cell->key = key;
  new_cell->real_return = ret;
  new_cell->ctx = context;
  return new_cell;

cleanup_cell:
  free (new_cell);
cleanup_nothing:
  return NULL;
}

struct janitor_cell *
janitor_cell_find (void *key)
{
  for (unsigned i = 0; i < g_ncells; ++i)
    {
      if (g_cells[i]->key == key)
        return g_cells[i];
    }

  return NULL;
}

void *
janitor_cell_get_return (struct janitor_cell *cell)
{
  return cell->real_return;
}

struct janitor_context *
janitor_cell_get_context (struct janitor_cell *cell)
{
  return cell->ctx;
}

void
janitor_cell_free (struct janitor_cell *cell)
{
  for (unsigned i = 0; i < g_ncells; ++i)
    {
      if (g_cells[i]->key != cell->key)
        continue;

      g_cells[i] = g_cells[g_ncells - 1];

      struct janitor_cell **cells
          = reallocarray (g_cells, g_ncells, sizeof (struct janitor_cell *));
      if (cells != NULL)
        g_cells = cells;

      break;
    }

  free (cell);
}
