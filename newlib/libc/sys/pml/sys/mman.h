/* mman.h -- This file is part of PML.
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

#ifndef __SYS_MMAN_H
#define __SYS_MMAN_H

#include <pml/mman.h>
#include <pml/types.h>
#include <sys/cdefs.h>

__BEGIN_DECLS

void *mmap (void *addr, size_t len, int prot, int flags, int fd, off_t offset);
int munmap (void *addr, size_t len);
int msync (void *addr, size_t len, int flags);

__END_DECLS

#endif
