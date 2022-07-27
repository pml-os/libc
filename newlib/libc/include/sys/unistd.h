#ifndef _SYS_UNISTD_H
#define _SYS_UNISTD_H

#ifdef __cplusplus
extern "C" {
#endif

#include <_ansi.h>
#define __need_size_t
#define __need_ptrdiff_t
#include <sys/cdefs.h>
#include <sys/types.h>
#include <sys/_types.h>
#include <stddef.h>
#include <pml/fcntl.h>

extern char **environ;

void	_exit (int __status) _ATTRIBUTE ((__noreturn__));

int	access (const char *__path, int __amode);
unsigned  alarm (unsigned __secs);
int     chdir (const char *__path);
int     chmod (const char *__path, mode_t __mode);
#if !defined(__INSIDE_CYGWIN__)
int     chown (const char *__path, uid_t __owner, gid_t __group);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE >= 4 && __POSIX_VISIBLE < 200112)
int     chroot (const char *__path);
#endif
int     close (int __fildes);
#if __POSIX_VISIBLE >= 199209
size_t	confstr (int __name, char *__buf, size_t __len);
#endif
#if __XSI_VISIBLE
char *  crypt (const char *__key, const char *__salt);
#endif
#if __XSI_VISIBLE && __XSI_VISIBLE < 700
char *  ctermid (char *__s);
#endif
#if __XSI_VISIBLE && __XSI_VISIBLE < 600
char *  cuserid (char *__s);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
int	daemon (int nochdir, int noclose);
#endif
int     dup (int __fildes);
int     dup2 (int __fildes, int __fildes2);
#if __GNU_VISIBLE
int     dup3 (int __fildes, int __fildes2, int flags);
int	eaccess (const char *__path, int __mode);
#endif
#if __XSI_VISIBLE
void	encrypt (char *__block, int __edflag);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
void	endusershell (void);
#endif
#if __GNU_VISIBLE
int	euidaccess (const char *__path, int __mode);
#endif
int     execl (const char *__path, const char *, ...);
int     execle (const char *__path, const char *, ...);
int     execlp (const char *__file, const char *, ...);
#if __MISC_VISIBLE
int     execlpe (const char *__file, const char *, ...);
#endif
int     execv (const char *__path, char * const __argv[]);
int     execve (const char *__path, char * const __argv[], char * const __envp[]);
int     execvp (const char *__file, char * const __argv[]);
#if __GNU_VISIBLE
int     execvpe (const char *__file, char * const __argv[], char * const __envp[]);
#endif
#if __ATFILE_VISIBLE
int	faccessat (int __dirfd, const char *__path, int __mode, int __flags);
#endif
#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int     fchdir (int __fildes);
#endif
#if __POSIX_VISIBLE >= 199309
int     fchmod (int __fildes, mode_t __mode);
#endif
#if !defined(__INSIDE_CYGWIN__)
#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int     fchown (int __fildes, uid_t __owner, gid_t __group);
#endif
#endif
#if __ATFILE_VISIBLE
int	fchownat (int __dirfd, const char *__path, uid_t __owner, gid_t __group, int __flags);
#endif
#if __POSIX_VISIBLE >= 200809
int	fexecve (int __fd, char * const __argv[], char * const __envp[]);
#endif
pid_t   fork (void);
long    fpathconf (int __fd, int __name);
int     fsync (int __fd);
#if __POSIX_VISIBLE >= 199309
int     fdatasync (int __fd);
#endif
#if __GNU_VISIBLE
char *  get_current_dir_name (void);
#endif
char *  getcwd (char *__buf, size_t __size);
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
int	getdomainname  (char *__name, size_t __len);
#endif
#if __BSD_VISIBLE
int     getentropy (void *, size_t);
#endif
#if !defined(__INSIDE_CYGWIN__)
gid_t   getegid (void);
uid_t   geteuid (void);
gid_t   getgid (void);
#endif
int     getgroups (int __gidsetsize, gid_t __grouplist[]);
#if __BSD_VISIBLE || __XSI_VISIBLE >= 4
long    gethostid (void);
#endif
char *  getlogin (void);
#if defined(_POSIX_THREAD_SAFE_FUNCTIONS)
int getlogin_r (char *name, size_t namesize) ;
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __POSIX_VISIBLE < 200112)
char *  getpass (const char *__prompt);
int	getpagesize (void);
#endif
#if __BSD_VISIBLE
int    getpeereid (int, uid_t *, gid_t *);
#endif
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE >= 4
pid_t   getpgid (pid_t);
#endif
pid_t   getpgrp (void);
pid_t   getpid (void);
pid_t   getppid (void);
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE >= 4
pid_t   getsid (pid_t);
#endif
#if !defined(__INSIDE_CYGWIN__)
uid_t   getuid (void);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
char *	getusershell (void);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE >= 4 && __POSIX_VISIBLE < 200809)
char *  getwd (char *__buf);
#endif
#if __BSD_VISIBLE
int	iruserok (unsigned long raddr, int superuser, const char *ruser, const char *luser);
#endif
int     isatty (int __fildes);
#if __BSD_VISIBLE
int        issetugid (void);
#endif
#if !defined(__INSIDE_CYGWIN__)
#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int     lchown (const char *__path, uid_t __owner, gid_t __group);
#endif
#endif
int     link (const char *__path1, const char *__path2);
#if __ATFILE_VISIBLE
int     linkat (int __dirfd1, const char *__path1, int __dirfd2, const char *__path2, int __flags);
#endif
#if __MISC_VISIBLE || __XSI_VISIBLE
int	nice (int __nice_value);
#endif
#if !defined(__INSIDE_CYGWIN__)
off_t   lseek (int __fildes, off_t __offset, int __whence);
#endif
#if __MISC_VISIBLE || __XSI_VISIBLE >= 4
#define F_ULOCK	0
#define F_LOCK	1
#define F_TLOCK	2
#define F_TEST	3
int     lockf (int __fd, int __cmd, off_t __len);
#endif
long    pathconf (const char *__path, int __name);
int     pause (void);
#if __POSIX_VISIBLE >= 199506
int	pthread_atfork (void (*)(void), void (*)(void), void (*)(void));
#endif
int     pipe (int __fildes[2]);
#if __GNU_VISIBLE
int     pipe2 (int __fildes[2], int flags);
#endif
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE >= 500
ssize_t pread (int __fd, void *__buf, size_t __nbytes, off_t __offset);
ssize_t pwrite (int __fd, const void *__buf, size_t __nbytes, off_t __offset);
#endif
_READ_WRITE_RETURN_TYPE read (int __fd, void *__buf, size_t __nbyte);
#if __BSD_VISIBLE
int	rresvport (int *__alport);
int	revoke (char *__path);
#endif
int     rmdir (const char *__path);
#if __BSD_VISIBLE
int	ruserok (const char *rhost, int superuser, const char *ruser, const char *luser);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE >= 4 && __POSIX_VISIBLE < 200112)
void *  sbrk (ptrdiff_t __incr);
#endif
#if !defined(__INSIDE_CYGWIN__)
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200112
int     setegid (gid_t __gid);
int     seteuid (uid_t __uid);
#endif
int     setgid (gid_t __gid);
#endif
#if __BSD_VISIBLE
int	setgroups (int ngroups, const gid_t *grouplist);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
int	sethostname (const char *, size_t);
#endif
int     setpgid (pid_t __pid, pid_t __pgid);
#if __SVID_VISIBLE || __XSI_VISIBLE >= 500
int     setpgrp (void);
#endif
#if (__BSD_VISIBLE || __XSI_VISIBLE >= 4) && !defined(__INSIDE_CYGWIN__)
int	setregid (gid_t __rgid, gid_t __egid);
int	setreuid (uid_t __ruid, uid_t __euid);
#endif
pid_t   setsid (void);
#if !defined(__INSIDE_CYGWIN__)
int     setuid (uid_t __uid);
#endif
#if __BSD_VISIBLE || (__XSI_VISIBLE && __XSI_VISIBLE < 500)
void	setusershell (void);
#endif
unsigned sleep (unsigned int __seconds);
#if __XSI_VISIBLE
void    swab (const void *__restrict, void *__restrict, ssize_t);
#endif
long    sysconf (int __name);
pid_t   tcgetpgrp (int __fildes);
int     tcsetpgrp (int __fildes, pid_t __pgrp_id);
char *  ttyname (int __fildes);
int     ttyname_r (int, char *, size_t);
int     unlink (const char *__path);
#if __XSI_VISIBLE >= 500 && __POSIX_VISIBLE < 200809 || __BSD_VISIBLE
int 	usleep (useconds_t __useconds);
#endif
#if __BSD_VISIBLE
int     vhangup (void);
#endif
_READ_WRITE_RETURN_TYPE write (int __fd, const void *__buf, size_t __nbyte);

#ifdef __CYGWIN__
# define __UNISTD_GETOPT__
# include <getopt.h>
# undef __UNISTD_GETOPT__
#else
extern char *optarg;			/* getopt(3) external variables */
extern int optind, opterr, optopt;
int	 getopt(int, char * const [], const char *);
extern int optreset;			/* getopt(3) external variable */
#endif

#if __BSD_VISIBLE || (__XSI_VISIBLE >= 4 && __POSIX_VISIBLE < 200809)
pid_t   vfork (void);
#endif

#ifdef _COMPILING_NEWLIB
/* Provide prototypes for most of the _<systemcall> names that are
   provided in newlib for some compilers.  */
int     _close (int __fildes);
pid_t   _fork (void);
pid_t   _getpid (void);
int	_isatty (int __fildes);
int     _link (const char *__path1, const char *__path2);
_off_t   _lseek (int __fildes, _off_t __offset, int __whence);
#ifdef __LARGE64_FILES
_off64_t _lseek64 (int __filedes, _off64_t __offset, int __whence);
#endif
_READ_WRITE_RETURN_TYPE _read (int __fd, void *__buf, size_t __nbyte);
void *  _sbrk (ptrdiff_t __incr);
int     _unlink (const char *__path);
_READ_WRITE_RETURN_TYPE _write (int __fd, const void *__buf, size_t __nbyte);
int     _execve (const char *__path, char * const __argv[], char * const __envp[]);
#endif

#if !defined(__INSIDE_CYGWIN__)
#if __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE >= 500
int     ftruncate (int __fd, off_t __length);
#endif
#if __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE >= 500
int     truncate (const char *, off_t __length);
#endif
#endif

#if __BSD_VISIBLE || __POSIX_VISIBLE < 200112
int	getdtablesize (void);
#endif
#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200809 || __XSI_VISIBLE >= 500
useconds_t ualarm (useconds_t __useconds, useconds_t __interval);
#endif

#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE >= 500
#if !(defined  (_WINSOCK_H) || defined (_WINSOCKAPI_) || defined (__USE_W32_SOCKETS))
/* winsock[2].h defines as __stdcall, and with int as 2nd arg */
 int	gethostname (char *__name, size_t __len);
#endif
#endif

#if __MISC_VISIBLE
int	setdtablesize (int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 500
void    sync (void);
#endif

#if __BSD_VISIBLE || __POSIX_VISIBLE >= 200112 || __XSI_VISIBLE >= 4
ssize_t readlink (const char *__restrict __path,
                          char *__restrict __buf, size_t __buflen);
int     symlink (const char *__name1, const char *__name2);
#endif
#if __ATFILE_VISIBLE
ssize_t        readlinkat (int __dirfd1, const char *__restrict __path,
                            char *__restrict __buf, size_t __buflen);
int	symlinkat (const char *, int, const char *);
int	unlinkat (int, const char *, int);
#endif

#include <sys/features.h>

#define STDIN_FILENO    0       /* standard input file descriptor */
#define STDOUT_FILENO   1       /* standard output file descriptor */
#define STDERR_FILENO   2       /* standard error file descriptor */

#ifdef __cplusplus
}
#endif

#if __SSP_FORTIFY_LEVEL > 0
#include <ssp/unistd.h>
#endif

#endif /* _SYS_UNISTD_H */
