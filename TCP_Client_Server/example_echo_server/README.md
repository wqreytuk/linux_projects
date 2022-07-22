this is our simple C/S model

![Figure 5.1. Simple echo client and server.](README.assets/figure_5.1.png)



this is actually a full-duplex TCP connection



the server is concurrent, it can handle multi clients at the same time, which is implementing by forking child process



```c
for (;;) {
    clie_len = sizeof(cli_addr);
    conn_fd = Accept(listen_fd, (SA*)&cli_addr, &clie_len);

    if (0 == (child_pid = Fork())) {
        Close(listen_fd);
        str_echo(conn_fd);
        exit(0);
    }
    Close(conn_fd);
}
```



function `str_echo` is the main logic for client handling, it reads data sent from client and writes it back

```c
while ((n = read(sockfd, buf, MAXLINE)) > 0)
	Writen(sockfd, buf, n);
```

when client drops or closes the connection, `read` will return 0, which is the bytes read from `sockfd`, then the while loop is break, so child process is terminated
