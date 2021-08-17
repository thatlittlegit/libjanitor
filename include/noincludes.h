/**
 * @file noincludes.h
 * @copyright Copyright 2021 thatlittlegit
 * @license SPDX-License-Identifier: LGPL-3.0-or-later
 */
#ifdef __janitor__noincludes_h__
#error cannot include noincludes.h twice, use janitor.h
#endif
#define __janitor__noincludes_h__

/**
 * Schedules the given context to be cleaned at the end of the function.
 */
void janitor_clean (struct janitor_context *);
