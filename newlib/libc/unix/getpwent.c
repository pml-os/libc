/* passwd.c -- This file is part of OS/0 libc.
   Copyright (C) 2021 XNSC

   OS/0 libc is free software: you can redistribute it and/or modify
   it under the terms of the GNU Lesser General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   OS/0 libc is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
   GNU Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public License
   along with OS/0 libc. If not, see <https://www.gnu.org/licenses/>. */

#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PASSWD_FILE     "/etc/passwd"
#define GROUP_FILE      "/etc/groups"
#define PASSWD_BUFSIZ   512
#define GROUP_BUFSIZ    512

static struct group __libc_group;
static FILE *__libc_getgrent_stream;
static char __libc_grpbuf[GROUP_BUFSIZ];

static struct passwd __libc_passwd;
static FILE *__libc_getpwent_stream;
static char __libc_pwbuf[PASSWD_BUFSIZ];

static struct passwd *
__getpwent (struct passwd *__restrict result, FILE *__restrict stream,
	    char *__restrict buffer, size_t len)
{
  char *ptr;
  if (fgets (buffer, len, stream) == NULL)
    return NULL;
  if (buffer[strlen (buffer) - 1] != '\n')
    {
      /* Not enough space in buffer to read entire line */
      errno = ERANGE;
      return NULL;
    }
  else
    buffer[strlen (buffer) - 1] = '\0';

  result->pw_name = buffer;
  ptr = strchr (buffer, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->pw_passwd = ptr + 1;
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->pw_uid = atoi (ptr + 1);
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->pw_gid = atoi (ptr + 1);
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->pw_gecos = ptr + 1;
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->pw_dir = ptr + 1;
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';
  result->pw_shell = ptr + 1;
  return result;
}

struct passwd *
getpwnam (const char *name)
{
  struct passwd *pwd;
  if (getpwnam_r (name, &__libc_passwd, __libc_pwbuf, PASSWD_BUFSIZ, &pwd)
      == -1)
    return NULL;
  return pwd;
}

struct passwd *
getpwuid (uid_t uid)
{
  struct passwd *pwd;
  if (getpwuid_r (uid, &__libc_passwd, __libc_pwbuf, PASSWD_BUFSIZ, &pwd)
      == -1)
    return NULL;
  return pwd;
}

int
getpwnam_r (const char *__restrict name, struct passwd *__restrict pwd,
	    char *__restrict buffer, size_t len,
	    struct passwd **__restrict result)
{
  FILE *file = fopen (PASSWD_FILE, "r");
  if (file == NULL)
    {
      errno = ENOENT;
      *result = NULL;
      return -1;
    }
  while (1)
    {
      if (__getpwent (pwd, file, buffer, len) == NULL)
	{
	  fclose (file);
	  *result = NULL;
	  return -1;
	}
      if (strcmp (pwd->pw_name, name) == 0)
	break;
    }
  fclose (file);
  *result = pwd;
  return 0;
}

int
getpwuid_r (uid_t uid, struct passwd *__restrict pwd, char *__restrict buffer,
	    size_t len, struct passwd **__restrict result)
{
  FILE *file = fopen (PASSWD_FILE, "r");
  if (file == NULL)
    {
      errno = ENOENT;
      *result = NULL;
      return -1;
    }
  while (1)
    {
      if (__getpwent (pwd, file, buffer, len) == NULL)
	{
	  fclose (file);
	  *result = NULL;
	  return -1;
	}
      if (pwd->pw_uid == uid)
	break;
    }
  fclose (file);
  *result = pwd;
  return 0;
}

void
setpwent (void)
{
  if (__libc_getpwent_stream != NULL)
    rewind (__libc_getpwent_stream);
}

struct passwd *
getpwent (void)
{
  if (__libc_getpwent_stream == NULL)
    {
      __libc_getpwent_stream = fopen (PASSWD_FILE, "r");
      if (__libc_getpwent_stream == NULL)
	{
	  errno = ENOENT;
	  return NULL;
	}
    }
  return __getpwent (&__libc_passwd, __libc_getpwent_stream, __libc_pwbuf,
		     PASSWD_BUFSIZ);
}

void
endpwent (void)
{
  if (__libc_getpwent_stream != NULL)
    {
      fclose (__libc_getpwent_stream);
      __libc_getpwent_stream = NULL;
    }
}

static struct group *
__getgrent (struct group *__restrict result, FILE *__restrict stream,
	    char *__restrict buffer, size_t len)
{
  char *base;
  char *ptr;
  int i = 0;
  if (fgets (buffer, len, stream) == NULL)
    return NULL;
  if (buffer[strlen (buffer) - 1] != '\n')
    {
      /* Not enough space in buffer to read entire line */
      errno = ERANGE;
      return NULL;
    }
  else
    buffer[strlen (buffer) - 1] = '\0';

  result->gr_name = buffer;
  ptr = strchr (buffer, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  result->gr_gid = atoi (ptr + 1);
  ptr = strchr (ptr + 1, ':');
  if (ptr == NULL)
    return NULL;
  *ptr = '\0';

  while (i < __gr_mem_limit)
    {
      base = ptr + 1;
      ptr = strchr (base, ',');
      if (ptr != NULL)
	*ptr = '\0';
      result->__gr_memv[i++] = base;
      if (ptr == NULL)
	break;
    }
  result->gr_mem = result->__gr_memv;
  return result;
}

struct group *
getgrgid (gid_t gid)
{
  struct group *grp;
  if (getgrgid_r (gid, &__libc_group, __libc_grpbuf, GROUP_BUFSIZ, &grp)
      == -1)
    return NULL;
  return grp;
}

struct group *
getgrnam (const char *name)
{
  struct group *grp;
  if (getgrnam_r (name, &__libc_group, __libc_grpbuf, GROUP_BUFSIZ, &grp)
      == -1)
    return NULL;
  return grp;
}

int
getgrgid_r (gid_t gid, struct group *__restrict grp, char *__restrict buffer,
	    size_t len, struct group **__restrict result)
{
  FILE *file = fopen (GROUP_FILE, "r");
  if (file == NULL)
    {
      errno = ENOENT;
      *result = NULL;
      return -1;
    }
  while (1)
    {
      if (__getgrent (grp, file, buffer, len) == NULL)
	{
	  fclose (file);
	  *result = NULL;
	  return -1;
	}
      if (grp->gr_gid == gid)
	break;
    }
  fclose (file);
  *result = grp;
  return 0;
}

int
getgrnam_r (const char *__restrict name, struct group *__restrict grp,
	    char *__restrict buffer, size_t len,
	    struct group **__restrict result)
{
  FILE *file = fopen (GROUP_FILE, "r");
  if (file == NULL)
    {
      errno = ENOENT;
      *result = NULL;
      return -1;
    }
  while (1)
    {
      if (__getgrent (grp, file, buffer, len) == NULL)
	{
	  fclose (file);
	  *result = NULL;
	  return -1;
	}
      if (strcmp (grp->gr_name, name) == 0)
	break;
    }
  fclose (file);
  *result = grp;
  return 0;
}

void
setgrent (void)
{
  if (__libc_getgrent_stream != NULL)
    rewind (__libc_getgrent_stream);
}

struct group *
getgrent (void)
{
  if (__libc_getgrent_stream == NULL)
    {
      __libc_getgrent_stream = fopen (GROUP_FILE, "r");
      if (__libc_getgrent_stream == NULL)
	{
	  errno = ENOENT;
	  return NULL;
	}
    }
  return __getgrent (&__libc_group, __libc_getgrent_stream, __libc_grpbuf,
		     GROUP_BUFSIZ);
}

void
endgrent (void)
{
  if (__libc_getgrent_stream != NULL)
    {
      fclose (__libc_getgrent_stream);
      __libc_getgrent_stream = NULL;
    }
}

int
getgrouplist (const char *user, gid_t group, gid_t *groups, int *ngroups)
{
  FILE *file = fopen (GROUP_FILE, "r");
  char *buffer = malloc (GROUP_BUFSIZ);
  struct group g;
  size_t count = 0;
  int fail = 0;
  if (*ngroups > 0)
    groups[count++] = group;
  if (file == NULL || buffer == NULL)
    return *ngroups;

  while (1)
    {
      size_t i;
      if (__getgrent (&g, file, buffer, GROUP_BUFSIZ) == NULL)
	break;
      for (i = 0; g.gr_mem[i] != NULL; i++)
	{
	  if (strcmp (g.gr_mem[i], user) == 0)
	    {
	      if (count >= *ngroups)
		fail = 1;
	      if (!fail && g.gr_gid != groups[0])
		groups[count++] = g.gr_gid;
	      break;
	    }
	}
    }
  free (buffer);
  if (ferror (file))
    {
      fclose (file);
      return *ngroups;
    }
  fclose (file);

  if (fail)
    {
      errno = ERANGE;
      *ngroups = count;
      return -1;
    }
  return 0;
}
