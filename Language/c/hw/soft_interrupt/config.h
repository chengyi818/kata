/*-*- mode:C; -*- */
/* config.h.  Generated from build/cmake/config.h.in by cmake configure */

/*
 * Ensure we have C99-style int64_t, etc, all defined.
 */

/* First, we need to know if the system has already defined them. */
#define HAVE_INTMAX_T
#define HAVE_UINTMAX_T

/* Define to `int' if <sys/types.h> doesn't define. */
/* #undef pid_t */

/* Define intmax_t and uintmax_t if they are not already defined. */
#if !defined(HAVE_INTMAX_T)
typedef int64_t intmax_t;
#define INTMAX_MIN INT64_MIN
#define INTMAX_MAX INT64_MAX
#endif

#if !defined(HAVE_UINTMAX_T)
typedef uint64_t uintmax_t;
#endif
