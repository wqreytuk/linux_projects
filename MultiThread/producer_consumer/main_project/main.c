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
		// ����
		pthread_mutex_lock(&BufferLock);
		printf("\n\t\t---------------------------\n");
		while (QueueSize == BUFFER_SIZE && StopRequested == 0)
		{
			// buffer�Ѿ����ˣ��ȴ������߳Ե�buffer��Ķ���
			// �����ȴ��������ͷ��ź���BufferNotFull
			pthread_cond_wait(&BufferNotFull, &BufferLock);
		}
		
		if (StopRequested == 1)
		{
			// ������߳�ֹ֪ͨͣ���������ֱ������ѭ����ֹ��ǰ�߳�
			pthread_mutex_unlock(&BufferLock);
			break;
		}
		
		// �˴�ִ�б�Ҫ�Ĳ��������Ǵ�����ʾĿ�ģ���ֻ�����������Ϣ������QueueSize�Ĵ�С
		printf("here is thread_%s executing!\n", thread_name);
		QueueSize++;
		// ����
		pthread_mutex_unlock(&BufferLock);

		// �ͷ�BufferNotEmpty������������ȥ��buffer��Ķ���
		pthread_cond_signal(&BufferNotEmpty);
		
		// ˯��һ���ֹ�������Ƶ��
		sleep(1);
	}
	printf("thread_%s is exiting!\n", thread_name);
	return NULL;
}

void* ConsumerThreadProc(void* arg) {
	char* thread_name = (char*)arg;
	while (1) {
		// ����
		pthread_mutex_lock(&BufferLock);
		while (QueueSize == 0 && StopRequested == 0)
		{
			// buffer�ǿյģ��ȴ���������buffer��Ŷ���
			// �����ȴ��������ͷ��ź���BufferNotEmpty
			pthread_cond_wait(&BufferNotEmpty, &BufferLock);
		}

		if (StopRequested == 1)
		{
			// ������߳�ֹ֪ͨͣ���������ֱ������ѭ����ֹ��ǰ�߳�
			pthread_mutex_unlock(&BufferLock);
			break;
		}

		// �˴�ִ�б�Ҫ�Ĳ��������Ǵ�����ʾĿ�ģ���ֻ�����������Ϣ����СQueueSize�Ĵ�С
		printf("here is thread_%s executing!\n", thread_name);
		QueueSize--;
		// ����
		pthread_mutex_unlock(&BufferLock);

		// �ͷ�BufferNotFull��������������buffer��Ŷ���
		pthread_cond_signal(&BufferNotFull);

		// ˯��һ���ֹ�������Ƶ��
		sleep(1);
	}
	printf("thread_%s is exiting!\n", thread_name);
	return NULL;
}


int main(int argc, char* argv[]) {
	// ��ʼ����������
	pthread_cond_init(&BufferNotEmpty, NULL);
	pthread_cond_init(&BufferNotFull, NULL);

	// ��ʼ��������
	pthread_mutex_init(&BufferLock, NULL);

	// �����߳�
	pthread_t tid_a = 1;
	pthread_t tid_b = 2;
	char thread_a_name[520] = "A";
	char thread_b_name[520] = "B";
	pthread_create(&tid_a, NULL, ProducerThreadProc, (void*)thread_a_name);
	pthread_create(&tid_b, NULL, ConsumerThreadProc, (void*)thread_b_name);

	puts("Press enter to stop...");
	getchar();

	// ���������������������ͣ���洴�����������߳�
	pthread_mutex_lock(&BufferLock);
	printf("stop request\n");
	StopRequested = 1;
	// ����
	pthread_mutex_unlock(&BufferLock);

	// �����������ڵȴ��������������̣߳���ֹ���߳���Ϊһֱ�ȴ��ź����ͷŶ��޷������˳�
	pthread_cond_broadcast(&BufferNotEmpty);
	pthread_cond_broadcast(&BufferNotFull);

	// �����߳�
	pthread_join(tid_a, NULL);
	pthread_join(tid_b, NULL); 

	return 0;
}
