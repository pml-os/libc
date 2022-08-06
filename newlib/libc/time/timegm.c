/*
 * timegm.c
 * Original Author:	G. Haley
 *
 * Converts the broken-down time, expressed as UTC time, in the structure
 * pointed to by tim_p into a calendar time value. The original values of the
 * tm_wday and tm_yday fields of the structure are ignored, and the original
 * values of the other fields have no restrictions. On successful completion
 * the fields of the structure are set to represent the specified calendar
 * time. Returns the specified calendar time. If the calendar time can not be
 * represented, returns the value (time_t) -1.
 *
 * Modifications:	Fixed tm_isdst usage - 27 August 2008 Craig Howland.
 *                        Refactored mktime.c to support both mktime and timegm
 *                             - 23 July 2018 Andrew Russell.
 */

/*
FUNCTION
<<timegm>>---convert time to arithmetic representation

INDEX
	timegm

SYNOPSIS
	#include <time.h>
	time_t timegm(struct tm *<[timp]>);

DESCRIPTION
<<timegm>> assumes the time at <[timp]> is UTC time, and converts
its representation from the traditional representation defined by
<<struct tm>> into a representation suitable for arithmetic.

<<gmtime>> is the inverse of <<timegm>>.

RETURNS
If the contents of the structure at <[timp]> do not form a valid
calendar time representation, the result is <<-1>>.  Otherwise, the
result is the time, converted to a <<time_t>> value.

PORTABILITY
ANSI C requires <<timegm>>.

<<timegm>> requires no supporting OS subroutines.
*/

#include <stdlib.h>
#include <time.h>
#include "local.h"

#define _SEC_IN_MINUTE 60L
#define _SEC_IN_HOUR 3600L
#define _SEC_IN_DAY 86400L

static const int DAYS_IN_MONTH[12] =
{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#define _DAYS_IN_MONTH(x) ((x == 1) ? days_in_feb : DAYS_IN_MONTH[x])

static const int _DAYS_BEFORE_MONTH[12] =
{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};

void
__validate_tm_structure (struct tm *tim_p)
{
  div_t res;
  int days_in_feb = 28;

  /* calculate time & date to account for out of range values */
  if (tim_p->tm_sec < 0 || tim_p->tm_sec > 59)
    {
      res = div (tim_p->tm_sec, 60);
      tim_p->tm_min += res.quot;
      if ((tim_p->tm_sec = res.rem) < 0)
	{
	  tim_p->tm_sec += 60;
	  --tim_p->tm_min;
	}
    }

  if (tim_p->tm_min < 0 || tim_p->tm_min > 59)
    {
      res = div (tim_p->tm_min, 60);
      tim_p->tm_hour += res.quot;
      if ((tim_p->tm_min = res.rem) < 0)
	{
	  tim_p->tm_min += 60;
	  --tim_p->tm_hour;
        }
    }

  if (tim_p->tm_hour < 0 || tim_p->tm_hour > 23)
    {
      res = div (tim_p->tm_hour, 24);
      tim_p->tm_mday += res.quot;
      if ((tim_p->tm_hour = res.rem) < 0)
	{
	  tim_p->tm_hour += 24;
	  --tim_p->tm_mday;
        }
    }

  if (tim_p->tm_mon < 0 || tim_p->tm_mon > 11)
    {
      res = div (tim_p->tm_mon, 12);
      tim_p->tm_year += res.quot;
      if ((tim_p->tm_mon = res.rem) < 0)
        {
	  tim_p->tm_mon += 12;
	  --tim_p->tm_year;
        }
    }

  if (__days_in_year(tim_p->tm_year) == 366)
    days_in_feb = 29;

  if (tim_p->tm_mday <= 0)
    {
      while (tim_p->tm_mday <= 0)
	{
	  if (--tim_p->tm_mon == -1)
	    {
	      tim_p->tm_year--;
	      tim_p->tm_mon = 11;
	      days_in_feb =
		((__days_in_year(tim_p->tm_year) == 366) ?
		 29 : 28);
	    }
	  tim_p->tm_mday += _DAYS_IN_MONTH (tim_p->tm_mon);
	}
    }
  else
    {
      while (tim_p->tm_mday > _DAYS_IN_MONTH (tim_p->tm_mon))
	{
	  tim_p->tm_mday -= _DAYS_IN_MONTH (tim_p->tm_mon);
	  if (++tim_p->tm_mon == 12)
	    {
	      tim_p->tm_year++;
	      tim_p->tm_mon = 0;
	      days_in_feb =
		((__days_in_year (tim_p->tm_year) == 366) ?
		 29 : 28);
	    }
	}
    }
}

void
__set_tm_wday (long days, struct tm *tim_p)
{
  if ((tim_p->tm_wday = (days + 4) % 7) < 0)
    tim_p->tm_wday += 7;
}

static int
__is_leap_year (int year)
{
  return (year % 4) == 0
    && ((year % 100) != 0 || (((year / 100) & 3) == (-(YEAR_BASE / 100) & 3)));
}

int
__days_in_year (int year)
{
  return __is_leap_year(year) ? 366 : 365;
}

time_t 
__timegm_internal (struct tm *tim_p)
{
  time_t tim = 0;
  long days = 0;
  int year, isdst=0;
  __tzinfo_type *tz = __gettzinfo ();

  /* validate structure */
  __validate_tm_structure (tim_p);

  /* compute hours, minutes, seconds */
  tim += tim_p->tm_sec + (tim_p->tm_min * _SEC_IN_MINUTE) +
    (tim_p->tm_hour * _SEC_IN_HOUR);

  /* compute days in year */
  days += tim_p->tm_mday - 1;
  days += _DAYS_BEFORE_MONTH[tim_p->tm_mon];
  if (tim_p->tm_mon > 1 && __days_in_year(tim_p->tm_year) == 366)
    days++;

  /* compute day of the year */
  tim_p->tm_yday = days;

  if (tim_p->tm_year > 10000 || tim_p->tm_year < -10000)
      return (time_t) -1;

  /* compute days in other years */
  if ((year = tim_p->tm_year) > 70)
    {
      for (year = 70; year < tim_p->tm_year; year++)
	days += __days_in_year(year);
    }
  else if (year < 70)
    {
      for (year = 69; year > tim_p->tm_year; year--)
	days -= __days_in_year (year);
      days -= __days_in_year (year);
    }

  /* compute total seconds */
  tim += (time_t)days * _SEC_IN_DAY;


  return tim;
}

time_t
timegm (struct tm *tim_p)
{
  time_t tim = __timegm_internal(tim_p);
  long days = tim / SECSPERDAY;

  /* set isdst flag to 0 since we are in UTC */
  tim_p->tm_isdst = 0;

  /* compute day of the week */
  __set_tm_wday(days, tim_p);

  return tim;
}
