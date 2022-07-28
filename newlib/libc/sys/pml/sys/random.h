/* random.h -- This file is part of PML.
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

#ifndef __SYS_RANDOM_H
#define __SYS_RANDOM_H

#include <pml/random.h>
#include <sys/cdefs.h>
#include <sys/types.h>

__BEGIN_DECLS

ssize_t getrandom (void *buffer, size_t len, unsigned int flags);
int getentropy (void *buffer, size_t len);

__END_DECLS

#endif
