## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = cygnus

INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)

LIB_SOURCES = \
	asctime.c	\
	asctime_r.c	\
	clock.c		\
	ctime.c		\
	ctime_r.c	\
	difftime.c	\
	gettzinfo.c	\
	gmtime.c	\
	gmtime_r.c	\
	lcltime.c	\
	lcltime_r.c	\
	mktime.c	\
	timegm.c	\
	month_lengths.c \
	strftime.c  	\
	strptime.c	\
	time.c		\
	tzcalc_limits.c \
	tzlock.c	\
	tzset.c		\
	tzset_r.c	\
	tzvars.c	\
	wcsftime.c

libtime_la_LDFLAGS = -Xcompiler -nostdlib

if USE_LIBTOOL
noinst_LTLIBRARIES = libtime.la
libtime_la_SOURCES = $(LIB_SOURCES)
noinst_DATA = objectlist.awk.in
else
noinst_LIBRARIES = lib.a
lib_a_SOURCES = $(LIB_SOURCES)
lib_a_CFLAGS = $(AM_CFLAGS)
noinst_DATA =
endif # USE_LIBTOOL

# This rule is needed so that wcsftime.o is rebuilt when strftime.c changes.
include $(srcdir)/../../Makefile.shared

$(lpfx)wcsftime.$(oext): strftime.c

CHEWOUT_FILES = \
	asctime.def	\
	clock.def 	\
	ctime.def	\
	difftime.def	\
	gmtime.def	\
	lcltime.def	\
	mktime.def	\
	timegm.def	\
	strftime.def	\
	time.def	\
	tzlock.def	\
	tzset.def	\
	wcsftime.def

CHAPTERS = time.tex
