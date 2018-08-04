#include <u.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <ctype.h>
#include <pwd.h>
#include <libc.h>
#include <auth.h>
#include <fcall.h>
#include <authsrv.h>
#include <libsec.h>
#include "drawterm.h"

#undef socket
#undef connect
#undef getenv
#undef access

char*
getuser(void)
{
	return "glenda";
}

char*
getns(void)
{
	return NULL;
}

int
dialfactotum(void)
{
	return -1;
}

