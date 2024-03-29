/* utime.h -- This file is part of PML.
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

#ifndef __SYS_UTIME_H
#define __SYS_UTIME_H

struct utimbuf 
{
  time_t actime;
  time_t modtime; 
};

__BEGIN_DECLS

int utime (const char *path, const struct utimbuf *times);

__END_DECLS

#endif /* _SYS_UTIME_H */
