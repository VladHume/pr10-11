#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        // Child process
        const char *child_msg = "Written by child process\n";
        write(fd, child_msg, sizeof("Written by child process\n") - 1);
    } else {
        // Parent process
        const char *parent_msg = "Written by parent process\n";
        write(fd, parent_msg, sizeof("Written by parent process\n") - 1);
        wait(NULL); // Wait for child to finish
    }

    close(fd);
    return 0;
}
