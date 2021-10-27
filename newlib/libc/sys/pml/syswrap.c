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
execve (char *name, char **argv, char **envp)
{
  return do_syscall (SYS_execve, name, argv, envp);
}

int
fork (void)
{
  return do_syscall (SYS_fork);
}

int
getpid (void)
{
  return do_syscall (SYS_getpid);
}

int
open (const char *name, int flags, int mode)
{
  return do_syscall (SYS_open);
}

int
read (int fd, char *buffer, int len)
{
  return do_syscall (SYS_read, fd, buffer, len);
}

int
write (int fd, char *buffer, int len)
{
  return do_syscall (SYS_write, fd, buffer, len);
}
