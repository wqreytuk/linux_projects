

#include "lib/unp.h"



int main(int argc, char* argv[]) {
	int				listen_fd, conn_fd;
	pid_t			child_pid;
	socklen_t		clie_len;
	struct sockaddr_in cli_addr, serv_addr;

	listen_fd = Socket(AF_INET, SOCK_STREAM, 0);

	bzero(&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERV_PORT);

	Bind(listen_fd, (SA*)&serv_addr, sizeof(serv_addr));

}