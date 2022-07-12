/* termios.h -- This file is part of PML.
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

#ifndef __SYS_TERMIOS_H
#define __SYS_TERMIOS_H

#include <pml/termios.h>

speed_t cfgetispeed (const struct termios *tp);
speed_t cfgetospeed (const struct termios *tp);
int cfsetispeed (struct termios *tp, speed_t speed);
int cfsetospeed (struct termios *tp, speed_t speed);
int tcdrain (int fd);
int tcflow (int fd, int action);
int tcflush (int fd, int action);
int tcsendbreak (int fd, int duration);

int tcgetattr (int fd, struct termios *tp);
int tcsetattr (int fd, int action, const struct termios *tp);
pid_t tcgetpgrp (int fd);
int tcsetpgrp (int fd, pid_t pgid);
pid_t tcgetsid (int fd);

#endif
