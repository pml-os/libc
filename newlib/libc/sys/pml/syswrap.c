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

#include <pml/syscall.h>

long do_syscall (long num, ...);

void
_exit (int status)
{
  do_syscall (SYS_exit, status);
}

int
close (int fd)
{
  return do_syscall (SYS_close, fd);
}

int
execve (const char *name, char *const *argv, char *const *envp)
{
  return do_syscall (SYS_execve, name, argv, envp);
}

pid_t
fork (void)
{
  return do_syscall (SYS_fork);
}

pid_t
getpid (void)
{
  return do_syscall (SYS_getpid);
}

int
open (const char *name, int flags, mode_t mode)
{
  return do_syscall (SYS_open, name, flags, mode);
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
link (const char *old_path, const char *new_path)
{
  return do_syscall (SYS_link, old_path, new_path);
}

int
dup (int fd)
{
  return do_syscall (SYS_dup, fd);
}
