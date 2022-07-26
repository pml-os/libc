/* err.h -- This file is part of PML.
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

#ifndef __ERR_H
#define __ERR_H

#include <stdarg.h>

void vwarn (const char *fmt, va_list args);
void vwarnx (const char *fmt, va_list args);
void warn (const char *fmt, ...);
void warnx (const char *fmt, ...);
void verr (int status, const char *fmt, va_list args);
void verrx (int status, const char *fmt, va_list args);
void err (int status, const char *fmt, ...);
void errx (int status, const char *fmt, ...);

#endif
