// 、、使用内存映射可以拷贝文件
/*
对原始文件进行内存映射
创建一个新文件
把新文件的数据拷贝映射到内存中
通过内存拷贝将第一个文件的内存映射区拷贝到第二个文件的内存映射区
释放资源
*/

// 匿名映射，不需要文件实体来进行内存映射
// 只能用于有血缘关系的进程间通信
#include <sys/mman.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
// int main()
// {

    /*
// kill函数
// pid》0将信号发送给指定进程
// =0：将信号发送给当前进程组
// =-1：将信号发送给每一个有权限接受这个信号的进程
// 《-1：进程组id的绝对值
// sig，要发送的信号
// kill(getppid(), 9);
// kill(getpid(), 9);
// raise函数，给当前进程发送信号
// sig，要发送的信号，成功返回0，失败返回非0*/
// alarm函数
// 设置定时器，倒计时，当时间为0的时候，会给当前进程发送一个 SIGALARM信号
// 取消定时器，alarm(0)即可
// 返回值是unsigned int，倒计时剩余的时间（上一个alarm剩余的时间）
// SIGALRARM信号默认终止当前进程，每个进程只能设置一个定时器
// int seconds = alarm(5);
// printf("%d\n", seconds);
//  sleep(2);
//  seconds = alarm(3);
// printf("%d\n", seconds);
// while(1){

// }
// 1秒钟电脑能输多少个数?
//无论进程处于什么状态，alarm都会正常计时
// 实际时间=内核时间+用户时间+io消耗的时间
// alarm(1);
// int i =0;
// while(1){
//     printf("%d\n",i++);
// }

// settimeer函数，用于替换alarm函数，且精度比alarm要高很多，
// 参数
// which，定时器以什么时间计时
//     ITIME_REAL： 真实时间，时间到达，就发送SIGALRM
//     ITIME_VIRTUAL；用户时间，时间到达就发送SIGVTALRM
//     ITIMER_PROF：进程在内核状态下消耗的时间
// 过3秒后，每两秒执行一次
// struct itimerval new_value;
// // 设置值
// new_value.it_interval.tv_sec = 2;
// new_value.it_interval.tv_usec =0;
// new_value.it_value.tv_sec=3;
// new_value.it_value.tv_usec=0;
// int ret = setitimer(ITIMER_REAL,&new_value,NULL);
// printf("定时器开始\n");
// if (ret==-1){
//     perror("settimer");
//     exit(0);
// }
// getchar();
// signal捕获信号
// sigkill,sigstop既不能被捕捉也不能被忽略
// signum：要捕捉的信号
// handler：捕捉到信号之后如何处理
//     sig_ign：忽略
//     sig_dfl：使用信号默认的行为
//     回调函数:捕获到信号后执行该函数
// 过3秒后，每两秒执行一次
// 注册信号捕捉函数
//忽略信号
// signal(SIGALRM,SIG_IGN);
//直行信号的默认动作（sig_ALRM结束程序）
// signal(SIGALRM,SIG_DFL);
// void (*sig_handler)(int),这是一个函数指针。返回void，参数int，函数名称：sig_handler
// 获取当前线程的现成id
int asda = 5;
//所欲的线程应该共享这100张门票
int tickets = 100;
// 创建一个互斥量
pthread_mutex_t mutex;

//出现了同一个线程，买同一张票的情况
// 需要确保多个线程不会同时修改一个变量
// 临界区。；i你姐资源
// #include<
pthread_mutex_t mutex1;
pthread_mutex_t mutex2;
void* sig_handler(void* arg) {
    //     printf("%d\n",*(int*)arg);
    //     printf("捕获到子线程：\n");
    //     // sleep(3);
    //     printf("llllllll子线程dilllllll]n的、n%ld\n",pthread_self());
    //     // return NULL;
    //     for (int i = 0; i < 5; i++)
    // {printf("我是你儿子%d\n",i);
    //     /* code */
    // }
    // return NULL;
    //     pthread_exit((void*)&asda);
    // 卖票
    // 枷锁
    while (1) {
        pthread_mutex_lock(&mutex);
        pthread_mutex_lock(&mutex);
        if (tickets > 0) {
            printf("子线程%ld正在卖地%d张哦票\n", pthread_self(), 100 - tickets + 1);
            tickets--;
        }
        else { pthread_mutex_unlock(&mutex); break; }
        // 解锁

        pthread_mutex_unlock(&mutex);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}


//     printf("%d\n",*(int*)arg);
//     printf("捕获到子线程：\n");
//     // sleep(3);
//     printf("llllllll子线程dilllllll]n的、n%ld\n",pthread_self());
//     // return NULL;
//     for (int i = 0; i < 5; i++)
// {printf("我是你儿子%d\n",i);
//     /* code */
// }
// return NULL;
//     pthread_exit((void*)&asda);
// 卖票
// 枷锁
pthread_mutex_t asdasdasdasdasdas;
int numm = 1;
void* sig_handler1(void* arg) {
    // // while(1){

    // pthread_mutex_lock(&mutex1);
    while (1) {
        pthread_mutex_lock(&asdasdasdasdasdas);
        numm++;
        //  pthread_mutex_unlock(&asdasdasdasdasdas);
        printf("++谢谢，tid:%ld,nummm:%d\n", pthread_self(), numm);
        pthread_mutex_unlock(&asdasdasdasdasdas);
        usleep(1);
        // (1);
    }
    // pthread_mutex_lock(&mutex2);
    // printf("workA：：\n");

    // pthread_mutex_unlock(&mutex2);
    // pthread_mutex_unlock(&mutex1);
    // //     if(tickets>0){
    // //     printf("子线程%ld正在卖地%d张哦票\n",pthread_self(),100-tickets+1);
    // //     tickets--;
    // // }else {pthread_mutex_unlock(&mutex);break;
    // // }
    // // 解锁

    // // pthread_mutex_unlock(&mutex);
    // // pthread_mutex_unlock(&mutex);
    // // }
    return NULL;
}
// 存在数据安全问题i，读写混乱
void* sig_handler12232(void* arg) {
    // // while(1){
    // pthread_mutex_lock(&mutex2);
    // sleep(1);
    // pthread_mutex_lock(&mutex1);
    // printf("二蛋：：\n");

    // pthread_mutex_unlock(&mutex1);
    // pthread_mutex_unlock(&mutex2);
    // //     if(tickets>0){
    // //     printf("子线程%ld正在卖地%d张哦票\n",pthread_self(),100-tickets+1);
    // //     tickets--;
    // // }else {pthread_mutex_unlock(&mutex);break;
    // // }
    while (1) {
        // numm++;
        pthread_mutex_lock(&asdasdasdasdasdas);
        printf("++读读，tid:%ld,nummm:%d\n", pthread_self(), numm);
        pthread_mutex_unlock(&asdasdasdasdasdas);
        usleep(1);
    }
    return NULL;
}

//     信号集
//     产生但是还没有被处理的信号被归到未决信号集

//     sigint信号状态被存储在第二个bit位上
//         bit位为1，说明信号处于未决状态
// 未决状态对的信号需要备处理
// 但是在处理之前需要和另一个叫做阻塞信号集的对应比特位进行比较
// 如果对应位置是1，那么就说明信号被阻塞，那么这个信号就不会被处理，直到指变成0
// 阻塞信号集默认不阻塞任何信号，我们可以手动进行设置（调用系统API）

// sigemptyset函数
//     清空信号集中的数据，所有标志位被设置为0
//     参数：set，要设置的信号集
// sigfillset函数
//     设为1
// sigaddset函数
//     设置信号集中的某一个标志位设置为1
// sigdelset 函数
//     和上面的相反，0
// sigismember函数
//     判断某个信号是否阻塞
// 上面的函数都是阻塞信号集的操作函数
// 创建一个信号集
// sigset_t set ;
// // 先清空
// sigemptyset(&set);
// // 判断信号是否在信号集中
// int ret = sigismember(&set,SIGINT);
// if (ret == 0) {
// printf("SIGINT 不阻塞\n");
// }else if(ret == 1) {
// printf("SIGINT 阻塞\n");

// }
// // 添加信号到信号集中
// sigaddset(&set,SIGINT);
// sigaddset(&set,SIGQUIT);
//  ret = sigismember(&set,SIGINT);
// if (ret == 0) {
// printf("SIGINT 不阻塞\n");
// }else if(ret == 1) {
// printf("SIGINT 阻塞\n");

// }
//  ret = sigismember(&set,SIGQUIT);
// if (ret == 0) {
// printf("SIGQUIT 不阻塞\n");
// }else if(ret == 1) {
// printf("SIGQUIT 阻塞\n");

// }
// sigdelset(&set, SIGQUIT);
//  ret = sigismember(&set,SIGQUIT);
// if (ret == 0) {
// printf("SIGQUIT 不阻塞\n");
// }else if(ret == 1) {
// printf("SIGQUIT 阻塞\n");

// }
// 系统调用设置信号集
// sigprocmask
// 该函数可以将我们自定义的信号集映射到内核中
// how：
//     如何对内核中的阻塞信号集进行处理
//         sig_block，mask|set
//         SIG_UNBLOCK: mask^set(异或操作
//         sig_setmask 覆盖内核的指
// sigpending
//     获取内核当中的未决信号集

// 编写一个程序，将所有的常规信号（1-31）的未决状态打印出来
// 设置某些信号是阻塞的，通过键盘来产生这些信号ctrl+?
// 设置2、3信号阻塞
// sigset_t set;
// sigemptyset(&set);
// // 将2、3信号添加到信号集中
// sigaddset(&set,SIGINT);
// sigaddset(&set,SIGQUIT);
// //修改内核中的阻塞信号集
// sigprocmask(SIG_BLOCK,&set, NULL);
// int num=0;
// while(1) {
//     printf("num：%d\n",num);
//     if(num == 5){
//         // 解除sigint的阻塞
//         sigprocmask(SIG_UNBLOCK,&set,NULL);
//     }
//     num++;
//     // 获取当前的未决信号集
//     sigset_t pendingset;
//     sigemptyset(&pendingset);
//     sigpending(&pendingset);
//     //遍历bit位
//     for(int i=1;i<=32;i++) {
// if(sigismember(&pendingset,i)==1){
//     printf("1");
// }else if(sigismember(&pendingset, i)==0) {
//     printf("0");
// }else{
//     perror("sigismember\n");exit(0);
// }


//     }printf("\n");sleep(1);
// }
// sigaction
// 检查或者改变信号的处理方式
// signum，需要捕捉的信号
// act，捕捉到信号后需要执行的动作
// oldaact，没用

// struct sigaction
//     sa_handle:回调函数指针

//     临时阻塞信号集
//     sa_mask
//     临时阻塞某些信号

// 使用那个信号处理对信号进行处理。如果是0表示使用回调函数
//     // 必须在设置定时器之前注册回调函数
// 最好使用sigaction去注册回调函数
// struct sigaction act;
// act.sa_flags = 0;
// act.sa_sigaction = sig_handler;
// //清空临时阻塞信号集
// sigemptyset(&act.sa_mask);
// sigaction(SIGALRM,&act,NULL);
// // sig_t retr =  signal(SIGALRM,sig_handler);
// // if(retr==SIG_ERR) {
// //     perror("signal注册");
// //     exit(-1);
// // }
// struct itimerval new_value;
// // 设置值
// new_value.it_interval.tv_sec = 2;
// new_value.it_interval.tv_usec =0;
// new_value.it_value.tv_sec=3;
// new_value.it_value.tv_usec=0;
// int ret = setitimer(ITIMER_REAL,&new_value,NULL);
// printf("定时器开始\n");
// if (ret==-1){
//     perror("settimer");
//     exit(0);
// }
// // getchar();
// // while(1);
// sigchild信号产生的条件
//     子进程终止
//     子进程接收到sigstop信号停止
//     子进程处于停滞状态，收到sigcont后唤醒
// 父进程默认葫芦该信号
// 可以用于解决僵尸进城的问题
#include<sys/time.h>
#include<time.h>
void sig_handler2(int num) {
    time_t     tm2 = time(NULL);
    struct tm* loc = localtime(&tm2);

    // char buf[524];
    // sprintf(buf, "%d-%d-%d %d:%d:%d\n",loc->tm_year,loc->tm_mon,loc->tm_mday,loc->tm_hour,loc->tm_min,loc->tm_sec);
    // printf("%s\n",buf);
    char* str = asctime(loc);
    int fd = open("time.txt", O_RDWR | O_CREAT | O_APPEND, 0664);
    write(fd, str, strlen(str));
    close(fd);
    // printf("捕捉奥得信号：%d\n",num);
    // // 回首紫禁城
    // // while(1){
    // // wait(NULL);}
    // while (1)
    // {int ret =waitpid(-1,NULL,WNOHANG);
    //     /* code */
    //     if(ret>0){
    //         printf("二字挂了：%d\n", ret);
    //     }else if(ret ==0) {
    //         // 说明还有子进程或者
    //           break;
    //     }else if(ret ==- 1){
    //         // 没有紫禁城了
    //         break;
    //     }
    // }

}
#include<sys/shm.h>
// int main()
// {
//     // 提前设置好阻塞信号集
//     // 阻塞sigchild
//     // 因为UN在西main这种可能：
//     //     子进程在注册号回调函数之前就已经结束了
// sigset_t set;
// sigemptyset(&set);
// sigaddset(&set,SIGCHLD);
// sigprocmask(SIG_BLOCK,&set  ,NULL);


// pid_t pid;
// int count=20;
// for (size_t i = 0; i < count; i++)
// {
//     pid = fork();
//     if(pid==0){
//         break;
//     }
//     /* code */

// }
// // 捕捉子进程死亡时发送的sigchild信号
// struct sigaction act;
// act.sa_flags=0;
// act.sa_sigaction = sig_handler2;
// sigemptyset(&act.sa_mask);
// sigaction(SIGCHLD,&act,NULL);
// // 注册完信号捕捉之后，就接触阻塞
// sigprocmask(SIG_UNBLOCK,&set,NULL);
// if(pid>0){
//     // 父进程
//     while(1){
//         printf("我是你爹\n");
//         sleep(2);
//     }} else if(pid==0){
//         printf("儿字：%d\n",getpid());
//     }

// pid_t pid = fork();
// if(pid==0){
//     for(int i=0;i<5;i++) {
//         printf("孩子进程%d\n", i);
//         sleep(1);
//     }
// }else if(pid>0) {
//   printf("爹进程\n");
//   sleep(2);
//   printf("傻儿子\n");
//   kill(pid,SIGINT);
// }
// 共享内存
// 创建一个新的内存共享段
// 或者获取一个   既有的共享内存段
// shmat和当前进程进行关联
// shmdat，移除和当前进程的关联
// shmctl
// 创建一个共享内存
// int shmid = shmget(50,4096,IPC_CREAT|0664);
// // 和当前进程进行关联
// void* ptr = shmat(shmid,NULL,0);
// printf("%d\n", shmid);
// char*str = "hello world";
// memcpy(ptr,str,strlen(str)+1);
// printf("按任意键继续\n");
// getchar();
// shmdt(ptr);
// shmctl(shmid,IPC_RMID,NULL);
// ftok函数，根据指定的路径名和int指生成一个共享内存的key

// 虽然是int类型的指，但是内核只会使用他的一个字节，也就是说范围其实是0-255
// 操作系统如何知道一块共享内存有多少个进程关联
//     共享内存维护了一个结构体，struct shmid——ds
//     该结构体中有一个成员shm_noattach记录了相关信息
//     ipcs -m可以查看
// 编写一个守护进程，每隔两秒获取一下系统时间，将这个时间写入磁盘文件中
// 创建子进程，推出父进程
// pid_t pid =fork();
// if(pid>0){
//     exit(0);
// }
// // 将子进程提升为回话，
// setsid();
// // 设置掩码
// umask(022);
// // 更改工作目录
// chdir("/");
// // 关闭并重定向文件描述符
// // int fd = open("/dev/null",O_RDWR);
// // dup2(fd,STDIN_FILENO);
// // dup2(fd,STDOUT_FILENO);
// // dup2(fd,STDERR_FILENO);
// // 业务逻辑
// // 创建定时器
// // setitimer(ITIMER_REAL,&val,NULL);
// // 捕捉定是信号
// struct sigaction act;
// act.sa_flags = 0;
// act.sa_sigaction = sig_handler2;
// sigemptyset(&act.sa_mask);
// sigaction(SIGALRM,&act,NULL);
// // struct itimerval new_value;
// // 设置值
// struct itimerval new_value;
// new_value.it_interval.tv_sec = 2;
// new_value.it_interval.tv_usec =0;
// new_value.it_value.tv_sec=2;
// new_value.it_value.tv_usec=0;
// int ret = setitimer(ITIMER_REAL,&new_value,NULL);
// while(1){
//     sleep(5);
// }
// pthread_create函数
//     用于创建一个子线程

// 一般情况下，main函数所在的县城的为主县城
// 其余创建的现成为子线程
// 程序中默认只有一个线程（主线程）
// 调用pthread_create创建一个新的县城
// pthere_detach
//     分离县城
//     奋力一个县县城层
//     被分离的县城在中值得时候，资源会自动返回给系统
//     不能多次分离
//     否则会产生不可预料的行为
//     不能去连接一个已经分离的县城
//         否则会报错
//     参数：
//         分要分离的县城id
//         成功返回0，失败返回错误号
// 创建一个显成熟性
// 创建5个生产者线程，5个消费者线程
// 使用链表来实现容器
// 使用互斥量解决同步问题
pthread_mutex_t mutext;
// 创建条件变量
pthread_cond_t cond;
#include <semaphore.h>
// 创建两个信号量
sem_t psem;
sem_t csem;
struct Node {
    int num;
    struct Node* next;
};
// 头节点
struct Node* head = NULL;

void* producer(void* arg) {
    while (1) {
        // 不断地创建新的节点并添加到链表当中
        sem_wait(&psem);
        pthread_mutex_lock(&mutex);
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->next = head;
        head = new_node;
        new_node->num = rand() % 1000;
        printf("add node, num %d, tid: %ld\n", new_node->num, pthread_self());
        pthread_mutex_unlock(&mutex);
        // 通知消费者生产出了一个产品
        sem_post(&csem);
    }
    return NULL;
}
void* consumer(void* arg) {
    while (1) {
        sem_wait(&csem);
        // 保存头结点的指针
        pthread_mutex_lock(&mutex);
        struct Node* tmp = head;
        head = head->next;
        printf("delete node, num: %d, tid: %ld\n", tmp->num, pthread_self());
        free(tmp);
        pthread_mutex_unlock(&mutex);
        // 通知生产者可以再生产一个
        sem_post(&psem);
    }
    return NULL;
}
#include<arpa/inet.h>
#include<bits/socket.h>
void recyle_child(int arg) {
    while (1) {
        int ret = waitpid(-1, NULL, WNOHANG);
        if (-1 == ret) {
            // 所有的子进程都回收完毕
            printf("所有的子进程回收完毕\n");
            break;
        }
        else if (ret == 0) {
            // 说明还有子进程活着
            // 等待下一次信号进来
            break;
        }
        else if (ret > 0) {
            // 进程被回收了
            printf("子进程%d被回收了\n", ret);
        }
    }
}
#include<errno.h>
#include<ctype.h>
#include<ctype.h>
#include<ctype.h>
#include<sys/select.h>
#include<poll.h>
#include<sys/epoll.h>
int main()
{
    /**
 * epoll的原理
 * epoll_create()函数会在内核区分配一块内存
 * epoll->event poll
 * 返回值是一个文件描述符
 * struct eventpoll {
 *  ...
 *  struct rb_root rbr; //红黑树
 *  struct list_head rdlist; // ready list
 *  ...
 * }
 * 直接操作内核态的数据，不用从用户态和内核态来回切换了
 *
 * epollctl
 *
 * 直接在内核中开辟一块内存，就不用来回切换了
 * 提高效率
 * 红黑树   一种高效的数据结构
 *
 * 之前是线性数组结构，现在是红黑树结构
 *
 * epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
 *
 * 第一个参数是create方法的返回值
 * EPOLL_CTL_ADD 表示进行添加操作
 * lfd是要检测的描述符
 * 第四个参数ev，委托内核检测的事件
 *
 * struct epoll_event ev;
 * ev.events = EPOLLIN // 读事件
 * ev.data.fd = lfd // 要检测的文件描述符的指
 *
 * epoll_wait(epfd) // 该方法会将rdlist中的数据拷贝回用户态
 * for (){
 *
 * }
 *
 * 直接遍历返回的数据就行了，返回的结果是具体哪几个节点的状态发生了改变
 *
 * rdlist是一个双链表
 *
 *
 *
 */
 // 创建一个新的epoll实例，在内核中创建一个数据，这个中有两个比较重要的成员
 // 一个是需要检测文件描述符的数据（红黑树），另一个是就序列表，用于存放数据发生改变的文件描述符集合（双向链表）

 // 参数 size 目前该参数是没有意义的，随便写一个数就行（非0）

 // 返回值   >0 表示文件描述符，是用于操作epoll实例的     失败返回-1



 //  int ret = epoll_create(int size);
 // 对epoll实例进行管理
 // epoll_ctl（int epfd, int op, int fd , struct epoll_enevt* event）
 // epoll_ctl_add  epoll_ctl_mod   epoll_ctl_del
 // fd  常见的epoll检测事件   epollIN  epollout epollerr
 // epoll_ctl   添加文件描述符信息   删除  修改等的
 // 修改，可以修改要检测的事件，比如以前要检测读，我们可以修改为检测写
     // 

     // 检测函数
     // epoll——wait）（int epfd, struct epoll_event *events, int maxevents, int timeouts）—
     //epfd       epoll实例对应的文件描述符
 // events传出参数   ，里面保存的有发生了变化的文件描述符信息（哪几个发生了变化，就返回哪几个）
 // maxevents   第二个参数结构体数组的大小
 // timeout阻塞时间     0表示不阻塞。-1表示阻塞   直到检测到fd数据发生变化  就会解除阻塞

 //  》0 表示阻塞的时长（单位是毫秒）
 // 返回值，返回发生变化的文件描述符的个数


 // 
 //  创建socket
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == lfd) {
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(9999);

    // int opt_val = 1;
    // setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val));
    // 绑定
    int ret = bind(lfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (-1 == ret) {
        perror("bind");
        exit(-1);
    }
    // 监听
    ret = listen(lfd, 128);
    if (-1 == ret) {
        perror("listen");
        exit(-1);
    }

    // 调用epoll_create()创建一个epoll实例
    int epfd = epoll_create(100);
    // 将监听的文件描述符相关信息添加到epoll实例当中
    struct  epoll_event epev;
    // EPOLLIN表示检测数据到达事件
    epev.events = EPOLLIN;
    epev.data.fd = lfd;
    // EPOLL_CTL_ADD表示往epfd中添加事件和文件描述符
    epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &epev);


    struct  epoll_event epevs[1024] = { 0 };

    while (1) {
        // 调用epoll——wati检测文件描述符的变化
        // 阻塞检测文件描述符的变化
        int trett = epoll_wait(epfd, epevs, 1024, -1);
        if (-1 == trett) {
            perror("epoll_wait");
            exit(-1);
        }

        // 发生改变的个数
        printf("epoll_wait函数的返回值 ret = %d\n", trett);
        // 检测发生改变的文件描述符，返回值就会发生改变的文件描述符个数
        for (int i = 0; i < trett; i++)
        {
            int curfd = epevs[i].data.fd;

            // 如果发生变化的文件描述符是我们的监听描述符，那么说明有连接进来了
            if (curfd == lfd) {
                // 表示有新的客户端连接进来了（listen的lfd）
                struct sockaddr_in client_addr;
                int len = sizeof(client_addr);
                // 这个时候我们再去调用accept是不会阻塞的，因为lfd中已经有数据了
                int cfd = accept(lfd, (struct sockaddr*)&client_addr, (socklen_t*)&len);
                printf("新的客户端进来了\n");
                char client_ip[16];
                inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
                unsigned short client_port = ntohs(client_addr.sin_port);
                printf("客户端IP：%s\n端口：%d\n", client_ip, client_port);
                if (-1 == cfd) {
                    if (EINTR == errno) {
                        continue;
                    }
                    perror("accept");
                    exit(-1);
                }
                // 追加文件描述符
                epev.events = EPOLLIN;
                epev.data.fd = cfd;
                // 现在我们把连接描述符也追加进去
                epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
            }
            else {
                // 有数据到达
                // 说明这个文件描述符对应的缓冲区来数据了、
                // 我们一共就监听了两种描述符，除了lfd以外的全部是连接文件描述符
                // 如果不是lfd，那肯定就是conn_fd了，所以直接读取到达的数据就行了
                char buf[1024] = { 0 };
                memset(buf, 1024, 0);
                int len = read(curfd, buf, sizeof(buf));
                if (-1 == len) {
                    perror("read");
                    exit(-1);
                }
                else if (0 == len) {
                    printf("客户端断开连接了\n");
                    // 删除客户端对应的文件描述符
                    // 如果客户端断开连接了就把这个文件描述符从epoll检测的事件中删除
                    epoll_ctl(epfd, EPOLL_CTL_DEL, curfd, NULL);
                    close(curfd);
                }
                else if (len > 0) {
                    printf("读取到数据：%s\n", buf);
                    // 输出读取到的数据
                    write(curfd, buf, strlen(buf) + 1);
                }
            }
        }
    }
    close(lfd);
    close(epfd);
    return 0;
}
//     // 注册信号捕捉，用于回收子进程
//     struct sigaction act;
//     act.sa_flags=0;
//     act.sa_sigaction = recyle_child;
//     sigemptyset(&act.sa_mask);

//     sigaction(SIGCHLD, &act, NULL);


//     // TCP通信服务器的并发
//     // 使用多线程或者多进程解决
//     // 一个父进程，多个子进程
//     // 父进程用于接收客户端连接（循环）
//     // 子进程用于通信，每接收一个连接，就创建一个子进程

//     // 创建socket
//     int lfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (-1 == lfd) {
// 		perror("socket");
//         exit(-1);
//     }

//     struct sockaddr_in server_addr;
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_addr.s_addr = INADDR_ANY;
//     server_addr.sin_port = htons(9999);

//     // int opt_val = 1;
//     // setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &opt_val, sizeof(opt_val));
//     // 绑定
//     int ret = bind(lfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
//     if (-1 == ret) {
//         perror("bind");
//         exit(-1);
//     }
// 	// 监听
//     ret = listen(lfd, 128);
//     if (-1 == ret) {
//         perror("listen");
//         exit(-1);
//     } 
//     // fd_set read_set, tmp;
//     // FD_ZERO(&read_set);
//     // FD_SET(lfd, &read_set);
//     // int max_fd = lfd;
//     // 初始化检测的文件描述符数组
//     struct pollfd fds[1024];
//     for (size_t i = 0; i < 1024; i++)
//     {
//         fds[i].fd = -1;
//         fds[i].events = POLLIN;
//     }
//     fds[0].fd = lfd;
//     int nfds = 1023;

//     printf("等待客户端连接...\n");
//     // 循环等待客户端连接
//     while(1) {
//         // 避免内核修改我们的原始文件描述符列表
//         // tmp = read_set;
//         int ret = poll(fds, nfds+1, -1);

//         // 接受连接
//         // 设置select永久阻塞，不检测到文件描述符的变化就不会返回
//         // int select_ret = select(max_fd+1, &tmp, NULL, NULL, NULL);
//         if (-1 == ret) {
//             perror("poll");
//             exit(-1);
//         } else if (ret == 0) {
//             continue;
//         } else if (ret > 0) {

//                 // 说明检测到了有文件描述符对应的缓冲区的数据发生了改变
//                 // 返回的是发生改变的文件描述符的数量，我们还需要再去遍历一遍来判断具体是哪些文件描述符发生了改变
//                 if (fds[0].revents & POLLIN) {
//                     // 表示有新的客户端连接进来了（listen的lfd）
//                     struct sockaddr_in client_addr;
//                     int len = sizeof(client_addr);
//                     int cfd = accept(fds[0].fd, (struct sockaddr*)&client_addr, &len);
//                     printf("新的客户端进来了\n");
//                     char client_ip[16];
//                     inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_ip, sizeof(client_ip));
//                     unsigned short client_port = ntohs(client_addr.sin_port);
//                     printf("客户端IP：%s\n端口：%d\n", client_ip, client_port);
//                     if (-1 == cfd) {
//                         if (EINTR == errno ) {
//                             continue;
//                         }
//                         perror("accept");
//                         exit(-1);
//                     }
//                     // 将新的文件描述符加入到集合中
//                     // accept函数返回的文件描述符
//                     for (size_t i = 0; i < 1024; i++)
//                     {
//                         if (fds[i].fd == -1) {
//                             fds[i].fd = cfd;
//                             fds[i].events = POLLIN;
//                             break;  
//                         }
//                     }

//                 }
//                 for (size_t i = 1; i < 1024; i++)
//                 {
//                     // 判断该文件描述符是否为1
//                     if (fds[i].revents & POLLIN) {
//                         // 说明这个文件描述符对应的缓冲区来数据了
//                         char buf[1024] = {0};
//                         int len = read(fds[i].fd, buf, sizeof(buf));
//                         if (-1 == len) {
//                             perror("read");
//                             exit(-1);
//                         } else if (0 == len) {
//                             printf("客户端断开连接了\n");
//                             close(fds[i].fd);
//                             fds[i].fd = -1;
//                         } else if (len > 0) {
//                             printf("读取到数据：%s\n", buf);
//                             write(fds[i].fd, buf, strlen(buf)+1);
//                         }
//                     }
//                 }


//         }

//     }
//     close(lfd);
//     return 0;
// }


// //         struct sockaddr_in cliaddr;
// //         int len = sizeof(cliaddr);
// //         // 由于子进程的回收产生了一个软中断，导致accpet出错，错误号为EINTR
// //         int cfd = accept(lfd, (struct sockaddr*)&cliaddr, &len);
// // 		if (-1 == cfd) {
// //             if (EINTR == errno ) {
// //                 continue;
// //             }
// //        		perror("accept");
// //         	exit(-1);
// //     	}
// //         // 每一个连接进来，就创建出一个子进程来和客户端进行通信
// //         pid_t pid = fork();
// //         if (0 == pid) {
// //             // 子进程
// //             // 获取客户端信息
// //             char client_ip[16];
// // 			inet_ntop(AF_INET, &cliaddr.sin_addr.s_addr, client_ip, sizeof(client_ip));
// // 			unsigned short client_port = ntohs(cliaddr.sin_port);
// //             printf("客户端IP：%s\n客户端PORT：%d\n", client_ip, client_port);
// //             // 接收客户端发来的数据
// //             char recv_buf[1024];
// //             while(1) {

// //                 int len = recv(cfd, recv_buf, sizeof(recv_buf), 0);
// //                 if (-1 == len) {
// //                     perror("read");
// //                     exit(-1);
// //                 } else if (len > 0) {
// //                     printf("接收到数据：%s\n", recv_buf);
// //                 } else if (0 == len) {
// //                     printf("客户端断开连接\n");
// //                     break;
// //                 }
// //                 // 对客户端传进来的数据进行小写转大写的转换
// //                 for (int i = 0; i < len; i++) {
// //                     recv_buf[i] = toupper(recv_buf[i]);
// //                 }

// //                 // size加1是为了接收字符串的结束符\0
// //                 write(cfd, recv_buf, strlen(recv_buf)+1);
// //             }
// //             close(cfd);
// //             printf("子进程结束\n");
// //             exit(0);
// //         }
// //     }
// // 	close(lfd);

// //     return 0;
// // }    
// // //     // TCP通信的服务端
// // //     // 创建用于监听的套接字
// // //     int lfd = socket(AF_INET, SOCK_STREAM, 0);
// // //     if (-1 == lfd) {
// // //         perror("socket");
// // //         exit(-1);
// // //     }
// // //     // 绑定bind
// // //     struct sockaddr_in saddr;
// // //     saddr.sin_family = AF_INET;
// // //     inet_pton(AF_INET, "192.168.43.193", &saddr.sin_addr.s_addr);
// // //     saddr.sin_port = htons(9999);
// // //     int ret = bind(lfd, (struct sockaddr*)&saddr, sizeof(saddr));
// // //     if (-1 == ret) {
// // //         perror("bind");
// // //         exit(-1);
// // //     }
// // //     ret = listen(lfd, 8);
// // //     if (-1 == ret) {
// // //         perror("listen");
// // //         exit(-1);
// // //     }
// // //     printf("等待客户端连接...\n");
// // //     // 接收客户端连接
// // //     struct sockaddr_in caddr;
// // //     socklen_t len = sizeof(caddr);
// // //     int cfd = accept(lfd, (struct sockaddr*)&caddr, &len);
// // //     if (-1 == cfd) {
// // //         perror("accept");
// // //         exit(-1);
// // //     }
// // //     // 输出客户端信息
// // //     char client_ip[16];
// // //     inet_ntop(AF_INET, &caddr.sin_addr.s_addr, client_ip, sizeof(client_ip));
// // //     unsigned short client_port = ntohs(caddr.sin_port);
// // //     printf("客户端IP：%s\n端口：%d\n", client_ip, client_port);
// // //     // 开始通信
// // //     char recv_buf[1024] = {0};
// // //     while(1) {
// // //         // 获取客户端的消息
// // //         len = read(cfd, recv_buf, sizeof(recv_buf));
// // //         if (-1 == len) {
// // //             perror("read");
// // //             exit(-1);
// // //         }
// // //         else if (len > 0) {
// // //             printf("收到客户端的消息： %s\n", recv_buf);
// // //         }   
// // //         else if (0 == len) {
// // //             // 表示客户端断开连接
// // //             printf("客户端断开连接\n");
// // //             break;
// // //         }

// // //         char* data  = "我是服务器";
// // //         // 给客户端发送消息
// // //         write(cfd, data, strlen(data));
// // //     }
// // //     // 关闭文件描述符
// // //     close(lfd);
// // //     close(cfd);

// // //     return 0;
// // // }
// // //     // // 讲字符串IP地址转换为inet地址 
// // //     // // 新建一个IP字符串，点分十进制
// // //     // char buf[] = "192.168.1.4";
// // //     // unsigned int num = 0;
// // //     // // 转换为网络字节序
// // //     // inet_pton(AF_INET, buf, &num);
// // //     // unsigned char* p = (unsigned char*)&num;
// // //     // printf("%d %d %d %d\n", *p, *(p+1), *(p+2), *(p+3));

// // //     // printf("<----------------------------->\n");

// // //     // // 讲网络字节序转换成IP字符串
// // //     // // 3个.，每个位置最长为3位数，3*4+3+1，最后这个1是\0
// // //     // char ip[16] = "";
// // //     // inet_ntop(AF_INET, &num, ip, 16);
// // //     // printf("%s\n", ip);



// // //     // union {
// // //     //     short value;
// // //     //     char bytes[sizeof(short)];
// // //     // } test;
// // //     // test.value = 0x0102;
// // //     // if (test.bytes[0] == 1 && test.bytes[1] == 2) 
// // //     //     printf("当前主机字节序：大端\n");
// // //     // else if (test.bytes[0] == 2 && test.bytes[1] == 1) 
// // //     //     printf("当前主机字节序：小端\n");

// // //     // 网络字节序即大端序
// // //     // host to network short
// // //     // 主机字节序转换成网络字节序
// // //     // 用于转换端口 16bit short int
// // //     // htons
// // //     // ntohs
// // //     // 用于转换IP 32bit int
// // //     // host to network long
// // //     // htonl
// // //     // ntohl

// // //     // unsigned short h = 0x0102;
// // //     // printf("%x\n", h);
// // //     // unsigned short n = htons(h);
// // //     // printf("%x\n", n);

// // //     // printf("<----------------------------->\n");

// // //     // unsigned char buf[4] = {192, 168, 1, 100};
// // //     // printf("%d\n", *buf);
// // //     // printf("%d\n", *(buf+1));
// // //     // printf("%d\n", *(buf+2));
// // //     // printf("%d\n", *(buf+3));
// // //     // // 4个char相当于一个int，都是4字节
// // //     // // 把这一块内存转换成int指针，然后取值
// // //     // int num = *(int *)buf;
// // //     // int res = htonl(num);
// // //     // unsigned char* p = (char*)&res;
// // //     // printf("%d\n", *p);
// // //     // printf("%d\n", *(p+1));
// // //     // printf("%d\n", *(p+2));
// // //     // printf("%d\n", *(p+3));

// // // //     pthread_mutex_init(&mutex, NULL);
// // // //     pthread_cond_init(&cond, NULL);
// // // //     sem_init(&psem, 0, 8);
// // // //     sem_init(&csem, 0, 0);
// // // //     pthread_t ptids[5], ctids[5];
// // // //     for (size_t i = 0; i < 5; i++)
// // // //     {
// // // //         pthread_create(&ptids[i], NULL, producer, NULL);
// // // //         pthread_create(&ctids[i], NULL, consumer, NULL);

// // // //     }
// // // //     for (size_t i = 0; i < 5; i++)
// // // //     {
// // // //         pthread_join(ptids[i], NULL);
// // // //         pthread_join(ctids[i], NULL);

// // // //     }
// // // //     pthread_mutex_destroy(&mutex);
// // // //     pthread_cond_destroy(&cond);
// // // //     pthread_exit(NULL);

// // // //     return 0;
// // // // }
// // // // // pthread_attr_t attr;
// // // // // // 初始化属性变量
// // // // // pthread_attr_init(&attr);
// // // // // // 设置属性
// // // // // pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
// // // // // // 使用多线程实现买票的案例
// // // // // // 3个窗口，卖100张票
// // // // // // 创建三个字咸亨

// // // // // // 获取线程暂的大小
// // // // // // 生产者消费者模型
// // // // // 创建5个生产者线程,5个消费者线程
// // // // pthread_t ptids[5], ctids[5];
// // // // for (size_t i = 0; i < count; i++)
// // // // {
// // // //     pthread_create(&ptids[i])
// // // // }

// // // // size_t size;
// // // pthread_attr_getstacksize(&attr,&size);
// // // printf("站大小：…%ld\n",size);
// // // pthread_t  tid1 ,tid2,tid3;
// // // // 创建三个写线程，5个度线程// 创建一个子线程
// // // int num = 5;
// // // pthread_mutex_init(&asdasdasdasdasdas,NULL);
// // // pthread_t  wstid[3],rtids[5];
// // // for (int i = 0; i < 5; i++)
// // // {int ret2 = pthread_create(&rtids[i],NULL,sig_handler1,(void*)&num);
// // //     /* code */
// // // }
// // // for (int i = 0; i < 3; i++)
// // // {int ret2 = pthread_create(&wstid[i],NULL,sig_handler12232,(void*)&num);
// // //     /* code */
// // // }
// // // // 设置线程分离
// // // for (int i = 0; i < 5; i++)
// // // {int ret2 = pthread_detach(rtids[i]);
// // //     /* code */
// // // }
// // for (int i = 0; i < 3; i++)
// // {int ret2 = pthread_detach(wstid[i]);
// //     /* code */
// // }
// // pthread_exit(NULL);
// // printf("你能执行我？？？？\n");
// // pthread_mutex_destroy(&asdasdasdasdasdas);
// // return 0;}
// // //读写锁
// // // // 读的操作需要比较多，因为读操作没必要被阻塞
// // // // rwlock


// // // // 互斥量
// // // //    pthread_mutex_t mutex1; 
// // // //    pthread_mutex_t mutex2; 
// // // pthread_mutex_init(&mutex1,NULL);
// // // pthread_mutex_init(&mutex2,NULL);
// // // int ret2 = pthread_create(&tid1,NULL,sig_handler1,(void*)&num);
// // // int re3t = pthread_create(&tid2,NULL,sig_handler22,(void*)&num);  
// // // // int re2t = pthread_create(&tid3,NULL,sig_handler,(void*)&num);
// // // // 回收子线程资源
// // // pthread_join(tid1,NULL);
// // // pthread_join(tid2,NULL);
// // // // pthread_join(tid3,NULL);
// // // // 设置线程分离
// // // // pthread_detach(tid1);
// // // // pthread_detach(tid2);
// // // // pthread_detach(tid3);
// // // // 推出主线程
// // // pthread_exit(NULL);
// // // // 释放互斥量
// // // pthread_mutex_destroy(&mutex1);
// // // pthread_mutex_destroy(&mutex2);
// // // // if(0!=ret){
// // // //     char* errstr = strerror(ret);
// // // //     printf("error: %s\n", errstr);
// // // // }
// // // // // pthread_cancel(tid);

// // // for (int i = 0; i < 5; i++)
// // // {printf("%d\n",i);
// // //     /* code */
// // // }
// // // printf("子线程id%ld主线程ID：%ld\n", tid,pthread_self());
// // // // 显成熟性

// // // // pthread_atfork
// // // // 回首紫禁城
// // // // int* asdasdasd ;
// // // // int caousod = pthread_join(tid,(void **)&asdasdasd);
// // // // if(ret!=0){
// // // //     char* errstr = strerror(ret);
// // // //     printf("error: %s",errstr);
// // // // }   
// // // // printf("紫禁城的返回值%d\n",*asdasdasd);
// // // // printf("子线程资源回收成功\n");
// // // // sleep(5);
// // // // 终止一个子线程
// // // // pthread-exit
// // // //     需要传递一个指针作为返回值
// // // //     可以再pthread_join中获取到
// // // // 终止一个县城，在哪个现成中调用，就终止哪个现成
// // // // 让主线程退出
// // // // 不会影响其他县城

// // // // 子线程结束是对应的资源就不需要主线程去释放了
// // // // pthread_detach(tid);
// // // // pthread_cancel函数
// // // //     终止现成（取消现）
// // // //     取消个现成，种植某个县城，但并不是立马终止
// // // //     等到现成执行到一个去小店，现成才会终止
// // // //     系统规定的系统调用
// // // //     粗略理解为用户渠道内核二区的切换位置

// // // // 对分离的子线程进行连接
// // // // 会报错，因为已经分离的子线程不能再进行连接了
// // // // int retttt = pthread_join(tid,NULL);
// // // // if(0!=retttt){
// // // //     char* errstr = strerror(retttt);
// // // //     printf("retttt  error: %s\n", errstr);
// // // // }
// // // // 释放显成熟性
// // // pthread_attr_destroy(&attr);
// // // pthread_exit(NULL);
// // // // printf("我他妈不会执行\n");
// // // // // 比较两个现成id是否相等
// // // // // pthread_equal
// // // // // 不同的操作系统，，实现发哪个是可能不太一样有的是无符号长正兴（大部分），有的是结构体类型
// // // // pthead_join
// // // //    挥手自现成的资源。和wait差不多
// // // //    这个函数是阻塞的
// // // //    调用一次智能回收一个子线程
// // // //    ，一般在主线程中使用
// // // //    retvalu: 勇于接受子线程退出时的返回值
// // // //             二级指针

// // /*

// //     // char * buf;
// //     // strcpy(buf, "cao nima");return 0;}/*
// //     // 修改mmap的flags参数，之前使用的是MAP_SHARED
// //     // 现在我们要用的是MAP_ANON
// //     int len = 1204;
// //     void *ptr = mmap(NULL, len, PROT_READ|PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
// //     if (ptr == MAP_FAILED)
// //     {
// //         perror("mmap");
// //         exit(0);
// //     }
// //     // 父子进程间通信
// //     int pid = fork();
// //     if (pid > 0)
// //     {
// //         strcpy((char *)ptr, "hello world");
// //         wait(NULL);
// //     }
// //     else if (0 == pid)
// //     {
// //         sleep(1);
// //         printf("%s\n", (char *)ptr);
// //     }
// //     // 释放内存映射区
// //     int ret = munmap(ptr, len);
// //     // int fd = open("englsih.txt", O_RDONLY);
// //     // // 获取原始文件的大小
// //     // int len = lseek(fd, 0, SEEK_END);
// //     // // 创建一个新文件，并对其大小进行拓展
// //     // int fd1 = open("cpy.txt", O_CREAT | O_RDWR, 0664);
// //     // truncate("cpy.txt", len);
// //     // write(fd1, " ", 1);
// //     // // 分别进行内存映射
// //     // void *ptr = mmap(NULL, len, PROT_READ, MAP_SHARED, fd, 0);
// //     // void *ptr1 = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd1, 0);
// //     // if (ptr == MAP_FAILED)
// //     // {
// //     //     perror("mmap");
// //     //     exit(0);
// //     // }
// //     // if (ptr1 == MAP_FAILED)
// //     // {
// //     //     perror("mmap");
// //     //     exit(0);
// //     // }
// //     // // 内存拷贝
// //     // memcpy(ptr1, ptr, len);
// //     // munmap(ptr1, len);
// //     // munmap(ptr, len);
// //     // close(fd1);
// //     // close(fd);
// //     return 0;
// // }
// // */

