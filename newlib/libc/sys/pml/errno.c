/* errno.c -- This file is part of PML.
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

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

char *__progname;

void
__set_errno (int e)
{
  errno = e;
}

void
vwarn (const char *fmt, va_list args)
{
  int error = errno;
  if (fmt)
    {
      fprintf (stderr, "%s: ", __progname);
      vfprintf (stderr, fmt, args);
      errno = error;
      fprintf (stderr, ": %s\n", strerror (errno));
    }
  else
    fprintf (stderr, "%s: %s\n", __progname, strerror (errno));
}

void
vwarnx (const char *fmt, va_list args)
{
  fprintf (stderr, "%s: ", __progname);
  if (fmt)
    vfprintf (stderr, fmt, args);
  fprintf (stderr, "\n");
}

void
warn (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vwarn (fmt, args);
  va_end (args);
}

void
warnx (const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  vwarnx (fmt, args);
  va_end (args);
}

void
verr (int status, const char *fmt, va_list args)
{
  vwarn (fmt, args);
  exit (status);
}

void
verrx (int status, const char *fmt, va_list args)
{
  vwarnx (fmt, args);
  exit (status);
}

void
err (int status, const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  verr (status, fmt, args);
  va_end (args);
}

void
errx (int status, const char *fmt, ...)
{
  va_list args;
  va_start (args, fmt);
  verrx (status, fmt, args);
  va_end (args);
}
