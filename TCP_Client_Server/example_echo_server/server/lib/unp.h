#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>	
#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


#define	SA			struct sockaddr
#define SERV_PORT 	8888
#define	MAXLINE		4096	/* max text line length */

/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif


int		 	Socket(int, int, int);
void 		Bind(int, const SA*, socklen_t);
void	 	err_sys(const char *, ...);
static void	err_doit(int, int, const char *, va_list);