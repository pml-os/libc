/***
**** CAUTION!!! KEEP DOC CONSISTENT---if you change text of a message
****            here, change two places:
****            1) the leading doc section (alphabetized by macro)
****            2) the real text inside switch(errnum)
***/

/*
FUNCTION
	<<strerror>>, <<strerror_l>>---convert error number to string

INDEX
	strerror

INDEX
	strerror_l

SYNOPSIS
	#include <string.h>
	char *strerror(int <[errnum]>);
	char *strerror_l(int <[errnum]>, locale_t <[locale]>);
	char *_strerror_r(struct _reent <[ptr]>, int <[errnum]>,
			  int <[internal]>, int *<[error]>);

DESCRIPTION
<<strerror>> converts the error number <[errnum]> into a
string.  The value of <[errnum]> is usually a copy of <<errno>>.
If <<errnum>> is not a known error number, the result points to an
empty string.

<<strerror_l>> is like <<strerror>> but creates a string in a format
as expected in locale <[locale]>.  If <[locale]> is LC_GLOBAL_LOCALE or
not a valid locale object, the behaviour is undefined.

This implementation of <<strerror>> prints out the following strings
for each of the values defined in `<<errno.h>>':

o+
o 0
Success

o E2BIG
Arg list too long

o EACCES
Permission denied

o EADDRINUSE
Address already in use

o EADDRNOTAVAIL
Address not available

o EADV
Advertise error

o EAFNOSUPPORT
Address family not supported by protocol family

o EAGAIN
No more processes

o EALREADY
Socket already connected

o EBADF
Bad file number

o EBADMSG
Bad message

o EBUSY
Device or resource busy

o ECANCELED
Operation canceled

o ECHILD
No children

o ECOMM
Communication error

o ECONNABORTED
Software caused connection abort

o ECONNREFUSED
Connection refused

o ECONNRESET
Connection reset by peer

o EDEADLK
Deadlock

o EDESTADDRREQ
Destination address required

o EEXIST
File exists

o EDOM
Mathematics argument out of domain of function

o EFAULT
Bad address

o EFBIG
File too large

o EHOSTDOWN
Host is down

o EHOSTUNREACH
Host is unreachable

o EIDRM
Identifier removed

o EILSEQ
Illegal byte sequence

o EINPROGRESS
Connection already in progress

o EINTR
Interrupted system call

o EINVAL
Invalid argument

o EIO
I/O error

o EISCONN
Socket is already connected

o EISDIR
Is a directory

o ELIBACC
Cannot access a needed shared library

o ELIBBAD
Accessing a corrupted shared library

o ELIBEXEC
Cannot exec a shared library directly

o ELIBMAX
Attempting to link in more shared libraries than system limit

o ELIBSCN
<<.lib>> section in a.out corrupted

o EMFILE
File descriptor value too large

o EMLINK
Too many links

o EMSGSIZE
Message too long

o EMULTIHOP
Multihop attempted

o ENAMETOOLONG
File or path name too long

o ENETDOWN
Network interface is not configured

o ENETRESET
Connection aborted by network

o ENETUNREACH
Network is unreachable

o ENFILE
Too many open files in system

o ENOBUFS
No buffer space available

o ENODATA
No data

o ENODEV
No such device

o ENOENT
No such file or directory

o ENOEXEC
Exec format error

o ENOLCK
No lock

o ENOLINK
Virtual circuit is gone

o ENOMEM
Not enough space

o ENOMSG
No message of desired type

o ENONET
Machine is not on the network

o ENOPKG
No package

o ENOPROTOOPT
Protocol not available

o ENOSPC
No space left on device

o ENOSR
No stream resources

o ENOSTR
Not a stream

o ENOSYS
Function not implemented

o ENOTBLK
Block device required

o ENOTCONN
Socket is not connected

o ENOTDIR
Not a directory

o ENOTEMPTY
Directory not empty

o ENOTRECOVERABLE
State not recoverable

o ENOTSOCK
Socket operation on non-socket

o ENOTSUP
Not supported

o ENOTTY
Not a character device

o ENXIO
No such device or address

o EOPNOTSUPP
Operation not supported on socket

o EOVERFLOW
Value too large for defined data type

o EOWNERDEAD
Previous owner died

o EPERM
Not owner

o EPIPE
Broken pipe

o EPROTO
Protocol error

o EPROTOTYPE
Protocol wrong type for socket

o EPROTONOSUPPORT
Unknown protocol

o ERANGE
Result too large

o EREMOTE
Resource is remote

o EROFS
Read-only file system

o ESHUTDOWN
Can't send after socket shutdown

o ESOCKTNOSUPPORT
Socket type not supported

o ESPIPE
Illegal seek

o ESRCH
No such process

o ESRMNT
Srmount error

o ESTRPIPE
Strings pipe error

o ETIME
Stream ioctl timeout

o ETIMEDOUT
Connection timed out

o ETXTBSY
Text file busy

o EWOULDBLOCK
Operation would block (usually same as EAGAIN)

o EXDEV
Cross-device link

o-

<<_strerror_r>> is a reentrant version of the above.

RETURNS
This function returns a pointer to a string.  Your application must
not modify that string.

PORTABILITY
ANSI C requires <<strerror>>, but does not specify the strings used
for each error number.

<<strerror_l>> is POSIX-1.2008.

Although this implementation of <<strerror>> is reentrant (depending
on <<_user_strerror>>), ANSI C declares that subsequent calls to
<<strerror>> may overwrite the result string; therefore portable
code cannot depend on the reentrancy of this subroutine.

Although this implementation of <<strerror>> guarantees a non-null
result with a NUL-terminator, some implementations return <<NULL>>
on failure.  Although POSIX allows <<strerror>> to set <<errno>>
to EINVAL on failure, this implementation does not do so (unless
you provide <<_user_strerror>>).

POSIX recommends that unknown <[errnum]> result in a message
including that value, however it is not a requirement and this
implementation does not provide that information (unless you
provide <<_user_strerror>>).

This implementation of <<strerror>> provides for user-defined
extensibility.  <<errno.h>> defines <[__ELASTERROR]>, which can be
used as a base for user-defined error values.  If the user supplies a
routine named <<_user_strerror>>, and <[errnum]> passed to
<<strerror>> does not match any of the supported values,
<<_user_strerror>> is called with three arguments.  The first is of
type <[int]>, and is the <[errnum]> value unknown to <<strerror>>.
The second is of type <[int]>, and matches the <[internal]> argument
of <<_strerror_r>>; this should be zero if called from <<strerror>>
and non-zero if called from any other function; <<_user_strerror>> can
use this information to satisfy the POSIX rule that no other
standardized function can overwrite a static buffer reused by
<<strerror>>.  The third is of type <[int *]>, and matches the
<[error]> argument of <<_strerror_r>>; if a non-zero value is stored
into that location (usually <[EINVAL]>), then <<strerror>> will set
<<errno>> to that value, and the XPG variant of <<strerror_r>> will
return that value instead of zero or <[ERANGE]>.  <<_user_strerror>>
returns a <[char *]> value; returning <[NULL]> implies that the user
function did not choose to handle <[errnum]>.  The default
<<_user_strerror>> returns <[NULL]> for all input values.  Note that
<<_user_sterror>> must be thread-safe, and only denote errors via the
third argument rather than modifying <<errno>>, if <<strerror>> and
<<strerror_r>> are are to comply with POSIX.

<<strerror>> requires no supporting OS subroutines.

QUICKREF
	strerror ansi pure
*/

#include <pml/strerror.h>
#include <errno.h>
#include <string.h>

static const char *errno_table[] = __PML_STRERROR_TABLE;
static const size_t errno_size = sizeof (errno_table) / sizeof (const char *);

char *
_strerror_r (struct _reent *ptr,
	int errnum,
	int internal,
	int *errptr)
{
  char *error;
  extern char *_user_strerror (int, int, int *);
  if (!errptr)
    errptr = &ptr->_errno;
  if (errnum < 0 || errnum >= errno_size || (error = errno_table[errnum]) == 0)
    error = "";
  return error;
}

char *
strerror (int errnum)
{
  return _strerror_r (_REENT, errnum, 0, NULL);
}

char *
strerror_l (int errnum, locale_t locale)
{
  /* We don't support per-locale error messages. */
  return _strerror_r (_REENT, errnum, 0, NULL);
}
