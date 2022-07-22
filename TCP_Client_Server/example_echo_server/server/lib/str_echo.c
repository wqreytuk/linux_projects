#include	"unp.h"

void
str_echo(int sockfd, pid_t child_pid)
{
	ssize_t		n;
	char		buf[MAXLINE];

again:
	while ((n = read(sockfd, buf, MAXLINE)) > 0) {
		printf("fd number:%d\tpid: %d\tdata in buf: %s\n",sockfd, child_pid, buf);
		Writen(sockfd, buf, n);
	}

	if (n < 0 && errno == EINTR)
		goto again;
	else if (n < 0)
		err_sys("str_echo: read error");
}
