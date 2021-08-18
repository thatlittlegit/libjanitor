/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
#define _DEFAULT_SOURCE

#include "../include/janitor.h"
#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

struct janitor_item
{
  void *ptr;
  janitor_free_t *free;
};

struct janitor_context
{
  unsigned count;
  struct janitor_item *items;
};

struct janitor_context *
janitor_context_new (void)
{
  struct janitor_context *ctx = malloc (sizeof (struct janitor_context));
  if (ctx == NULL)
    return NULL;

  ctx->count = 0;
  ctx->items = NULL;

  return ctx;
}

void
janitor_context_add (struct janitor_context *ctx, void *ptr,
                     janitor_free_t *free)
{
  assert (ctx != NULL);
  assert (free != NULL);

  struct janitor_item *items = reallocarray (ctx->items, ctx->count + 1,
                                             sizeof (struct janitor_item));

  assert (items != NULL);

  ctx->items = items;
  ctx->items[ctx->count].ptr = ptr;
  ctx->items[ctx->count].free = free;
  ctx->count += 1;
}

unsigned
janitor_context_iter (struct janitor_context *ctx, void **ptr,
                      janitor_free_t **free)
{
  assert (ctx != NULL);

  if (ctx->count == 0)
    return 0;

  struct janitor_item *item = &ctx->items[ctx->count - 1];

  if (ptr != NULL)
    *ptr = item->ptr;

  if (free != NULL)
    *free = item->free;

  struct janitor_item *items = reallocarray (ctx->items, ctx->count - 1,
                                             sizeof (struct janitor_item));

  if (ctx->count == 1 || items != NULL)
    ctx->items = items;

  return ctx->count--;
}

void
janitor_context_free (struct janitor_context *ctx)
{
  free (ctx->items);
  free (ctx);
}
