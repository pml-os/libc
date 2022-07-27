/* utmp.h -- This file is part of PML.
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

#ifndef __SYS_UTMP_H
#define __SYS_UTMP_H

#include <pml/time.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#define _PATH_UTMP              "/var/run/utmp"
#define _PATH_WTMP              "/var/log/wtmp"
#define UTMP_FILE               _PATH_UTMP

#define UT_LINESIZE	32
#define UT_NAMESIZE	32
#define UT_HOSTSIZE	256

struct exit_status
{
  short e_termination;
  short e_exit;
};

struct utmp
{
  short int ut_type;
  pid_t ut_pid;
  char ut_line[UT_LINESIZE];
  char ut_id[4];
  char ut_user[UT_NAMESIZE];
  char ut_host[UT_HOSTSIZE];
  struct exit_status ut_exit;
  long ut_session;
  struct timeval ut_tv;
  int32_t ut_addr_v6[4];
  char __filler[20];
};

#define ut_name                 ut_user
#define ut_time                 ut_tv.tv_sec
#define ut_xtime                ut_tv.tv_sec
#define ut_addr                 ut_addr_v6[0]

#define RUN_LVL		        1
#define BOOT_TIME	        2
#define NEW_TIME	        3
#define OLD_TIME	        4
#define INIT_PROCESS	        5
#define LOGIN_PROCESS	        6
#define USER_PROCESS	        7
#define DEAD_PROCESS	        8

__BEGIN_DECLS

struct utmp *_getutline (struct utmp *);
struct utmp *getutent (void);
struct utmp *getutid (struct utmp *);
struct utmp *getutline (struct utmp *);
void endutent (void);
void pututline (struct utmp *);
void setutent (void);
void utmpname (const char *);

__END_DECLS

#endif
