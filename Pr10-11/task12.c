#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if (pid == 0) {
        // дочірній процес
        execlp("echo", "echo", "Hello from child", (char *)NULL);
        perror("execlp");
        exit(1);
    } else {
        // батьківський процес
        int status;
        waitpid(pid, &status, 0);
        printf("Child process finished\n");
    }
    return 0;
}
