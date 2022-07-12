/* dirent.h -- This file is part of PML.
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

#ifndef __SYS_DIRENT_H
#define __SYS_DIRENT_H

#include <pml/dirent.h>

struct __DIR
{
  int dd_fd;
  void *dd_buf;
  size_t dd_len;
  size_t dd_size;
  off_t dd_loc;
  off_t dd_seek;
};

typedef struct __DIR DIR;

#define __dirfd(dp)             ((dp)->dd_fd)

#endif
