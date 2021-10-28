#ifndef	_SYS_STAT_H
#define	_SYS_STAT_H

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>
#include <time.h>
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/_timespec.h>

/* dj's stat defines _STAT_H_ */
#ifndef _STAT_H_

/* It is intended that the layout of this structure not change when the
   sizes of any of the basic types change (short, int, long) [via a compile
   time option].  */

#include <pml/stat.h>

#define 	S_BLKSIZE  1024 /* size of a block */

#if __BSD_VISIBLE
#define	S_IREAD		0000400	/* read permission, owner */
#define	S_IWRITE 	0000200	/* write permission, owner */
#define	S_IEXEC		0000100	/* execute/search permission, owner */
#define	S_ENFMT 	0002000	/* enforcement-mode locking */

#define ACCESSPERMS (S_IRWXU | S_IRWXG | S_IRWXO) /* 0777 */
#define ALLPERMS (S_ISUID | S_ISGID | S_ISVTX | S_IRWXU | S_IRWXG | S_IRWXO) /* 07777 */
#define DEFFILEMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH) /* 0666 */
#endif

#if defined(__CYGWIN__)
/* Special tv_nsec values for futimens(2) and utimensat(2). */
#define UTIME_NOW	-2L
#define UTIME_OMIT	-1L
#endif

int	chmod (const char *__path, mode_t __mode );
int     fchmod (int __fd, mode_t __mode);
int	fstat (int __fd, struct stat *__sbuf );
int	mkdir (const char *_path, mode_t __mode );
int	mkfifo (const char *__path, mode_t __mode );
int	stat (const char *__restrict __path, struct stat *__restrict __sbuf );
mode_t	umask (mode_t __mask );

#if defined (__SPU__) || defined(__rtems__) || defined(__CYGWIN__) && !defined(__INSIDE_CYGWIN__)
int	lstat (const char *__restrict __path, struct stat *__restrict __buf );
int	mknod (const char *__path, mode_t __mode, dev_t __dev );
#endif

#if __ATFILE_VISIBLE && !defined(__INSIDE_CYGWIN__)
int	fchmodat (int, const char *, mode_t, int);
int	fstatat (int, const char *__restrict , struct stat *__restrict, int);
int	mkdirat (int, const char *, mode_t);
int	mkfifoat (int, const char *, mode_t);
int	mknodat (int, const char *, mode_t, dev_t);
int	utimensat (int, const char *, const struct timespec *, int);
#endif
#if __POSIX_VISIBLE >= 200809 && !defined(__INSIDE_CYGWIN__)
int	futimens (int, const struct timespec *);
#endif

/* Provide prototypes for most of the _<systemcall> names that are
   provided in newlib for some compilers.  */
#ifdef _COMPILING_NEWLIB
int	_fstat (int __fd, struct stat *__sbuf );
int	_stat (const char *__restrict __path, struct stat *__restrict __sbuf );
int	_mkdir (const char *_path, mode_t __mode );
#ifdef __LARGE64_FILES
struct stat64;
int	_stat64 (const char *__restrict __path, struct stat64 *__restrict __sbuf );
int	_fstat64 (int __fd, struct stat64 *__sbuf );
#endif
#endif

#endif /* !_STAT_H_ */
#ifdef __cplusplus
}
#endif
#endif /* _SYS_STAT_H */
