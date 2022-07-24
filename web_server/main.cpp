#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "locker.h"
#include "threadpool.h"
#include "http_conn.h"

#define MAX_FD 65536   // 最大的文件描述符个数
#define MAX_EVENT_NUMBER 10000  // 监听的最大的事件数量

// 添加文件描述符
// 下面这两个extern函数修饰的函数声明在当前文件所包含的头文件中是找不到的
// 但是编译和链接阶段都不会报错，首先在编译的时候，编译器是无法找到这两个函数的实现的
// 但是由于有extern关键字修饰，就没有报错，编译通过
// 然后在链接阶段，链接器会在我们的liblib.a库文件中找到这两个函数，因此链接也没有问题
extern void addfd(int epollfd, int fd, bool one_shot);
extern void removefd(int epollfd, int fd);

void addsig(int sig, void(handler)(int)) {
    // 首先声明sigaction结构体变量
    struct sigaction sa;
    // 初始化结构体，即清空
    memset(&sa, '\0', sizeof(sa));
    // 开始填充结构体的各个成员、
    // 首先是sa_handler成员，该成员存储的是信号处理回调函数
    sa.sa_handler = handler;
    // sa_mask成员是一个__sigset_t类型的变量
    // 可以往里面添加一系列的信号，这些被添加进去的信号将不会在sig_handler执行的时候触发sig_handler
    // sigfillset函数会将所有的信号都添加到传给他的参数，也就是sa_mask中
    sigfillset(&sa.sa_mask);
    // 这里加一个断言，如果sigaction报错的话直接终止程序
    assert(sigaction(sig, &sa, NULL) != -1);
}

int main(int argc, char* argv[]) {

    // 程序为控制台应用程序，参数通过argv字符串数组传递进来
    // argc为参数个数，argv字符串数组的第一个字符串总是本程序的完整路径
    // 也就是说argc最小值是1，不可能为0
    if (argc <= 1) {
        // 这里调用了库函数basename，用于从一个路径中取出文件名部分
        printf("usage: %s port_number\n", basename(argv[0]));
        return 1;
    }

    // 本程序只接受一个参数，用于指定我们的webserver要监听到的端口
    // 我们会bind到本地的所有网卡 -> INADDR_ANY
    // 使用atoi库函数将字符串转换成int型
    int port = atoi(argv[1]);
    // addsig是我们自定义的函数
    // 接收两个参数，第一个是信号，第二个是信号的处理回调函数
    // SIGPIPE是管道破裂的信号，SIG_IGN是系统定义的处理函数，就是忽略这个信号
    // 我们进入到这个函数来复习一下信号的注册流程
    // 这行代码就做了一件事，就是忽略SIGPIPE信号
    addsig(SIGPIPE, SIG_IGN);

    // 这里threadpool是一个模板类
    threadpool< http_conn >* pool = NULL;
    try {
        // 实例化模板类，使用try catch包围，如果出现异常，直接终止程序
        // 这里使用的是默认构造函数
        // 不含任何参数或者所有的参数都带有默认值的构造函数就是默认构造函数
        // threadpool类中声明了一个带有默认参数的构造函数  
        // threadpool(int thread_number = 8, int max_requests = 10000);
        // 我们跟进去看看，这个构造函数都干了啥
        // 好了，现在我们看完了构造函数，其实构造函数做的事情很简单
        // 就是创建了一堆线程（默认是8个），线程回调函数就是从线程中取出请求
        // 然后对请求进行处理，具体怎么处理的，我们稍后再讲
        pool = new threadpool<http_conn>;
    }
    catch (...) {
        return 1;
    }

    // 初始化一个http_conn实例数组，数组长度为MAX_FD，即65536
    http_conn* users = new http_conn[MAX_FD];

    // 创建套接字
    int listenfd = socket(PF_INET, SOCK_STREAM, 0);

    int ret = 0;
    struct sockaddr_in address;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_family = AF_INET;
    address.sin_port = htons(port);

    // 端口复用
    int reuse = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));
    ret = bind(listenfd, (struct sockaddr*)&address, sizeof(address));
    ret = listen(listenfd, 5);

    // 创建epoll对象，和事件数组，添加
    epoll_event events[MAX_EVENT_NUMBER];
    int epollfd = epoll_create(5);
    // 添加到epoll对象中
    addfd(epollfd, listenfd, false);
    http_conn::m_epollfd = epollfd;

    while (true) {

        int number = epoll_wait(epollfd, events, MAX_EVENT_NUMBER, -1);

        if ((number < 0) && (errno != EINTR)) {
            printf("epoll failure\n");
            break;
        }

        for (int i = 0; i < number; i++) {

            int sockfd = events[i].data.fd;

            if (sockfd == listenfd) {

                struct sockaddr_in client_address;
                socklen_t client_addrlength = sizeof(client_address);
                int connfd = accept(listenfd, (struct sockaddr*)&client_address, &client_addrlength);

                if (connfd < 0) {
                    printf("errno is: %d\n", errno);
                    continue;
                }

                if (http_conn::m_user_count >= MAX_FD) {
                    close(connfd);
                    continue;
                }
                users[connfd].init(connfd, client_address);

            }
            else if (events[i].events & (EPOLLRDHUP | EPOLLHUP | EPOLLERR)) {

                users[sockfd].close_conn();

            }
            else if (events[i].events & EPOLLIN) {

                if (users[sockfd].read()) {
                    pool->append(users + sockfd);
                }
                else {
                    users[sockfd].close_conn();
                }

            }
            else if (events[i].events & EPOLLOUT) {

                if (!users[sockfd].write()) {
                    users[sockfd].close_conn();
                }

            }
        }
    }

    close(epollfd);
    close(listenfd);
    delete[] users;
    delete pool;
    return 0;
}