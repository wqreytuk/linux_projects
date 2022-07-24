#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

sem_t   mutex;
int     fd;

void write_file(char* thread_name) {
    write(fd, thread_name, strlen(thread_name));
    write(fd, "\n", 1);
}
void* thread(void* arg)
{
    char* thread_name = (char*)arg;
    int n = 10000;
    while (n != 0) {
        //wait
        sem_wait(&mutex);
        printf("\n%s entered..\n", thread_name);

        //critical section
        write_file(thread_name);

        //signal
        printf("\n%s left...\n", thread_name);
        sem_post(&mutex);
        n--;
    }
    return NULL;
}


int main()
{
    fd = open("/tmp/1.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    sem_init(&mutex, 0, 1);
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread, (void*)"thread_1");
    sleep(2);
    pthread_create(&t2, NULL, thread, (void*)"thread_2");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    sem_destroy(&mutex);
    close(fd);
    return 0;
}