#include "unp.h"

int main(int argc, char* argv[]) {
	int					listen_fd, conn_fd;
	pid_t				child_pid;
	socklen_t			clie_len;
	struct sockaddr_in	cli_addr, serv_addr;

	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	Bind(listen_fd, (SA*)&serv_addr, sizeof(serv_addr));

	Listen(listen_fd, LISTENQ);

	for (;;) {
		clie_len = sizeof(cli_addr);
		conn_fd = Accept(listen_fd, (SA*)&cli_addr, &clie_len);
		printf("parent listen fd: %d\n", listen_fd);
		printf("parent connection fd: %d\n", conn_fd);
		if (0 == (child_pid = Fork())) {
			Close(listen_fd);
			str_echo(conn_fd);
			printf("child listen fd: %d\n", listen_fd);
			printf("child connection fd: %d\n", conn_fd);
			exit(0);
		}
		Close(conn_fd);
	}
}
