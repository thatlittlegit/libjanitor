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

#if defined __GNUC__
#define JANITOR_FUNC extern __attribute__ ((visibility ("default")))
#else
#define JANITOR_FUNC extern
#endif

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
JANITOR_FUNC struct janitor_context *janitor_context_new (void);

/**
 * Adds a function to the Janitor context. The function will be called with the
 * provided element.
 */
JANITOR_FUNC void janitor_context_add (struct janitor_context *, void *,
                                       janitor_free_t *);

/**
 * Get the last thing to free in the Janitor context, removing it from the
 * context.
 */
JANITOR_FUNC unsigned janitor_context_iter (struct janitor_context *, void **,
                                            janitor_free_t **);

/**
 * Frees a given context. Note that it can't be in use within a janitor_clean;
 * if it is, it will be a use-after-free.
 *
 * It's automatically freed during a janitor_clean.
 */
JANITOR_FUNC void janitor_context_free (struct janitor_context *);

/**
 * Schedules the given context to be cleaned at the end of the function.
 */
JANITOR_FUNC void janitor_clean (struct janitor_context *);
