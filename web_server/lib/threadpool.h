#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

// 线程池类，将它定义为模板类是为了代码复用，模板参数T是任务类
template<typename T>
class threadpool {
public:
    /*thread_number是线程池中线程的数量，max_requests是请求队列中最多允许的、等待处理的请求的数量*/
    threadpool(int thread_number = 8, int max_requests = 10000);
    ~threadpool();
    bool append(T* request);

private:
    /*工作线程运行的函数，它不断从工作队列中取出任务并执行之*/
    static void* worker(void* arg);
    void run();

private:
    // 线程的数量
    int m_thread_number;

    // 描述线程池的数组，大小为m_thread_number    
    pthread_t* m_threads;

    // 请求队列中最多允许的、等待处理的请求的数量  
    int m_max_requests;

    // 请求队列
    std::list< T* > m_workqueue;

    // 保护请求队列的互斥锁
    locker m_queuelocker;

    // 是否有任务需要处理
    sem m_queuestat;

    // 是否结束线程          
    bool m_stop;
};

template< typename T >
// 使用列表初始化的形式，将两个成员变量m_thread_number和m_max_requests进行了初始化
threadpool< T >::threadpool(int thread_number, int max_requests) :
    m_thread_number(thread_number), m_max_requests(max_requests),
    m_stop(false), m_threads(NULL) {

    // 线程数量和允许的最大请求数量，判断传入的参数值是否合法
    if ((thread_number <= 0) || (max_requests <= 0)) {
        throw std::exception();
    }

    // 根据m_thread_number成员的值初始化一个pthread_t线程数组
    m_threads = new pthread_t[m_thread_number];
    if (!m_threads) {
        throw std::exception();
    }

    // 创建thread_number 个线程，并将他们设置为脱离线程。
    for (int i = 0; i < m_thread_number; ++i) {
        printf("create the %dth thread\n", i);
        // 创建线程，worker是线程回调函数，就是线程要执行的操作
        // 我们来看一下，worker都做了什么
        if (pthread_create(m_threads + i, NULL, worker, this) != 0) {
            delete[] m_threads;
            throw std::exception();
        }

        // detach之后的线程就脱离我们的控制了，我们也不需要操心这些线程的资源回收
        if (pthread_detach(m_threads[i])) {
            delete[] m_threads;
            throw std::exception();
        }
    }
}

template< typename T >
threadpool< T >::~threadpool() {
    delete[] m_threads;
    m_stop = true;
}

template< typename T >
bool threadpool< T >::append(T* request)
{
    // 操作工作队列时一定要加锁，因为它被所有线程共享。
    m_queuelocker.lock();
    if (m_workqueue.size() > m_max_requests) {
        m_queuelocker.unlock();
        return false;
    }
    m_workqueue.push_back(request);
    m_queuelocker.unlock();
    m_queuestat.post();
    return true;
}

template< typename T >
void* threadpool< T >::worker(void* arg)
{
    // 首先将参数类型转换为threadpool指针
    threadpool* pool = (threadpool*)arg;
    // 调用其threadpool类的run方法
    pool->run();
    return pool;
}

template< typename T >
void threadpool< T >::run() {
    // 只要m_stop不为True就循环
    while (!m_stop) {
        // m_queuestat是一个信号量
        // 信号量-1  这是一个二进制信号量，只有0和1两种状态
        // 关于二进制信号量，请参考 https://blog.csdn.net/ma_de_hao_mei_le/article/details/125962536
        m_queuestat.wait();
        // 现在需要对队列进行操作，加锁
        m_queuelocker.lock();
        // 如果队列为空，解锁队列锁，继续循环
        if (m_workqueue.empty()) {
            m_queuelocker.unlock();
            continue;
        }
        // m_workqueue是一个list容器，注意这个list使用了模板T
        // 调用list的front方法，取出队列最前面的元素
        T* request = m_workqueue.front();
        // 从队列中删除最前面的元素（因为已经被取出来了）
        m_workqueue.pop_front();
        // 队列操作完成，解锁队列锁
        m_queuelocker.unlock();
        // 如果取队列失败，则继续，我不清楚在什么情况下这个if条件会满足
        if (!request) {
            continue;
        }
        // 开始对取出来的这个请求进行处理
        // 我们使用的是模板类，所以这个process函数是我们在初始化threadpool类时使用类的process函数
        // pool = new threadpool<http_conn>;
        // 因此我们应该去看http_conn.process
        // 现在我们去http_conn类的process函数
        request->process();
    }

}

#endif
