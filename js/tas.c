#include "u.h"
#include "libc.h"

int
tas(long *x)
{
	int i;

	i = *x;
	*x = 1;
	return i;
}

