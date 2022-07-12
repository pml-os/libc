/* termios.c -- This file is part of PML.
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

#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>
#include <termios.h>

speed_t
cfgetispeed (const struct termios *tp)
{
  return tp->c_cflag & (CBAUD | CBAUDEX);
}

speed_t
cfgetospeed (const struct termios *tp)
{
  return tp->c_cflag & (CBAUD | CBAUDEX);
}

int
cfsetispeed (struct termios *tp, speed_t speed)
{
  if ((speed & ~CBAUD) && (speed < B57600 || speed > B4000000))
    {
      errno = EINVAL;
      return -1;
    }
  tp->c_cflag &= ~(CBAUD | CBAUDEX);
  tp->c_cflag |= speed;
  return 0;
}

int
cfsetospeed (struct termios *tp, speed_t speed)
{
  if ((speed & ~CBAUD) && (speed < B57600 || speed > B4000000))
    {
      errno = EINVAL;
      return -1;
    }
  tp->c_cflag &= ~(CBAUD | CBAUDEX);
  tp->c_cflag |= speed;
  return 0;
}

int
tcdrain (int fd)
{
  return 0; /* TODO Implement? */
}

int
tcflow (int fd, int action)
{
  return ioctl (fd, TCXONC, (void *) (long) action);
}

int
tcflush (int fd, int action)
{
  return ioctl (fd, TCFLSH, (void *) (long) action);
}

int
tcsendbreak (int fd, int duration)
{
  return ioctl (fd, TCSBRK, (void *) (long) duration);
}

int
tcgetattr (int fd, struct termios *tp)
{
  return ioctl (fd, TCGETS, tp);
}

int
tcsetattr (int fd, int action, const struct termios *tp)
{
  switch (action)
    {
    case TCSANOW:
      return ioctl (fd, TCSETS, tp);
    case TCSADRAIN:
      return ioctl (fd, TCSETSW, tp);
    case TCSAFLUSH:
      return ioctl (fd, TCSETSF, tp);
    default:
      errno = EINVAL;
      return -1;
    }
}

pid_t
tcgetpgrp (int fd)
{
  pid_t arg;
  if (ioctl (fd, TIOCGPGRP, &arg) == -1)
    return -1;
  return arg;
}

int
tcsetpgrp (int fd, pid_t pgid)
{
  return ioctl (fd, TIOCSPGRP, &pgid);
}

pid_t
tcgetsid (int fd)
{
  pid_t arg;
  if (ioctl (fd, TIOCGSID, &arg) == -1)
    return -1;
  return arg;
}
