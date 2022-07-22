#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdarg.h>	
#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>


#define	SA			struct sockaddr
#define SERV_PORT 	8001
#define	MAXLINE		4096	/* max text line length */
#define	LISTENQ		1024	/* 2nd argument to listen() */


/* Define bzero() as a macro if it's not in standard C library. */
#ifndef	HAVE_BZERO
#define	bzero(ptr,n)		memset(ptr, 0, n)
/* $$.If bzero$$ */
/* $$.If memset$$ */
#endif


int		 	Socket(int, int, int);
void 		Bind(int, const SA*, socklen_t);
void		Listen(int, int); 
int			Accept(int, SA*, socklen_t*);

pid_t		Fork(void);
void		Close(int);

void	 	err_sys(const char *, ...);
static void	err_doit(int, int, const char *, va_list);

void		str_echo(int, pid_t);


void		Writen(int, void*, size_t);