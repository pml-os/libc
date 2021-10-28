/* ANSI C namespace clean utility typedefs */

/* This file defines various typedefs needed by the system calls that support
   the C library.  Basically, they're just the POSIX versions with an '_'
   prepended.  Targets shall use <machine/_types.h> to define their own
   internal types if desired.

   There are three define patterns used for type definitions.  Lets assume
   xyz_t is a user type.

   The internal type definition uses __machine_xyz_t_defined.  It is defined by
   <machine/_types.h> to disable a default definition in <sys/_types.h>. It
   must not be used in other files.

   User type definitions are guarded by __xyz_t_defined in glibc and
   _XYZ_T_DECLARED in BSD compatible systems.
*/

#ifndef	_SYS__TYPES_H
#define _SYS__TYPES_H

#define __need_size_t
#define __need_wint_t
#include <stddef.h>
#include <newlib.h>
#include <sys/config.h>
#include <machine/_types.h>
#include <pml/types.h>

typedef off_t _off_t;
typedef off_t _off64_t;
typedef _off64_t __loff_t;

/*
 * We need fpos_t for the following, but it doesn't have a leading "_",
 * so we use _fpos_t instead.
 */
#ifndef __machine_fpos_t_defined
typedef long _fpos_t;		/* XXX must match off_t in <sys/types.h> */
				/* (and must be `long' for now) */
#endif

#ifdef __LARGE64_FILES
#ifndef __machine_fpos64_t_defined
typedef _off64_t _fpos64_t;
#endif
#endif

typedef ssize_t _ssize_t;

#ifndef __machine_mbstate_t_defined
/* Conversion state information.  */
typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;		/* Value so far.  */
} _mbstate_t;
#endif

#ifndef __machine_iconv_t_defined
/* Iconv descriptor type */
typedef void *_iconv_t;
#endif

#ifndef __machine_clock_t_defined
#define	_CLOCK_T_	clock_t
#endif

#if !defined(__time_t_defined) && !defined(_TIME_T_DECLARED)
#define _TIME_T_ time_t
#define	__time_t_defined
#define	_TIME_T_DECLARED
#endif

#ifndef __machine_clockid_t_defined
#define	_CLOCKID_T_ 	clockid_t;
#endif

#define	_TIMER_T_	timer_t

#ifndef __machine_sa_family_t_defined
typedef	__uint8_t	__sa_family_t;
#endif

#ifndef __machine_socklen_t_defined
typedef	__uint32_t	__socklen_t;
#endif

typedef	int		__nl_item;

/*
 * Must be identical to the __GNUCLIKE_BUILTIN_VAALIST definition in
 * <sys/cdefs.h>.  The <sys/cdefs.h> must not be included here to avoid cyclic
 * header dependencies.
 */
#if __GNUC_MINOR__ > 95 || __GNUC__ >= 3
typedef	__builtin_va_list	__va_list;
#else
typedef	char *			__va_list;
#endif

#endif	/* _SYS__TYPES_H */
