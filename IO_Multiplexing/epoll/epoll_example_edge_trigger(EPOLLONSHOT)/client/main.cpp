#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

#define PORT 8888
#define MAX_EVENT_NUMBER 1024
#define BUFFER_SIZE 10

void sig_handle(int sig) {
    printf("catch a sigpipe signal\n");
    printf("server have close\n");
    exit(0);
}

int main(int argc, char* argv[])
{
    const char* ip = "127.0.0.1";

    int ret = 0;
    char buf[1024];
    struct sockaddr_in address;
    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    inet_pton(AF_INET, ip, &address.sin_addr);
    address.sin_port = htons(PORT);

    signal(SIGPIPE, sig_handle);

    int listenfd = socket(PF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    while (1) {
        int ret = connect(listenfd, (struct sockaddr*)&address, sizeof(struct sockaddr_in));
        if (ret < 0)
        {
            printf("connect failure\n");
            sleep(1);
            continue;
        }
        break;
    }

    while (1)
    {
        memset(buf, 0, sizeof(buf));
        fgets(buf, BUFFER_SIZE, stdin);
        send(listenfd, buf, BUFFER_SIZE - 1, 0);
    }

    close(listenfd);
    return 0;
}