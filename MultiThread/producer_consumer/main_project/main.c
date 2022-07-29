#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


#define BUFFER_SIZE 1

pthread_cond_t BufferNotEmpty;
pthread_cond_t BufferNotFull;
pthread_mutex_t BufferLock;
int StopRequested;
int QueueSize;

void* ProducerThreadProc(void* arg) {
	char* thread_name = (char*)arg;
	while (1) {
		// 加锁
		pthread_mutex_lock(&BufferLock);
		printf("\n\t\t---------------------------\n");
		while (QueueSize == BUFFER_SIZE && StopRequested == 0)
		{
			// buffer已经满了，等待消费者吃掉buffer里的东西
			// 阻塞等待消费者释放信号量BufferNotFull
			pthread_cond_wait(&BufferNotFull, &BufferLock);
		}
		
		if (StopRequested == 1)
		{
			// 如果主线程通知停止，则解锁并直接跳出循环终止当前线程
			pthread_mutex_unlock(&BufferLock);
			break;
		}
		
		// 此处执行必要的操作，但是处于演示目的，我只是输出调试信息并增加QueueSize的大小
		printf("here is thread_%s executing!\n", thread_name);
		QueueSize++;
		// 解锁
		pthread_mutex_unlock(&BufferLock);

		// 释放BufferNotEmpty，唤醒消费者去吃buffer里的东西
		pthread_cond_signal(&BufferNotEmpty);
		
		// 睡眠一秒防止输出过于频繁
		sleep(1);
	}
	printf("thread_%s is exiting!\n", thread_name);
	return NULL;
}

void* ConsumerThreadProc(void* arg) {
	char* thread_name = (char*)arg;
	while (1) {
		// 加锁
		pthread_mutex_lock(&BufferLock);
		while (QueueSize == 0 && StopRequested == 0)
		{
			// buffer是空的，等待生产者往buffer里放东西
			// 阻塞等待生产者释放信号量BufferNotEmpty
			pthread_cond_wait(&BufferNotEmpty, &BufferLock);
		}

		if (StopRequested == 1)
		{
			// 如果主线程通知停止，则解锁并直接跳出循环终止当前线程
			pthread_mutex_unlock(&BufferLock);
			break;
		}

		// 此处执行必要的操作，但是处于演示目的，我只是输出调试信息并减小QueueSize的大小
		printf("here is thread_%s executing!\n", thread_name);
		QueueSize--;
		// 解锁
		pthread_mutex_unlock(&BufferLock);

		// 释放BufferNotFull，唤醒生产者往buffer里放东西
		pthread_cond_signal(&BufferNotFull);

		// 睡眠一秒防止输出过于频繁
		sleep(1);
	}
	printf("thread_%s is exiting!\n", thread_name);
	return NULL;
}


int main(int argc, char* argv[]) {
	// 初始化条件变量
	pthread_cond_init(&BufferNotEmpty, NULL);
	pthread_cond_init(&BufferNotFull, NULL);

	// 初始化互斥锁
	pthread_mutex_init(&BufferLock, NULL);

	// 创建线程
	pthread_t tid_a = 1;
	pthread_t tid_b = 2;
	char thread_a_name[520] = "A";
	char thread_b_name[520] = "B";
	pthread_create(&tid_a, NULL, ProducerThreadProc, (void*)thread_a_name);
	pthread_create(&tid_b, NULL, ConsumerThreadProc, (void*)thread_b_name);

	puts("Press enter to stop...");
	getchar();

	// 加锁，在这里加锁可以暂停上面创建的那两个线程
	pthread_mutex_lock(&BufferLock);
	printf("stop request\n");
	StopRequested = 1;
	// 解锁
	pthread_mutex_unlock(&BufferLock);

	// 唤醒所有正在等待此条件变量的线程，防止有线程因为一直等待信号量释放而无法正常退出
	pthread_cond_broadcast(&BufferNotEmpty);
	pthread_cond_broadcast(&BufferNotFull);

	// 回收线程
	pthread_join(tid_a, NULL);
	pthread_join(tid_b, NULL); 

	return 0;
}
