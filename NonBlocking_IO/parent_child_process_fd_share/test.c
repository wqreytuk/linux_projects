#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
int main(char* argv[]) {
    int fd = open("abc.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    pid_t pid = fork();
    if (0 == pid) {
        sleep(1);
        printf("child fd offset before write %ld\n", lseek(fd, 0, SEEK_CUR));
        write(fd, "xyz", 3);
        printf("child fd offset after write %ld\n", lseek(fd, 0, SEEK_CUR));
    }
    else {
        write(fd, "xyz", 3);
        printf("parent fd offset %ld\n", lseek(fd, 0, SEEK_CUR));
    }
    close(fd);
    return 0;
}