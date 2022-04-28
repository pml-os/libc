#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include "_ansi.h"
#include <sys/cdefs.h>
#include <sys/signal.h>

_BEGIN_STD_C

struct _reent;

_sig_func_ptr _signal_r (struct _reent *, int, _sig_func_ptr);
int	_raise_r (struct _reent *, int);

#ifndef _REENT_ONLY
_sig_func_ptr signal (int, _sig_func_ptr);
int	raise (int);
void	psignal (int, const char *);
#endif

_END_STD_C

#endif /* _SIGNAL_H_ */
