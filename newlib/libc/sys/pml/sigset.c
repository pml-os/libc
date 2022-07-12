/* sigset.c -- This file is part of PML.
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

#include <signal.h>

int
sigemptyset (sigset_t *set)
{
  *set = 0;
  return 0;
}

int
sigfillset (sigset_t *set)
{
  *set = 0xffffffffffffffffUL;
  return 0;
}

int
sigaddset (sigset_t *set, int sig)
{
  *set |= 1UL << (NSIG - sig);
  return 0;
}

int
sigdelset (sigset_t *set, int sig)
{
  *set &= ~(1UL << (NSIG - sig));
  return 0;
}

int
sigismember (const sigset_t *set, int sig)
{
  return !!(*set & (1UL << (NSIG - sig)));
}
