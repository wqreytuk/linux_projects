参考链接：

- [https://blog.csdn.net/hnlyyk/article/details/50946655](https://blog.csdn.net/hnlyyk/article/details/50946655)



EPOLLONESHOT主要用于避免出现多个线程或者进程同时处理一个文件描述符的情况



在EPOLL的边缘触发模式下，fd中来了数据，线程1对其进行读取，但是此时fd中又一次有数据到达，那么就有可能被另一个处于检测状态的线程收到状态改变提醒，那么此时就会有两个不同的线程对用一个fd进行读取



EPOLLONESHOT保证在重置之前，fd的转态改变只会被触发一次，也就是说在重置EPOLLONESHOT之前，只能由一个线程或者进行来处理对应的fd