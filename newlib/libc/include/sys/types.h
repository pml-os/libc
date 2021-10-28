/* unified sys/types.h: 
   start with sef's sysvi386 version.
   merge go32 version -- a few ifdefs.
   h8300hms, h8300xray, and sysvnecv70 disagree on the following types:

   typedef int gid_t;
   typedef int uid_t;
   typedef int dev_t;
   typedef int ino_t;
   typedef int mode_t;
   typedef int caddr_t;

   however, these aren't "reasonable" values, the sysvi386 ones make far 
   more sense, and should work sufficiently well (in particular, h8300 
   doesn't have a stat, and the necv70 doesn't matter.) -- eichin
 */

#ifndef _SYS_TYPES_H

#include <_ansi.h>
#include <sys/cdefs.h>
#include <machine/_types.h>

/* BSD types permitted by POSIX and always exposed as in Glibc.  Only provided
   for backward compatibility with BSD code.  The uintN_t standard types should
   be preferred in new code. */
#if ___int8_t_defined
typedef __uint8_t	u_int8_t;
#endif
#if ___int16_t_defined
typedef __uint16_t	u_int16_t;
#endif 
#if ___int32_t_defined
typedef __uint32_t	u_int32_t;
#endif
#if ___int64_t_defined
typedef __uint64_t	u_int64_t;
#endif
typedef __intptr_t register_t;
#define __BIT_TYPES_DEFINED__ 1

#ifndef __need_inttypes

#define _SYS_TYPES_H
#include <sys/_types.h>
#include <sys/_stdint.h>

#if __BSD_VISIBLE
#include <machine/endian.h>
#include <sys/select.h>
#  define	physadr		physadr_t
#  define	quad		quad_t

#ifndef _IN_ADDR_T_DECLARED
typedef	__uint32_t	in_addr_t;	/* base type for internet address */
#define	_IN_ADDR_T_DECLARED
#endif

#ifndef _IN_PORT_T_DECLARED
typedef	__uint16_t	in_port_t;
#define	_IN_PORT_T_DECLARED
#endif

typedef	__uintptr_t	u_register_t;
#endif /* __BSD_VISIBLE */

#if __MISC_VISIBLE
#ifndef _BSDTYPES_DEFINED
/* also defined in mingw/gmon.h and in w32api/winsock[2].h */
#ifndef __u_char_defined
typedef	unsigned char	u_char;
#define __u_char_defined
#endif
#ifndef __u_short_defined
typedef	unsigned short	u_short;
#define __u_short_defined
#endif
#ifndef __u_int_defined
typedef	unsigned int	u_int;
#define __u_int_defined
#endif
#ifndef __u_long_defined
typedef	unsigned long	u_long;
#define __u_long_defined
#endif
#define _BSDTYPES_DEFINED
#endif
#endif /* __MISC_VISIBLE */

#if __MISC_VISIBLE
typedef	unsigned short	ushort;		/* System V compatibility */
typedef	unsigned int	uint;		/* System V compatibility */
typedef	unsigned long	ulong;		/* System V compatibility */
#endif

#if !defined(__clock_t_defined) && !defined(_CLOCK_T_DECLARED)
typedef	_CLOCK_T_	clock_t;
#define	__clock_t_defined
#define	_CLOCK_T_DECLARED
#endif

#if !defined(__time_t_defined) && !defined(_TIME_T_DECLARED)
typedef	_TIME_T_	time_t;
#define	__time_t_defined
#define	_TIME_T_DECLARED
#endif

#ifndef __daddr_t_defined
typedef	long	daddr_t;
#define __daddr_t_defined
#endif
#ifndef __caddr_t_defined
typedef	char *	caddr_t;
#define __caddr_t_defined
#endif

typedef	__int64_t	sbintime_t;

#include <sys/features.h>
#include <sys/_pthreadtypes.h>
#include <machine/types.h>

#endif  /* !__need_inttypes */

#undef __need_inttypes

#endif	/* _SYS_TYPES_H */
