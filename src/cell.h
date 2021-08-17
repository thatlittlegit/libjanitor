/*
 * Copyright 2021 thatlittlegit <personal@thatlittlegit.tk>
 * SPDX-License-Identifier: LGPL-3.0-or-later
 */
#ifndef _janitor__cell_h_
#define _janitor__cell_h_

struct janitor_cell;
struct janitor_context;

struct janitor_cell *janitor_cell_new (void *key, void *ret,
                                       struct janitor_context *context);
struct janitor_cell *janitor_cell_find (void *key);

void *janitor_cell_get_return (struct janitor_cell *);
struct janitor_context *janitor_cell_get_context (struct janitor_cell *);

void janitor_cell_free (struct janitor_cell *);

#endif
