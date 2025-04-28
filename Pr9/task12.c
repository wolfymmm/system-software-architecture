#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

int main() {
    while (1) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork failed");
            printf("errno = %d\n", errno);
            break;
        } else if (pid == 0) {
            // дочірній процес просто чекає
            pause();
            exit(0);
        } else {
            printf("Created process with PID: %d\n", pid);
        }
    }

    return 0;
}
