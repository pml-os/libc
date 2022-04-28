/* sys/signal.h */

#ifndef _SYS_SIGNAL_H
#define _SYS_SIGNAL_H
#ifdef __cplusplus
extern "C" {
#endif

#include "_ansi.h"
#include <pml/signal.h>
#include <sys/cdefs.h>
#include <sys/features.h>
#include <sys/types.h>
#include <sys/_timespec.h>

typedef sighandler_t _sig_func_ptr;

#if defined(__CYGWIN__)
#include <cygwin/signal.h>
#else

#if defined(_POSIX_REALTIME_SIGNALS) || __POSIX_VISIBLE >= 199309

/* sigev_notify values
   NOTE: P1003.1c/D10, p. 34 adds SIGEV_THREAD.  */

#define SIGEV_NONE   1  /* No asynchronous notification shall be delivered */
                        /*   when the event of interest occurs. */
#define SIGEV_SIGNAL 2  /* A queued signal, with an application defined */
                        /*  value, shall be delivered when the event of */
                        /*  interest occurs. */
#define SIGEV_THREAD 3  /* A notification function shall be called to */
                        /*   perform notification. */

/*  Signal Generation and Delivery, P1003.1b-1993, p. 63
    NOTE: P1003.1c/D10, p. 34 adds sigev_notify_function and
          sigev_notify_attributes to the sigevent structure.  */

struct sigevent {
  int              sigev_notify;               /* Notification type */
  int              sigev_signo;                /* Signal number */
  union sigval     sigev_value;                /* Signal value */

#if defined(_POSIX_THREADS)
  void           (*sigev_notify_function)( union sigval );
                                               /* Notification function */
  pthread_attr_t  *sigev_notify_attributes;    /* Notification Attributes */
#endif
};

#endif /* defined(_POSIX_REALTIME_SIGNALS) || __POSIX_VISIBLE >= 199309 */

#endif /* defined(__CYGWIN__) */

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
/*
 * Minimum and default signal stack constants. Allow for target overrides
 * from <sys/features.h>.
 */
#ifndef	MINSIGSTKSZ
#define	MINSIGSTKSZ	2048
#endif
#ifndef	SIGSTKSZ
#define	SIGSTKSZ	8192
#endif
#endif

#if __POSIX_VISIBLE

int sigprocmask (int, const sigset_t *, sigset_t *);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_sigmask (int, const sigset_t *, sigset_t *);
#endif

#ifdef _COMPILING_NEWLIB
int _kill (pid_t, int);
#endif /* _COMPILING_NEWLIB */

#if __POSIX_VISIBLE
int kill (pid_t, int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4
int killpg (pid_t, int);
#endif
#if __POSIX_VISIBLE
int sigaction (int, const struct sigaction *, struct sigaction *);
int sigaddset (sigset_t *, const int);
int sigdelset (sigset_t *, const int);
int sigismember (const sigset_t *, int);
int sigfillset (sigset_t *);
int sigemptyset (sigset_t *);
int sigpending (sigset_t *);
int sigsuspend (const sigset_t *);
int sigwait (const sigset_t *, int *);

#if !defined(__CYGWIN__) && !defined(__rtems__)
/* These depend upon the type of sigset_t, which right now 
   is always a long.. They're in the POSIX namespace, but
   are not ANSI. */
#define sigaddset(what,sig) (*(what) |= (1<<(sig)), 0)
#define sigdelset(what,sig) (*(what) &= ~(1<<(sig)), 0)
#define sigemptyset(what)   (*(what) = 0, 0)
#define sigfillset(what)    (*(what) = ~(0), 0)
#define sigismember(what,sig) (((*(what)) & (1<<(sig))) != 0)
#endif /* !__CYGWIN__ && !__rtems__ */
#endif /* __POSIX_VISIBLE */

/* There are two common sigpause variants, both of which take an int argument.
   If you request _XOPEN_SOURCE or _GNU_SOURCE, you get the System V version,
   which removes the given signal from the process's signal mask; otherwise
   you get the BSD version, which sets the process's signal mask to the given
   value. */
#if __XSI_VISIBLE && !defined(__INSIDE_CYGWIN__)
# ifdef __GNUC__
int sigpause (int) __asm__ (__ASMNAME ("__xpg_sigpause"));
# else
int __xpg_sigpause (int);
#  define sigpause __xpg_sigpause
# endif
#elif __BSD_VISIBLE
int sigpause (int);
#endif

#if __BSD_VISIBLE || __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
int sigaltstack (const stack_t *__restrict, stack_t *__restrict);
#endif

#if __POSIX_VISIBLE >= 199506
int pthread_kill (pthread_t, int);
#endif

#if __POSIX_VISIBLE >= 199309

/*  3.3.8 Synchronously Accept a Signal, P1003.1b-1993, p. 76
    NOTE: P1003.1c/D10, p. 39 adds sigwait().  */

int sigwaitinfo (const sigset_t *, siginfo_t *);
int sigtimedwait (const sigset_t *, siginfo_t *, const struct timespec *);
/*  3.3.9 Queue a Signal to a Process, P1003.1b-1993, p. 78 */
int sigqueue (pid_t, int, const union sigval);

#endif /* __POSIX_VISIBLE >= 199309 */

#ifdef __cplusplus
}
#endif

#if defined(__CYGWIN__)
#if __XSI_VISIBLE >= 4 || __POSIX_VISIBLE >= 200809
#include <sys/ucontext.h>
#endif
#endif

#ifndef _SIGNAL_H_
/* Some applications take advantage of the fact that <sys/signal.h>
 * and <signal.h> are equivalent in glibc.  Allow for that here.  */
#include <signal.h>
#endif
#endif /* _SYS_SIGNAL_H */
