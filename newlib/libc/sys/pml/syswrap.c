/* syswrap.c -- This file is part of PML.
   Copyright (C) 2021 XNSC

   PML is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   PML is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with PML. If not, see <https://www.gnu.org/licenses/>. */

#include <pml/fcntl.h>
#include <pml/syscall.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

long do_syscall (long num, ...);

pid_t
fork (void)
{
  return do_syscall (SYS_fork);
}

pid_t
vfork (void)
{
  return do_syscall (SYS_vfork);
}

pid_t
getpid (void)
{
  return do_syscall (SYS_getpid);
}

pid_t
getppid (void)
{
  return do_syscall (SYS_getppid);
}

pid_t
gettid (void)
{
  return do_syscall (SYS_gettid);
}

pid_t
getpgid (pid_t pid)
{
  return do_syscall (SYS_getpgid, pid);
}

int
setpgid (pid_t pid, pid_t pgid)
{
  return do_syscall (SYS_setpgid, pid, pgid);
}

pid_t
getpgrp (void)
{
  return do_syscall (SYS_getpgrp);
}

int
setpgrp (void)
{
  return do_syscall (SYS_setpgrp);
}

uid_t
getuid (void)
{
  return do_syscall (SYS_getuid);
}

int
setuid (uid_t uid)
{
  return do_syscall (SYS_setuid, uid);
}

uid_t
geteuid (void)
{
  return do_syscall (SYS_geteuid);
}

int
seteuid (uid_t euid)
{
  return do_syscall (SYS_seteuid, euid);
}

int
setreuid (uid_t ruid, uid_t euid)
{
  return do_syscall (SYS_setreuid, ruid, euid);
}

int
getresuid (uid_t *ruid, uid_t *euid, uid_t *suid)
{
  return do_syscall (SYS_getresuid, ruid, euid, suid);
}

int
setresuid (uid_t ruid, uid_t euid, uid_t suid)
{
  return do_syscall (SYS_setresuid, ruid, euid, suid);
}

gid_t
getgid (void)
{
  return do_syscall (SYS_getgid);
}

int
setgid (gid_t gid)
{
  return do_syscall (SYS_setgid, gid);
}

gid_t
getegid (void)
{
  return do_syscall (SYS_getegid);
}

int
setegid (gid_t egid)
{
  return do_syscall (SYS_setegid, egid);
}

int
setregid (gid_t rgid, gid_t egid)
{
  return do_syscall (SYS_setregid, rgid, egid);
}

int
getresgid (gid_t *rgid, gid_t *egid, gid_t *sgid)
{
  return do_syscall (SYS_getresgid, rgid, egid, sgid);
}

int
setresgid (gid_t rgid, gid_t egid, gid_t sgid)
{
  return do_syscall (SYS_setresgid, rgid, egid, sgid);
}

int
getgroups (int size, gid_t *list)
{
  return do_syscall (SYS_getgroups, size, list);
}

int
setgroups (size_t size, const gid_t *list)
{
  return do_syscall (SYS_setgroups, size, list);
}

int
_execve (const char *name, char *const *argv, char *const *envp)
{
  return do_syscall (SYS_execve, name, argv, envp);
}

void
_exit (int status)
{
  do_syscall (SYS_exit, status);
}

int
brk (void *addr)
{
  return do_syscall (SYS_brk, addr);
}

void *
sbrk (ptrdiff_t incr)
{
  return (void *) do_syscall (SYS_sbrk, incr);
}

mode_t
umask (mode_t mask)
{
  return do_syscall (SYS_umask, mask);
}

int
open (const char *name, int flags, mode_t mode)
{
  return do_syscall (SYS_open, name, flags, mode);
}

int
close (int fd)
{
  return do_syscall (SYS_close, fd);
}

ssize_t
read (int fd, void *buffer, size_t len)
{
  return do_syscall (SYS_read, fd, buffer, len);
}

ssize_t
write (int fd, const void *buffer, size_t len)
{
  return do_syscall (SYS_write, fd, buffer, len);
}

off_t
lseek (int fd, off_t offset, int whence)
{
  return do_syscall (SYS_lseek, fd, offset, whence);
}

int
stat (const char *path, struct stat *st)
{
  return do_syscall (SYS_stat, path, st);
}

int
fstat (int fd, struct stat *st)
{
  return do_syscall (SYS_fstat, fd, st);
}

int
lstat (const char *path, struct stat *st)
{
  return do_syscall (SYS_lstat, path, st);
}

int
mkdir (const char *path, mode_t mode)
{
  return do_syscall (SYS_mkdir, path, mode);
}

int
_rename (const char *old_path, const char *new_path)
{
  return do_syscall (SYS_rename, old_path, new_path);
}

int
link (const char *old_path, const char *new_path)
{
  return do_syscall (SYS_link, old_path, new_path);
}

int
unlink (const char *path)
{
  return do_syscall (SYS_unlink, path);
}

int
symlink (const char *old_path, const char *new_path)
{
  return do_syscall (SYS_symlink, old_path, new_path);
}

ssize_t
readlink (const char *path, char *buffer, size_t len)
{
  return do_syscall (SYS_readlink, path, buffer, len);
}

int
truncate (const char *path, off_t len)
{
  return do_syscall (SYS_truncate, path, len);
}

void
sync (void)
{
  do_syscall (SYS_sync);
}

int
fsync (int fd)
{
  return do_syscall (SYS_fsync, fd);
}

int
chdir (const char *path)
{
  return do_syscall (SYS_chdir, path);
}

int
fchdir (int fd)
{
  return do_syscall (SYS_fchdir, fd);
}

ssize_t
getdents (int fd, void *dirp, size_t len)
{
  return do_syscall (SYS_getdents, fd, dirp, len);
}

int
dup (int fd)
{
  return do_syscall (SYS_dup, fd);
}

int
pipe (int fds[2])
{
  return do_syscall (SYS_pipe, fds);
}

int
fcntl (int fd, int cmd, void *arg)
{
  return do_syscall (SYS_fcntl, fd, cmd, arg);
}

int
dup2 (int fd, int fd2)
{
  int save;
  if (fd2 < 0 || fd2 >= OPEN_MAX)
    {
      errno = EBADF;
      return -1;
    }
  if (fcntl (fd, F_GETFL, NULL) < 0)
    return -1;
  if (fd == fd2)
    return fd2;
  save = errno;
  close (fd2);
  errno = save;
  return fcntl (fd, F_DUPFD, (void *) (long) fd2);
}

int
ioctl (int fd, unsigned long req, void *arg)
{
  return do_syscall (SYS_ioctl, fd, req, arg);
}

void *
mmap (void *addr, size_t len, int prot, int flags, int fd, off_t offset)
{
  return (void *) do_syscall (SYS_mmap, addr, len, prot, flags, fd, offset);
}

int
munmap (void *addr, size_t len)
{
  return do_syscall (SYS_munmap, addr, len);
}

int
msync (void *addr, size_t len, int flags)
{
  return do_syscall (SYS_msync, addr, len, flags);
}

int
getrusage (int who, struct rusage *rusage)
{
  return do_syscall (SYS_getrusage, who, rusage);
}

pid_t
wait (int *status)
{
  return wait4 (-1, status, 0, NULL);
}

pid_t
wait3 (int *status, int flags, struct rusage *rusage)
{
  return wait4 (-1, status, flags, rusage);
}

pid_t
wait4 (pid_t pid, int *status, int flags, struct rusage *rusage)
{
  return do_syscall (SYS_wait4, pid, status, flags, rusage);
}

pid_t
waitpid (pid_t pid, int *status, int flags)
{
  return wait4 (pid, status, flags, NULL);
}

sighandler_t
signal (int sig, sighandler_t handler)
{
  return (sighandler_t) do_syscall (SYS_signal, sig, handler);
}

int
sigaction (int sig, const struct sigaction *act, struct sigaction *old_act)
{
  return do_syscall (SYS_sigaction, sig, act, old_act);
}

int
sigprocmask (int how, const sigset_t *set, sigset_t *old_set)
{
  return do_syscall (SYS_sigprocmask, how, set, old_set);
}

int
nanosleep (const struct timespec *req, struct timespec *rem)
{
  return do_syscall (SYS_nanosleep, req, rem);
}

int
pause (void)
{
  return do_syscall (SYS_pause);
}

int
sigsuspend (const sigset_t *mask)
{
  return do_syscall (SYS_sigsuspend, mask);
}

int
kill (pid_t pid, int sig)
{
  return do_syscall (SYS_kill, pid, sig);
}

int
killpg (pid_t pgrp, int sig)
{
  return do_syscall (SYS_killpg, pgrp, sig);
}
