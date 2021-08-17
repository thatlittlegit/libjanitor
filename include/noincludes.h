/**
 * @file noincludes.h
 * @copyright Copyright 2021 thatlittlegit
 * @license SPDX-License-Identifier: LGPL-3.0-or-later
 */
#ifdef __janitor__noincludes_h__
#error cannot include noincludes.h twice, use janitor.h
#endif
#define __janitor__noincludes_h__

typedef void (janitor_free_t) (void *);

/**
 * @struct janitor_context
 *
 * Represents the data and functions that will be freed by janitor_clean. It's
 * automatically freed.
 */
struct janitor_context;

/**
 * Creates a new, automatically-resizing Janitor context, using the default
 * allocator.
 *
 * @returns the new allocator, or NULL on allocation failure
 */
struct janitor_context *janitor_context_new (void);

/**
 * Adds a function to the Janitor context. The function will be called with the
 * provided element.
 */
void janitor_context_add (struct janitor_context *, void *, janitor_free_t *);

/**
 * Get the last thing to free in the Janitor context, removing it from the
 * context.
 */
void janitor_context_iter (struct janitor_context *, void **,
                           janitor_free_t **);
/**
 * Schedules the given context to be cleaned at the end of the function.
 */
void janitor_clean (struct janitor_context *);
