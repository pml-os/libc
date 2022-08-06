/*
 * mktime.c
 * Original Author:	G. Haley
 *
 * Converts the broken-down time, expressed as local time, in the structure
 * pointed to by tim_p into a calendar time value. The original values of the
 * tm_wday and tm_yday fields of the structure are ignored, and the original
 * values of the other fields have no restrictions. On successful completion
 * the fields of the structure are set to represent the specified calendar
 * time. Returns the specified calendar time. If the calendar time can not be
 * represented, returns the value (time_t) -1.
 *
 * Modifications:	Fixed tm_isdst usage - 27 August 2008 Craig Howland.
 *                            Refactor code from mktime.c to shared internal
 *                            functions. - 17 July 2018 Andrew Russell.
 */

/*
FUNCTION
<<mktime>>---convert time to arithmetic representation

INDEX
	mktime

SYNOPSIS
	#include <time.h>
	time_t mktime(struct tm *<[timp]>);

DESCRIPTION
<<mktime>> assumes the time at <[timp]> is a local time, and converts
its representation from the traditional representation defined by
<<struct tm>> into a representation suitable for arithmetic.

<<localtime>> is the inverse of <<mktime>>.

RETURNS
If the contents of the structure at <[timp]> do not form a valid
calendar time representation, the result is <<-1>>.  Otherwise, the
result is the time, converted to a <<time_t>> value.

PORTABILITY
ANSI C requires <<mktime>>.

<<mktime>> requires no supporting OS subroutines.
*/

#include <stdlib.h>
#include <time.h>
#include "local.h"

time_t 
mktime (struct tm *tim_p)
{
  time_t tim = __timegm_internal(tim_p);
  long days = tim / SECSPERDAY;
  int year = tim_p->tm_year;
  int isdst=0;
  __tzinfo_type *tz = __gettzinfo ();

  TZ_LOCK;

  _tzset_unlocked ();

  if (_daylight)
    {
      int tm_isdst;
      int y = tim_p->tm_year + YEAR_BASE;
      /* Convert user positive into 1 */
      tm_isdst = tim_p->tm_isdst > 0  ?  1 : tim_p->tm_isdst;
      isdst = tm_isdst;

      if (y == tz->__tzyear || __tzcalc_limits (y))
	{
	  /* calculate start of dst in dst local time and 
	     start of std in both std local time and dst local time */
          time_t startdst_dst = tz->__tzrule[0].change
	    - (time_t) tz->__tzrule[1].offset;
	  time_t startstd_dst = tz->__tzrule[1].change
	    - (time_t) tz->__tzrule[1].offset;
	  time_t startstd_std = tz->__tzrule[1].change
	    - (time_t) tz->__tzrule[0].offset;
	  /* if the time is in the overlap between dst and std local times */
	  if (tim >= startstd_std && tim < startstd_dst)
	    ; /* we let user decide or leave as -1 */
          else
	    {
	      isdst = (tz->__tznorth
		       ? (tim >= startdst_dst && tim < startstd_std)
		       : (tim >= startdst_dst || tim < startstd_std));
 	      /* if user committed and was wrong, perform correction, but not
 	       * if the user has given a negative value (which
 	       * asks mktime() to determine if DST is in effect or not) */
 	      if (tm_isdst >= 0  &&  (isdst ^ tm_isdst) == 1)
		{
		  /* we either subtract or add the difference between
		     time zone offsets, depending on which way the user got it
		     wrong. The diff is typically one hour, or 3600 seconds,
		     and should fit in a 16-bit int, even though offset
		     is a long to accomodate 12 hours. */
		  int diff = (int) (tz->__tzrule[0].offset
				    - tz->__tzrule[1].offset);
		  if (!isdst)
		    diff = -diff;
		  tim_p->tm_sec += diff;
		  tim += diff;  /* we also need to correct our current time calculation */
		  int mday = tim_p->tm_mday;
		  __validate_tm_structure (tim_p);
		  mday = tim_p->tm_mday - mday;
		  /* roll over occurred */
		  if (mday) {
		    /* compensate for month roll overs */
		    if (mday > 1)
			  mday = -1;
		    else if (mday < -1)
			  mday = 1;
		    /* update days for wday calculation */
		    days += mday;
		    /* handle yday */
		    if ((tim_p->tm_yday += mday) < 0) {
			  --year;
			  tim_p->tm_yday = __days_in_year(year) - 1;
		    } else {
			  mday = __days_in_year(year);
			  if (tim_p->tm_yday > (mday - 1))
				tim_p->tm_yday -= mday;
		    }
		  }
		}
	    }
	}
    }

  /* add appropriate offset to put time in gmt format */
  if (isdst == 1)
    tim += (time_t) tz->__tzrule[1].offset;
  else /* otherwise assume std time */
    tim += (time_t) tz->__tzrule[0].offset;

  TZ_UNLOCK;

  /* reset isdst flag to what we have calculated */
  tim_p->tm_isdst = isdst;

  /* compute day of the week */
  __set_tm_wday(days, tim_p);

  return tim;
}
